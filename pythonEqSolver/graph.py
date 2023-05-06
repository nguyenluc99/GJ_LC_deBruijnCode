import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def drawConvergenceLine200(b, k, rate):
# b, k, rate = 3, 2, 0.4056
    path = './rate/rate_' + str(b) + str(k) + '.txt'
    with open(path) as f:
        contents = f.readlines()
    bits, rates = list(), list()
    for c in contents[1:]:
        val = c.strip().split(':')
        if(val[2] != 'nan'):
            bits.append(int(val[0]))
            rates.append(float(val[2]))

    plt.clf()
    plt.plot(bits, rates, color='blue', label='Our rate')
    plt.ylabel('rate')
    plt.xlabel('bits')
    plt.ylim([0,1.1])
    plt.axhline(y=rate, xmin=0, xmax=1, color='red', linestyle='--', label='Original rate')
    plt.legend()
    return plt

results = [
           [3, 2, 0.4056],
           [3, 3, 0.7946],
           [4, 3, 0.6341],
           [4, 4, 0.8600],
           [4, 5, 0.9392],
           [4, 6, 0.9719],
           [5, 3, 0.4709],
           [5, 4, 0.7973],
           [5, 5, 0.9150],
           [5, 6, 0.9615],
           [5, 7, 0.9818],
           [5, 8, 0.9912],
           [5, 9, 0.9957]
          ]

for (b, k, rate) in results:
    plot = drawConvergenceLine200(b, k, rate)
    plot.savefig('figures/rateb' + str(b) + 'k' + str(k) + '.png', dpi=500)
    print("Done b=" + str(b) + ", k=" + str(k))
#     break
