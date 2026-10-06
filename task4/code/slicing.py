import sys
import numpy as np

def main():
    img = []
    with open("input.txt", 'r') as f:
        # skip the row and column counts
        for line in f.readlines()[1:]:
            nums = [int(x) for x in line.strip().split()]
            img.append(nums)

    img = np.array(img)
    raw_params = input('Please input the slicing parameters (format: "row_start row_end col_start col_end"): ').split()
    params = [int(x) for x in raw_params]
    if len(params) != 4:
        print("Please input exactly the four required parameters.")
        return
    
    row_start, row_end, col_start, col_end = params
    if row_start > len(img):
        print("row_start is out of bounds")
        return
    if row_end > len(img):
        print("row_end is out of bounds")
        return
    if col_start > len(img[0]):
        print("col_start is out of bounds")
        return
    if col_end > len(img[0]):
        print("col_end is out of bounds")
        return
    if row_start > row_end:
        print("row_start must be smaller than row_end")
        return
    if col_start > col_end:
        print("col_start must smaller than col_end")
        return
    
    res = img[row_start:row_end, col_start:col_end]
    
    with open("output_py.txt", 'w') as f:
        f.write('\n'.join([' '.join(col.astype(str).tolist()) for col in res]))

if __name__ == "__main__":
    main()
