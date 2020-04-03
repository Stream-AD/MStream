from sklearn import metrics
import pandas as pd
import numpy as np
import argparse

parser = argparse.ArgumentParser(description="Find AUC")
parser.add_argument("--label", help="labels file", required=True)
parser.add_argument("--scores", help="scores file", required=True)
args = parser.parse_args()

data = pd.read_csv(args.label, names=["label"])
is_anom = data.label
scores = pd.read_csv(args.scores, header=None, squeeze=True)
fpr, tpr, _ = metrics.roc_curve(is_anom, scores)
auc = metrics.roc_auc_score(is_anom, scores)
count = np.sum(is_anom)
preds = np.zeros_like(is_anom)
indices = np.argsort(scores, axis=0)[::-1]
preds[indices[:count]] = 1
print(
    "AUC: ", auc,
)
