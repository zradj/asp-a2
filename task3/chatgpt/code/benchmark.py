import argparse, time, numpy as np
from multiply import multiply

p = argparse.ArgumentParser(); p.add_argument("--size", type=int, default=500); p.add_argument("--repeats", type=int, default=5)
a = p.parse_args(); n=a.size
x=np.random.default_rng(42).random((n,n)); y=np.random.default_rng(43).random((n,n))
# warm-up
multiply(x,y)
times=[]
for _ in range(a.repeats):
    t=time.perf_counter(); z=multiply(x,y); times.append(time.perf_counter()-t)
print(f"numpy,{n},{a.repeats},{min(times):.6f},{sum(times)/len(times):.6f},{max(times):.6f},{z[0,0]:.12f}")
