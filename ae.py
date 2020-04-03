import torch
import torch.nn as nn
import numpy as np
import time
import argparse
import os
os.environ['KMP_DUPLICATE_LIB_OK']=True # For MAC MKL Optimization
np.random.seed(0)
torch.manual_seed(0)
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

parser = argparse.ArgumentParser(description="Training for MSTREAM-AE")
parser.add_argument(
    "--outputdim", type=int, help="number of output dimensions", default=12
)
parser.add_argument(
    "--inputdim", type=int, help="number of input dimensions", required=True
)
parser.add_argument("--input", help="input file", required=True)
parser.add_argument("--output", help="output file", default="ae.txt")
parser.add_argument(
    "--numRecords", type=int, help="number of records for training", default=256
)
parser.add_argument("--lr", type=float, help="learning rate", required=True)
parser.add_argument("--numEpochs", type=int, help="number of epochs", required=True)
args = parser.parse_args()


class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()
        self.e1 = nn.Linear(args.inputdim, args.outputdim)
        self.output_layer = nn.Linear(args.outputdim, args.inputdim)

    def forward(self, x):
        x = F.relu(self.e1(x))
        x = self.output_layer(x)
        return x


ae = AutoEncoder().to(device)
loss_func = nn.MSELoss()
optimizer = torch.optim.Adam(ae.parameters(), lr=args.lr)
data = torch.Tensor(np.loadtxt(args.input, delimiter=","))
t = time.time()
mean, std = data.mean(0), data.std(0)
new = (data - mean) / std
new[:, std == 0] = 0
for epoch in range(args.numEpochs):
    x = torch.autograd.Variable(new[: args.numRecords]).to(device)
    optimizer.zero_grad()
    pred = ae(x)
    loss = loss_func(pred, x)
    loss.backward()
    optimizer.step()
recon = F.relu(ae.e1(torch.autograd.Variable(new).to(device))).detach().cpu()
print("Time for Training AE is ", time.time() - t)
np.savetxt(args.output, recon.numpy(), delimiter=",", fmt="%.2f")
