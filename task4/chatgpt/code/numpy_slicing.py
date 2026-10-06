from pathlib import Path
import csv
import numpy as np
import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parent.parent
IMAGE_PATH = ROOT / "images" / "slicing_comparison.png"
CSV_PATH = ROOT / "code" / "numpy_slice.csv"

# 6 x 8 matrix with values 1..48.
matrix = np.arange(1, 49).reshape(6, 8)

# The NumPy operation being demonstrated.
sliced = matrix[1:5:2, 2:7:2]

with CSV_PATH.open("w", newline="") as f:
    writer = csv.writer(f)
    writer.writerows(sliced.tolist())

# Highlight the elements selected by the slice on the original matrix.
mask = np.zeros_like(matrix, dtype=bool)
mask[1:5:2, 2:7:2] = True

fig, axes = plt.subplots(1, 3, figsize=(14, 4.5))
fig.suptitle("2D Matrix Slicing: NumPy vs C++", fontsize=16)

for ax, data, title in [
    (axes[0], matrix, "Original 6 × 8 matrix"),
    (axes[1], matrix, "Elements selected by matrix[1:5:2, 2:7:2]"),
    (axes[2], sliced, "NumPy slice result"),
]:
    ax.imshow(data, cmap="Blues", aspect="auto")
    ax.set_title(title)
    ax.set_xticks(range(data.shape[1]))
    ax.set_yticks(range(data.shape[0]))
    for r in range(data.shape[0]):
        for c in range(data.shape[1]):
            ax.text(c, r, str(data[r, c]), ha="center", va="center")

# Visually mark selected elements in the middle panel.
for r in range(matrix.shape[0]):
    for c in range(matrix.shape[1]):
        if mask[r, c]:
            rect = plt.Rectangle((c - 0.48, r - 0.48), 0.96, 0.96,
                                 fill=False, linewidth=3)
            axes[1].add_patch(rect)

fig.text(0.5, 0.02, "C++ produces the same 2 × 3 values: 11 13 15 / 27 29 31",
         ha="center", fontsize=11)
fig.tight_layout(rect=[0, 0.06, 1, 0.93])
fig.savefig(IMAGE_PATH, dpi=180, bbox_inches="tight")
plt.close(fig)

print("NumPy original:")
print(matrix)
print("\nNumPy slice matrix[1:5:2, 2:7:2]:")
print(sliced)
print(f"\nWrote {CSV_PATH}")
print(f"Wrote {IMAGE_PATH}")
