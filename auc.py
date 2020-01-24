from sklearn import metrics
from sklearn.metrics import precision_recall_curve
import matplotlib.pyplot as plt
import pandas as pd

#data = pd.read_csv("./Data/unsw_label.txt", names=['label']) 
#is_anom = data.label != 0 #UNSW

#data = pd.read_csv("./Data/ddos_label.txt", names=['label']) 
#is_anom = data.label != 1 #DDOS

data = pd.read_csv("./Data/dos_label.txt", names=['label']) 
is_anom = data.label != 'Benign' #DOS

#data = pd.read_csv("./Data/kdd_label.txt", names=['label']) 
#is_anom = data.label != 'normal.' #KDD

#data = pd.read_csv("./Data/cid_label.txt", names=['label']) 
#is_anom = data.label != 'normal' #CIDDS

methods = ['mstream']
for i in range(len(methods)):
	scores = pd.read_csv("scores.txt", header=None, squeeze=True)
	fpr, tpr, _ = metrics.roc_curve(is_anom, scores)
	auc = metrics.roc_auc_score(is_anom, scores)
	#f1 = metrics.f1_score(is_anom, scores)
	print("AUC: ", auc)
	#print("F1: ", f1)