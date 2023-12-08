import numpy as np

def c2py(mat: np.ndarray):
  print("------ C++ -> Python ------")
  print(mat)
  print()

def py2c() -> np.ndarray:
  mat = np.zeros((4, 7))
  mat[0, 0] = 0.1
  mat[0, 2] = 8
  mat[3, 2] = -2
  mat[1, 1] = 3.2
  mat[2, 3] = 0.3
  return mat
