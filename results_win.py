from sklearn import metrics
import pandas as pd
import numpy as np
import argparse

parser = argparse.ArgumentParser(description="Find AUC")
parser.add_argument("--label", help="labels file", required=True)
parser.add_argument("--scores", help="scores file", required=True)
parser.add_argument("--window", help="window size", type=int, required=True)
args = parser.parse_args()

data = pd.read_csv(args.label, names=["label"])
is_anom = data.label
scores = pd.read_csv(args.scores, header=None, squeeze=True)
window = args.window
aucfile = open('aucwindow'+str(window)+'.txt', 'w')
for low in range(0, data.shape[0], window):
	auc = metrics.roc_auc_score(is_anom[low:low+window], scores[low:low+window])
	aucfile.write('%f\n'%(auc))
aucfile.close()
