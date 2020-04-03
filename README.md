# MStream
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/bhatiasiddharth/M-Stream/blob/master/LICENSE)

MStream detects group anomalies from a multi-aspect data stream in constant time and memory. We output an anomaly score for each record.

## Getting started
1. Run `make` to compile code and create the binary.
2. Run `./mstream -n numericalfile -c categoricalfile -t timefile `
3. Run `make clean` to clean binaries.

## Demo

1. Create a `data` directory and place the datasets in this directory.
2. Run `./demo.sh DATASET_NAME` to compile the code and run it on the given dataset


## Command line options
  * `-h --help`: produce help message
  * `-n --numerical`: Numerical file name
  * `-c --categorical`: Categorical file name
  * `-c --time`: Timestamps file name
  * `-o --output`: Output file name (default: scores.txt)  
  * `-r --rows`: Number of Hash Functions (default: 2)  
  * `-b --buckets`: Number of Buckets (default: 1024)
  * `-a --alpha`: Temporal Decay Factor (default: 0.6)


## Input file format
MStream expects the input multi-aspect record stream to be stored in three files:
1. `Numerical file`: contains `,` separated Numerical Features. 
2. `Categorical file`: contains `,` separated Categorical Features. 
3. `Time File`: contains Timestamps. 

Both Numerical and Categorical files contain corresponding features of the multi-aspect record. Records should be sorted in non-decreasing order of their time stamps and the column delimiter should be `,`


## Datasets
1. [CICIDS-DoS](https://www.unb.ca/cic/datasets/ids-2018.html)
2. [UNSW-NB 15](https://www.unsw.adfa.edu.au/unsw-canberra-cyber/cybersecurity/ADFA-NB15-Datasets/)
3. [CICIDS-DDoS](https://www.unb.ca/cic/datasets/ids-2018.html)
