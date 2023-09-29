#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>
#include "Stack.cpp"

using namespace std;

enum symbolType { OPERATOR, OPERAND, UNKNOWN };   //defining symbol types in expression
enum preced { PCPAR = 0, PADD = 10, PMULT = 15, PEXP = 20, PSIGN = 25, POPAR = 30 }; //defining precedance of operators
enum Operators { CPAR = ')', ADD = '+', SUB = '-', MULT = '*', DIV = '/', EXP = '^', OPAR = '(' };  //operators

int symbolType(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')' || symbol == '^') {
        return OPERATOR;
    }
    else if (symbol >= '0' && symbol <= '9') {
        return OPERAND;
    }
    else {
        return UNKNOWN;
    }
}
int precValue(char symbol) {
    if (symbol == CPAR)
        return PCPAR;
    else if (symbol == '+')
        return PADD;
    else if (symbol == '-')
        return PADD;
    else if (symbol == '*')
        return PMULT;
    else if (symbol == '^')
        return PEXP;
    else if (symbol == '(')
        return PCPAR;
    else if (symbol == '/')
        return 12;

    return -1;
}
int cmpPrec(char oprStk, char oprInp) {
    //cout<< "onstack: "<<oprStk<<"  "<<precValue(oprStk)<<endl;
    //cout<< "oninput: "<<oprInp<<"  "<<precValue(oprInp)<<endl;
    if (precValue(oprStk) > precValue(oprInp)) {
        return 1;
    }
    else if (precValue(oprStk) < precValue(oprInp)) {
        return -1;
    }
    else {
        return 0;
    }
}
int associativity(char opr) {
    if (opr == '+' || opr == '-') {
        return 1;
    }
    else {
        return 0;
    }
}
int toPostfix(string infix, string& postfix) {
    double num;
    bool multiply = false;
    char opr;
    Stack <char> oprStk;
    stringstream ss(infix);
    ss.seekg(0, ios::beg);
    while (!ss.eof()) {
        if (symbolType(ss.peek()) == OPERATOR) {
            if (oprStk.isEmpty()) {
                if (ss.peek() == '(' && multiply == true) {
                    oprStk.push('*');
                }
                ss >> opr;
                oprStk.push(opr);
            }
            else {
                if (ss.peek() == '(' && multiply == true) {
                    oprStk.push('*');
                    ss >> opr;
                    oprStk.push(opr);
                }
                else if (ss.peek() == ')') {
                    while (!oprStk.isEmpty() && oprStk.peep() != '(') {
                        postfix = postfix + oprStk.pop() + " ";
                    }
                    oprStk.pop();
                }
                else {
                    ss >> opr;
                    while (!oprStk.isEmpty() && cmpPrec(oprStk.peep(), opr) != -1) {
                        postfix = postfix + oprStk.pop() + " ";
                    }
                    oprStk.push(opr);
                }
            }
            multiply = false;
        }
        else if (symbolType(ss.peek()) == OPERAND) {
            multiply = true;
            ss >> num;
            postfix = postfix + std::to_string(num) + " ";
        } /*else if(symbolType(ss.peek()) == UNKNOWN){
            ss.seekg(1,ios::cur);
        } */else if (symbolType(ss.peek()) == UNKNOWN) {
            return -1;
        }
    }
    while (!oprStk.isEmpty()) {
        if (oprStk.peep() == ')' || oprStk.peep() == '(')
            oprStk.pop();
        else {
            postfix = postfix + oprStk.pop() + ' ';
        }
    }
    oprStk.empty();
    return 0;

}

int evaluate(string  postfix) {
    Stack<double> oprStk;
    stringstream ss(postfix);
    double op1, op2;
    char opr;
    while (!ss.eof()) {
        if (symbolType(ss.peek()) == OPERAND) {
            ss >> op1;
            oprStk.push(op1);
        }
        else if (symbolType(ss.peek()) == OPERATOR) {
            op1 = (double)oprStk.pop();
            op2 = (double)oprStk.pop();
            ss >> opr;
            int as = associativity(opr);
            switch (opr)
            {
            case ADD: {
                oprStk.push(op2 + op1);
                break;
            }
            case SUB: {
                oprStk.push(op2 - op1);
                break;
            }
            case MULT: {
                oprStk.push(op2 * op1);
                break;
            }
            case DIV: {
                oprStk.push(op2 / op1);
                break;
            }
            case EXP: {
                oprStk.push(pow(op2, op1));
                break;
            }
            }
        }
        else if (ss.peek() == ' ') {
            ss.seekg(1, ios::cur);
        }
    }
    return oprStk.pop();
}

int main()
{
    string infix, postfix;
    do {
        postfix.clear();
        cout << "Simple Calculator. Press X to exit" << endl;
        cout << "Enter expression" << endl;
        cin >> infix;
        int p = toPostfix(infix, postfix);
        cout << "Infix: " << infix << endl;
        cout << "Postfix: " << postfix << endl;
        cout << "Result: " << evaluate(postfix) << endl;

        if (infix == "x" || infix == "X") {
            cout << "Thank you for using our calculator" << endl;
        }
        system("pause");
        system("cls");
    } while (infix != "x" && infix != "X");
    return 0;
}
