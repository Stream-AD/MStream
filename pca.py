from sklearn.decomposition import PCA
import numpy as np
import time
import argparse

np.random.seed(0)  # For reproducibility
np.seterr(divide="ignore", invalid="ignore")
parser = argparse.ArgumentParser(description="Training for MSTREAM-PCA")
parser.add_argument("--dim", type=int, help="number of dimensions", default=12)
parser.add_argument("--input", help="input file", required=True)
parser.add_argument("--output", help="output file", default="pca.txt")
parser.add_argument(
    "--numRecords", type=int, help="number of records for training", default=256
)
args = parser.parse_args()
pca = PCA(n_components=args.dim)

data = np.loadtxt(args.input, delimiter=",")
mean, std = data.mean(0), data.std(0)
new = (data - mean) / std
new[:, std == 0] = 0
t = time.time()
pca.fit(new[: args.numRecords])
new = pca.transform(new)
print("Time for Training PCA is: ", time.time() - t)
np.savetxt(args.output, new, delimiter=",", fmt="%.2f")
