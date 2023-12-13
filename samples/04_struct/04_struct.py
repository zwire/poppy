from ctypes import *
from random import *

class Child(Structure):
  _fields_ = [
    ('val0', c_double),
    ('val1', c_char * 32),
  ]

class Parent(Structure):
  _fields_ = [
    ('val0', c_int32),
    ('val1', Child * 4),
  ]

def py2c():
  p = Parent(int(uniform(-10, 10)))
  for i in range(3):
    p.val1[i] = Child(uniform(-10, 10), f"random: {random()}".encode("utf-8"))
  return p
