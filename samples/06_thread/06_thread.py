def multiply(a: int, b: int) -> int:
  print("------ C++ -> Python ------")
  print("Will compute", a, "times", b)
  print()
  c = 0
  for i in range(0, a):
    c = c + b
  return c
