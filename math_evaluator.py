from math import cos, acos, sin, asin, tan, atan, sqrt, pow

def evaluate(expression):
  """Evaluates a mathematical expression and returns the result.

  Args:
      expression: A string representing the mathematical expression.

  Returns:
      The numerical result of the expression or None if the expression is malformed.
  """
  try:
    return eval(expression)
  except (NameError, SyntaxError):
    print("Error: Malformed expression.")
    return None

def main():
  """Main function that reads user input and evaluates expressions."""
  while True:
    expression = input("Enter expression (or 'q' to quit): ")
    if expression.lower() == 'q':
      break
    result = evaluate(expression)
    if result is not None:
      print(f"Result: {result}")

if __name__ == "__main__":
  main()
