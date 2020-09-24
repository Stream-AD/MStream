# MSᴛʀᴇᴀᴍ

<p>
  <a href="https://arxiv.org/pdf/2009.08451.pdf"><img src="http://img.shields.io/badge/Paper-PDF-brightgreen.svg"></a>
  <a href="https://github.com/Stream-AD/MStream/blob/master/LICENSE">
    <img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg">
  </a>
</p>

Implementation of

- [MSᴛʀᴇᴀᴍ: Fast Streaming Multi-Aspect Group Anomaly
Detection](https://arxiv.org/pdf/2009.08451.pdf). *Siddharth Bhatia, Arjit Jain, Pan Li, Ritesh Kumar, Bryan Hooi.*

![](https://www.comp.nus.edu.sg/~sbhatia/assets/img/mstream.png)
MSᴛʀᴇᴀᴍ detects group anomalies from a multi-aspect data stream in constant time and memory. We output an anomaly score for each record. MSᴛʀᴇᴀᴍ builds on top of [MIDAS](https://github.com/Stream-AD/MIDAS) to work in a multi-aspect setting such as event-log data, multi-attributed graphs etc.

## Demo

1. Run `bash run.sh KDD` to compile the code and run it on the KDD dataset.
2. Run `bash run.sh DOS` to compile the code and run it on the DOS dataset.
3. Run `bash run.sh UNSW` to compile the code and run it on the UNSW dataset.


## MSᴛʀᴇᴀᴍ
1. Change Directory to MSᴛʀᴇᴀᴍ folder `cd mstream`
2. Run `make` to compile code and create the binary
2. Run `./mstream -n numericalfile -c categoricalfile -t timefile `
3. Run `make clean` to clean binaries

## Command line options
  * `-h --help`: produce help message
  * `-n --numerical`: Numerical file name
  * `-c --categorical`: Categorical file name
  * `-c --time`: Timestamps file name
  * `-o --output`: Output file name (default: scores.txt)  
  * `-r --rows`: Number of Hash Functions (default: 2)  
  * `-b --buckets`: Number of Buckets (default: 1024)
  * `-a --alpha`: Temporal Decay Factor (default: 0.6)


## Input file format for MSᴛʀᴇᴀᴍ
MSᴛʀᴇᴀᴍ expects the input multi-aspect record stream to be stored in three files:
1. `Numerical file`: contains `,` separated Numerical Features. 
2. `Categorical file`: contains `,` separated Categorical Features. 
3. `Time File`: contains Timestamps. 

Both Numerical and Categorical files contain corresponding features of the multi-aspect record. Records should be sorted in non-decreasing order of their time stamps and the column delimiter should be `,`


## Datasets
1. [KDDCUP99](http://kdd.ics.uci.edu/databases/kddcup99/kddcup99.html)
2. [CICIDS-DoS](https://www.unb.ca/cic/datasets/ids-2018.html)
2. [UNSW-NB 15](https://www.unsw.adfa.edu.au/unsw-canberra-cyber/cybersecurity/ADFA-NB15-Datasets/)
3. [CICIDS-DDoS](https://www.unb.ca/cic/datasets/ids-2018.html)


## Citation

If you use this code for your research, please consider citing our arXiv preprint

```bibtex
@misc{bhatia2020mstream,
    title={MSᴛʀᴇᴀᴍ: Fast Streaming Multi-Aspect Group Anomaly
Detection},
    author={Siddharth Bhatia and Arjit Jain and Pan Li and Ritesh Kumar and Bryan Hooi},
    year={2020},
    eprint={2009.08451},
    archivePrefix={arXiv},
    primaryClass={cs.LG}
}

```
