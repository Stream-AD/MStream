import numpy as np
import math
import torch
import torch.nn as nn
import time
from torch.autograd import Variable
import pandas as pd
import argparse

np.random.seed(0)
torch.manual_seed(0)
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
"""Modified from https://github.com/burklight/nonlinear-IB-PyTorch"""


def compute_distances(x):
    x_norm = (x ** 2).sum(1).view(-1, 1)
    x_t = torch.transpose(x, 0, 1)
    x_t_norm = x_norm.view(1, -1)
    dist = x_norm + x_t_norm - 2.0 * torch.mm(x, x_t)
    dist = torch.clamp(dist, 0, np.inf)

    return dist


def KDE_IXT_estimation(logvar_t, mean_t):
    n_batch, d = mean_t.shape
    var = torch.exp(logvar_t) + 1e-10  # to avoid 0's in the log
    normalization_constant = math.log(n_batch)
    dist = compute_distances(mean_t)
    distance_contribution = -torch.mean(torch.logsumexp(input=-0.5 * dist / var, dim=1))
    I_XT = normalization_constant + distance_contribution

    return I_XT


def get_IXT(mean_t, logvar_t):
    IXT = KDE_IXT_estimation(logvar_t, mean_t)  # in natts
    IXT = IXT / np.log(2)  # in bits
    return IXT


def get_ITY(logits_y, y):
    HY_given_T = ce(logits_y, y)
    ITY = (np.log(2) - HY_given_T) / np.log(2)  # in bits
    return ITY


def get_loss(IXT_upper, ITY_lower):
    loss = -1.0 * (ITY_lower - beta * IXT_upper)
    return loss


parser = argparse.ArgumentParser(description="Training for MSTREAM-IB")
parser.add_argument(
    "--outputdim", type=int, help="number of output dimensions", default=12
)
parser.add_argument(
    "--inputdim", type=int, help="number of input dimensions", required=True
)
parser.add_argument("--input", help="input file", required=True)
parser.add_argument("--label", help="labels file", required=True)
parser.add_argument("--output", help="output file", default="ib.txt")
parser.add_argument(
    "--numRecords", type=int, help="number of records for training", default=256
)
parser.add_argument("--beta", type=float, help="beta value of IB", default=0.5)
parser.add_argument("--lr", type=float, help="learning rate", required=True)
parser.add_argument("--numEpochs", type=int, help="number of epochs", required=True)
args = parser.parse_args()
beta = args.beta


class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()
        self.e1 = nn.Linear(args.inputdim, args.outputdim)
        self.output_layer = nn.Linear(args.outputdim, 1)

    def forward(self, x):
        mu = self.e1(x)
        intermed = mu + torch.randn_like(mu) * 1
        x = self.output_layer(intermed)
        return x, mu


ce = torch.nn.BCEWithLogitsLoss()
data = torch.Tensor(np.loadtxt(args.input, delimiter=","))
label = pd.read_csv(args.label, names=["label"])[: args.numRecords]
t = time.time()
mean, std = data.mean(0), data.std(0)
new = (data - mean) / std
new[:, std == 0] = 0
label = torch.Tensor(np.array(label.label).reshape(-1, 1))

ae = AutoEncoder().to(device)
optimizer = torch.optim.Adam(ae.parameters(), lr=args.lr)

for epoch in range(args.numEpochs):
    train_x = Variable(new[: args.numRecords]).to(device)
    train_y = Variable(label).to(device)
    optimizer.zero_grad()
    train_logits_y, train_mean_t = ae(train_x)
    train_ITY = get_ITY(train_logits_y, train_y)
    logvar_t = torch.Tensor([0]).to(device)
    train_IXT = get_IXT(train_mean_t, logvar_t)
    loss = get_loss(train_IXT, train_ITY)
    loss.backward()
    optimizer.step()

recon = ae.e1(torch.autograd.Variable(new).to(device)).detach().cpu()
print("Time for Training IB is ", time.time() - t)
np.savetxt(args.output, recon.numpy(), delimiter=",", fmt="%.2f")
