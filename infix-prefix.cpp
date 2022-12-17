#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

bool isOperator(string c)
{
    if (c == "/\\" || c == "\\/") {
        return true;
    }
    else {
        return false;
    }
}
bool isOperator2(string c)
{
    if (c == "~") {
        return true;
    } else {
        return false;
    }
}

bool isPar(string c) {
    if (c == ")" || c == "(") {
        return true;
    } else {
        return false;
    }
}

int precedence(string c)
{
    if (c == "\\/") // acts as /\ operator since its flipped
        return 3;
    else if (c == "/\\") //acts as \/ operator since its flipped
        return 2;
    else if (c == "~")
        return 1;
    else
        return -1;
}

string InfixToPrefix(stack<string> s, string infix)
{
    string prefix;
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i]=='~') {
            prefix +=infix[i];
        // adding variable to prefix
        } else if (infix[i] != '/' && infix[i] != '\\' && infix[i] != '~' && !isPar(infix.substr(i,1))){ 
            prefix += infix[i];
        }
        else if (infix[i] == '(') {
            string s1;
            s1 += infix[i];
            s.push(s1);
            //i = i + s.top().length();
        }
        else if (infix[i] == ')') {
            while ((s.top() != "(") && (!s.empty())) {
                
                prefix +=  s.top() ;
                
                s.pop();
            }

            if (s.top() == "(") {
                s.pop();
            }
            //i = i + 1;
        }
        else if (isOperator(infix.substr(i,2)) || isOperator2(infix.substr(i,1))) {
            int index1;
            if (isOperator(infix.substr(i,2))) {
                index1 = 2;
            } else {
                index1 = 1;
            }
            string prec = infix.substr(i,index1);
            if (s.empty()) {
                s.push(infix.substr(i,index1));
                //i +=1;
            }
            else {
                if (precedence(prec) > precedence(s.top())) {
                    s.push(prec);
                }
                else if ((precedence(prec) == precedence(s.top()))
                    && (prec == "\\/")) {
                    while ((precedence(prec) == precedence(s.top()))
                        && ((infix.substr(i,index1)) == "\\/")) {
                        
                        prefix += s.top();
                        //i += 1;
                        s.pop();
                    }
                    s.push(prec);
                }
                else if (precedence(prec) == precedence(s.top())) {
                    s.push(prec);
                    //i += 1;
                }
                else {
                    while ((!s.empty()) && (precedence(prec) < precedence(s.top()))) {
                        
                        prefix += s.top();
                        //i+= 1;
                        s.pop();
                    }
                    s.push(prec);
                }
            }
            
        }
    }

    while (!s.empty()) {
        prefix += s.top();
        s.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main()
{

    string infix, prefix;
    cout << "Enter a Infix Expression :" << endl;
    cin >> infix;
    stack<string> stack;
    cout << "INFIX EXPRESSION: " << infix << endl;
    prefix = InfixToPrefix(stack, infix);
    cout << endl
         << "PREFIX EXPRESSION: " << prefix << endl;

    return 0;
}
