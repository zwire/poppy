import time
import numpy as np

def echo(obj):
  return obj

def echo_fail(obj):
  raise Exception("panic!")

def make_empty():
  pass

def make_buffer():
  return np.eye(2, 3, dtype=np.float32)

def make_tuple():
  return "str", 10, 0.1

def make_list():
  return [ "str", 10, 0.1 ]

def make_dict():
  return { 0: "str", 1.0: 10, "key2": 0.1 }

def heavy_task(obj):
  time.sleep(0.1)
  return obj
