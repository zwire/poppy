import numpy as np

def echo(obj):
  return obj

def make_buffer():
  return np.eye(2, 3)

def make_tuple():
  return "str", 10, 0.1

def make_list():
  return [ "str", 10, 0.1 ]

def make_dict():
  return { "a": "str", "b": 10, "c": 0.1 }
