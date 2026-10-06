from pathlib import Path
import csv
import subprocess
import sys

ROOT = Path(__file__).resolve().parent.parent
CODE = ROOT / "code"
CPP_SOURCE = CODE / "cpp_slicing.cpp"
CPP_BINARY = CODE / "cpp_slicing"
CPP_CSV = CODE / "cpp_slice.csv"
NUMPY_CSV = CODE / "numpy_slice.csv"

subprocess.run([
    "g++", "-std=c++17", "-O2", str(CPP_SOURCE), "-o", str(CPP_BINARY)
], check=True)
subprocess.run([str(CPP_BINARY), str(CPP_CSV)], check=True)
subprocess.run([sys.executable, str(CODE / "numpy_slicing.py")], check=True)


def read_csv(path: Path):
    with path.open(newline="") as f:
        return [[int(x) for x in row] for row in csv.reader(f)]

numpy_result = read_csv(NUMPY_CSV)
cpp_result = read_csv(CPP_CSV)

print("\nComparison")
print("NumPy:", numpy_result)
print("C++:  ", cpp_result)
print("MATCH:", numpy_result == cpp_result)

if numpy_result != cpp_result:
    raise SystemExit("ERROR: NumPy and C++ results differ")
