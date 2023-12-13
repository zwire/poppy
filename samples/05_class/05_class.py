from random import *

class Hoge:
  def __init__(self) -> None:
    self.seed = uniform(0, 1)
    pass

  def get(self) -> float:
    return self.seed * uniform(-1, 1)
  
  def set(self, val) -> None:
    self.seed = val
    print("------ C++ -> Python ------")
    print(f"set value: {val}")
    print()

def new() -> Hoge:
  return Hoge()
