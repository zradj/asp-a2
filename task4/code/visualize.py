import glob
import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import BoundaryNorm, ListedColormap

# 1 -> red, 2 -> green, 3 -> blue, 4 -> yellow
cmap = ListedColormap(["red", "green", "blue", "yellow"])
norm = BoundaryNorm([0.5, 1.5, 2.5, 3.5, 4.5], cmap.N)

here = os.path.dirname(os.path.abspath(__file__))
files = sorted(glob.glob(os.path.join(here, "output_*")))
files = [f for f in files if not f.endswith(".png")]

fig, axes = plt.subplots(1, len(files), figsize=(5 * len(files), 5), squeeze=False)

for ax, path in zip(axes[0], files):
    grid = np.loadtxt(path, dtype=int, ndmin=2)
    ax.imshow(grid, cmap=cmap, norm=norm)

    # thin grid lines so each number shows up as its own square
    ax.set_xticks(np.arange(-0.5, grid.shape[1]), minor=True)
    ax.set_yticks(np.arange(-0.5, grid.shape[0]), minor=True)
    ax.grid(which="minor", color="black", linewidth=0.5)
    ax.tick_params(which="both", bottom=False, left=False,
                   labelbottom=False, labelleft=False)
    ax.set_title(os.path.basename(path))

fig.tight_layout()
fig.savefig(os.path.join(here, "output.png"), dpi=150)
