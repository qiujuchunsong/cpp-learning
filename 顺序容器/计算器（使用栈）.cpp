#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

// 函数声明
int evaluateExpression(const string& expr);
double calculate(double operand1, char op, double operand2);

int main() {
    string expression;
    cout << "Please enter a parenthesized expression (enter 'q' to quit): " << endl;
    
    while (getline(cin, expression)) {
        if (expression == "q") break;
        
        try {
            int result = evaluateExpression(expression);
            cout << "Calculation result: " << result << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        
        cout << "Please enter the next expression (enter 'q' to quit): " << endl;
    }
    
    return 0;
}

int evaluateExpression(const string& expr) {
    stack<char> operators;    // 存储运算符的栈
    stack<int> operands;      // 存储操作数的栈
    
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        
        // 跳过空格
        if (isspace(ch)) continue;
        
        // 处理数字
        if (isdigit(ch)) {
            int num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;  // 回退一位，因为外层循环还会++i
            operands.push(num);
        }
        // 处理左括号
        else if (ch == '(') {
            operators.push(ch);
        }
        // 处理右括号，计算括号内的表达式
        else if (ch == ')') {
            // 弹出并计算，直到遇到左括号
            while (!operators.empty() && operators.top() != '(') {
                if (operands.size() < 2) {
                    throw runtime_error("Expression format error: insufficient operands");
                }
                
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                
                // 计算结果并压入栈中
                int result = calculate(operand1, op, operand2);
                operands.push(result);
            }
            
            // 弹出左括号
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            } else {
                throw runtime_error("Expression format error: unmatched parentheses");
            }
            
            // 括号处理完成后，可以将结果看作一个新的操作数
            // 这里不需要额外处理，因为结果已经在operands栈中
        }
        // 处理运算符
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // 处理优先级：乘除高于加减
            while (!operators.empty() && operators.top() != '(' && 
                  ((ch == '+' || ch == '-') || 
                   (operators.top() == '*' || operators.top() == '/'))) {
                if (operands.size() < 2) {
                    throw runtime_error("Expression format error: insufficient operands");
                }
                
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                
                int result = calculate(operand1, op, operand2);
                operands.push(result);
            }
            
            operators.push(ch);
        }
        else {
            throw runtime_error(string("Unsupported character: ") + ch);
        }
    }
    
    // 处理剩余的运算符
    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw runtime_error("Expression format error: unmatched parentheses");
        }
        
        if (operands.size() < 2) {
            throw runtime_error("Expression format error: insufficient operands");
        }
        
        int operand2 = operands.top();
        operands.pop();
        int operand1 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        
        int result = calculate(operand1, op, operand2);
        operands.push(result);
    }
    
    if (operands.size() != 1) {
        throw runtime_error("Expression format error: too many operands");
    }
    
    return operands.top();
}

double calculate(double operand1, char op, double operand2) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': 
            if (operand2 == 0) {
                throw runtime_error("Division by zero error");
            }
            return operand1 / operand2;
        default:
            throw runtime_error(string("Unsupported operator: ") + op);
    }
}
