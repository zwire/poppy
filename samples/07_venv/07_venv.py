import sympy

def factor(formula: str) -> str:
  print("------ C++ -> Python ------")
  print(formula)
  print()
  expr = sympy.sympify(formula)
  return sympy.factor(expr)
