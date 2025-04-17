# Infix to Postfix Converter
A C++ program that converts mathematical infix expressions to postfix format and evaluates them using a custom templated `Stack<T>` class.

---
## Features
- Converts infix expressions to postfix
- Evaluates postfix expressions
- Custom templated stack implementation
- Handles parentheses and operator precedence
- Detects invalid expressions

---
## Build and Run

```bash
make
./in2post

## Example
Enter expression: (3 + 4) * 5
Postfix: 3 4 + 5 *
Evaluated: 35
