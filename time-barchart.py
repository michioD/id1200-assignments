import subprocess
import time
import matplotlib.pyplot as plt

N_values = [100, 1000, 10000, 100000, 1000000]
times = []

for N in N_values:
    cmd = ["./q7", str(N)]
    start = time.time()
    subprocess.run(cmd)
    end = time.time()
    times.append(end - start)

plt.figure(figsize=(10,6))
plt.bar([str(n) for n in N_values], times)
plt.xlabel("size array of floats (N)")
plt.ylabel("time taken to sum (seconds)")
plt.show()
