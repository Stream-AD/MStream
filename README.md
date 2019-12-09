# M-Stream
M-Stream, short for Streaming Multi-Aspect Group Anomaly Detection, detects group anomalies from a multi-aspect data stream in constant time and memory. We output an anomaly score for each record.

This implementation is based on the following paper - [M-Stream:Streaming Multi-Aspect Group Anomaly Detection](). *Siddharth Bhatia, Bryan Hooi*. 2020.

## Getting started
1. Run `make` to compile code and create the binary.
2. Run `./mstream -n numericalfile -c categoricalfile -t timefile `
3. Run `make clean` to clean binaries.

## Demo
1. Run `./demo.sh` to compile the code and run it on example dataset.


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
M-Stream expects the input multi-aspect record stream to be stored in three files:
1. `Numerical file`: containing `,` separated Numerical Features
2. `Categorical file`: containing `,` separated Categorical Features
3. `Time File`: containing Timestamps

Both Numerical and Categorical files contain corresponding features of the multi-aspect record. Records should be sorted in non-decreasing order of their time stamps and the column delimiter should be `,`


## Datasets
1. [CICIDS-DoS](https://www.unb.ca/cic/datasets/ids-2018.html)
2. [UNSW-NB 15](https://www.unsw.adfa.edu.au/unsw-canberra-cyber/cybersecurity/ADFA-NB15-Datasets/)
3. [CICIDS-DDoS](https://www.unb.ca/cic/datasets/ids-2018.html)
