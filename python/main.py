import matplotlib.pyplot as plt
import numpy as np
import os


from time import gmtime, strftime

def current_time():
    return strftime("%Y-%m-%d %H-%M-%S", gmtime())
source_dir = os.path.join(os.getcwd(), "data")

file_names = [f for f in os.listdir(source_dir) if os.path.isfile(os.path.join(source_dir, f))]

x = np.arange(10, 2000, 1, dtype=int)
y1 = [i * i for i in x]
y2 = [i * np.log2(i) for i in x]

size = []
time = []
quad = ["bubble.txt", "insertion.txt"]
nlogn = ["heap.txt", "merge.txt", "quick.txt"]

for fname in file_names:
    with open(os.path.join(source_dir, fname), "r") as f:
        for line in f:
            line = line.rstrip('\n')
            splits = line.split()
            
            size.append(int(splits[0]))
            time.append(int(splits[1]))

    plt.rcParams["figure.figsize"] = (20,20)
    plt.rcParams.update({'font.size': 30})
    if fname.lower() in quad: 
        plt.plot(np.log2(x), np.log2(y1), label="$O(N^2)$")

    if fname.lower() in nlogn:
        plt.plot(np.log2(x), np.log2(y2), label="$O(NLog(N))$")
    plt.plot(np.log2(size), np.log2(time), label="Real time")

   
    plt.xlabel('$Log(N)$')
    plt.ylabel('$Log(T(N))$')

    plt.title(fname.replace(".txt", "").capitalize() + " sort time complexity")

    plt.legend(loc="upper left")
    
    plt.savefig(os.path.join(os.getcwd(), "imgs", current_time() + fname.replace(".txt", ".png")), dpi=200)
    plt.clf()
    size.clear()
    time.clear()