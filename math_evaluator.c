#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 100

int is_operator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

int is_number(char ch) {
  return isdigit(ch) || ch == '.';
}

double evaluate(char* expression) {
  // Stack to store operands and operators
  double stack[MAX_EXPRESSION_LENGTH];
  int top = -1;

  for (int i = 0; expression[i] != '\0'; i++) {
    char ch = expression[i];

    // Skip whitespaces
    if (isspace(ch)) {
      continue;
    }

    // Push numbers onto the stack
    if (is_number(ch)) {
      double value = 0.0;
      int decimal_seen = 0;
      double decimal_place = 1.0;
      while (is_number(ch)) {
        if (ch == '.') {
          decimal_seen = 1;
        } else {
          value = value * 10 + (ch - '0');
          if (decimal_seen) {
            decimal_place /= 10;
          }
        }
        ch = expression[++i];
      }
      i--;  // Backtrack one step to process the next character
      stack[++top] = value * decimal_place;
    } else if (is_operator(ch)) {
      // Pop operands and apply the operator
      if (top < 1) {
        printf("Error: Malformed expression.\n");
        return NAN;
      }
      double operand2 = stack[top--];
      double operand1 = stack[top--];
      switch (ch) {
        case '+':
          stack[++top] = operand1 + operand2;
          break;
        case '-':
          stack[++top] = operand1 - operand2;
          break;
        case '*':
          stack[++top] = operand1 * operand2;
          break;
        case '/':
          if (operand2 == 0) {
            printf("Error: Division by zero.\n");
            return NAN;
          }
          stack[++top] = operand1 / operand2;
          break;
        case '^':
          stack[++top] = pow(operand1, operand2);
          break;
      }
    } else if (isalpha(ch)) {
      // Not supported (variables)
      printf("Error: Variables not supported.\n");
      return NAN;
    } else {
      printf("Error: Invalid character in expression.\n");
      return NAN;
    }
  }


  if (top != 0) {
    printf("Error: Malformed expression.\n");
    return NAN;
  }

  return stack[top];
}

int main() {
  char expression[MAX_EXPRESSION_LENGTH];

  while (1) {
    printf("Enter expression (or 'q' to quit): ");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);

    if (expression[0] == 'q' && expression[1] == '\n') {
      break;
    }

    double result = evaluate(expression);
    if (!isnan(result)) {
      printf("Result: %.2lf\n", result);
    }
  }

  return 0;
}
