#include <iostream>
#include "stack.h"
#include <sstream>

using namespace std;
using namespace cop4530;

int operators(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0; // For non-operators
}

double evaluatePostfix(const vector<string>& output) {
    Stack<double> evalStack; 

    for (const string& token : output) {
        if (isdigit(token[0])) {
            evalStack.push(stod(token)); // Convert string to double and push
        } else {
            double right = evalStack.top(); evalStack.pop(); // Pop the right operand
            double left = evalStack.top(); evalStack.pop(); // Pop the left operand
            // Perform the operation
            if (token == "+") evalStack.push(left + right);
            else if (token == "-") evalStack.push(left - right);
            else if (token == "*") evalStack.push(left * right);
            else if (token == "/") evalStack.push(left / right);
        }
    }
    
    return evalStack.top(); // Return the result
}

int main() {
    Stack<string> fixStack;
    string expression;
    vector<string> output;

    bool keepgoing = true;

    // Loops until user wants to exit
    while (keepgoing) {
        cout << "Enter infix expression (\"exit\" to quit): ";
        getline(cin, expression);

        // Exits program if user types exit
        if (expression == "exit") {
            keepgoing = false;
            break;
        }

        output.clear(); // Clear output
        fixStack.clear(); // Clear stack
        string lastInput;

        bool validExpression = true;
        bool hasLetter = false;

        for (size_t i = 0; i < expression.length(); ++i) {
            if (isspace(expression[i])) {
                continue;
            }

            string token;

            if (isalnum(expression[i]) || expression[i] == '_') {
                token.clear();
                while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                    token += expression[i++];
                }
                if (isalpha(token[0])) // Checks if the input/token contains a letter
                {
                    hasLetter = true;
                }
                output.push_back(token);
                lastInput = token;
                --i;
            } 
            else if (expression[i] == '(') {
                fixStack.push("(");
                lastInput = "(";
            } 
            else if (expression[i] == ')') {
                if (lastInput.empty() || lastInput == "+" || lastInput == "-" || lastInput == "*" || lastInput == "/") {
                    validExpression = false;
                    break;
                }
                while (!fixStack.empty() && fixStack.top() != "(") {
                    output.push_back(fixStack.top());
                    fixStack.pop();
                }
                if (fixStack.empty()) {
                    validExpression = false;
                    break;
                }
                fixStack.pop(); 
                lastInput = ")";
            } 
            
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
            {
                string op(1, expression[i]);
                if (lastInput.empty() || lastInput == "+" || lastInput == "-" || lastInput == "*" || lastInput == "/" || lastInput == "(") {
                    cout << endl;
                    cout << "Error: Missing operands in the expression" << endl; // Print error message
                    validExpression = false;
                    break;
                }
                while (!fixStack.empty() && operators(fixStack.top()) >= operators(op)) {
                    output.push_back(fixStack.top());
                    fixStack.pop();
                }
                fixStack.push(op);
                lastInput = op;
            } 
            else {
                cout << endl;
                cout << "Error: Invalid " << string(1, expression[i]) << endl;
                validExpression = false;
                break;
            }
        }

        // End of input check
        if (validExpression) {
            if (lastInput.empty() || lastInput == "+" || lastInput == "-" || lastInput == "*" || lastInput == "/" || lastInput == "(") {
                cout << endl;
                cout << "Error: Missing operand in postfix string. Unable to evaluate postfix string!" << endl; // Print error message
                validExpression = false;
            }
        }

        // Goes through and checks if there are mismatched parenthesis
        while (validExpression && !fixStack.empty()) {
            if (fixStack.top() == "(") {
                cout << endl;
                cout << "Error: Infix expression: " << expression << " has mismatched parens!" << endl; // Print error message
                validExpression = false;
                break;
            }
            output.push_back(fixStack.top());
            fixStack.pop();
        }

        // Output the postfix expression if valid
        if (validExpression) 
        {
            ostringstream finexpression; // final expression
            for (const auto& elem : output) {
                finexpression << elem << " ";
            }
            string finalExpression = finexpression.str();
            cout << endl;

            // Outputs expression
            cout << "Postfix expression: " << finalExpression << endl;

            // Seperate outputs depending on if the expression contains a letter
            if (!hasLetter)
            {
            double result = evaluatePostfix(output);
            cout << "Postfix evaluation: " << finalExpression << " = " << result << endl;  
            }
            else
            {
              cout << "Postfix evaluation: " << finalExpression << " = " << finalExpression << endl;  
            }   
        }

    }

    return 0;
}
