//DONT CHANGE
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
    if (c == "\\/") // acts as and since its flipped
        return 3;
    else if (c == "/\\") //acts as or since its flipped
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
    int i = 0;
    while (i < infix.length()) {
        if (infix[i]== '~') {
            prefix +=infix[i];
        } else if (infix[i] != '/' && infix[i] != '\\' && !isOperator2(infix.substr(i,1)) && !isPar(infix.substr(i,1))){ //|| (infix[i] >= 'A' && infix[i] <= 'Z')) 
            cout<<infix.substr(i)<<endl;
            int right = (infix.substr(i)).find("(");
            int left = (infix.substr(i)).find(")");
            int backslash = (infix.substr(i).find("\\"));
            int forwardslash = infix.substr(i).find("/");
            if (left == -1) 
                left +=1000;
            if (right == -1) 
                right +=1000;
            if (backslash == -1) 
                backslash+=1000;
            if (forwardslash==-1)
                forwardslash+=1000;
            if (forwardslash == 999 && backslash == 999 && left == 999 && right == 999) {
                prefix += infix.substr(i);
                i = i + (infix.substr(i)).length();
                
            } else {
                int min1 = min(right, left);
                int min2 = min(backslash, forwardslash);
                int minimum = min(min1, min2);
                cout<<"min "<<minimum<<endl;
                prefix += infix.substr(i, minimum);
                cout<<"PRE "<<prefix<<endl;
                string pre = infix.substr(i, minimum);
                int len = pre.length();
                cout<<"len "<<len<<endl;
                i = i + len;
            }
            //i = i + 2;
        }
        else if (infix[i] == '(') {
            string s1;
            s1 += infix[i];
            s.push(s1);
            i = i + s.top().length();
        }
        else if (infix[i] == ')') {
            while ((s.top() != "(") && (!s.empty())) {
                prefix += s.top();
                s.pop();
            }

            if (s.top() == "(") {
                s.pop();
            }
            i = i + 1;
        }
        else if (isOperator(infix.substr(i,2))) {
            string prec = infix.substr(i,2);
            if (s.empty()) {
                s.push(infix.substr(i,2));
                i = i + s.top().length();
            }
            else {
                /*
                string top = s.top();
                s.pop();
                string second = s.top();
                s.push(top);
                string topTwo = top + second;
                //topTwo.push_back(top);
                //topTwo.push_back(second);
                */
                if (precedence(prec) > precedence(s.top())) {
                    s.push(prec);
                }
                else if ((precedence(prec) == precedence(s.top()))
                    && (prec == "\\/")) {
                    while ((precedence(prec) == precedence(s.top()))
                        && ((infix.substr(i,2)) == "\\/")) {
                        prefix += s.top();
                        i += s.top().length();
                        s.pop();
                    }
                    s.push(prec);
                }
                else if (precedence(prec) == precedence(s.top())) {
                    s.push(prec);
                    i += s.top().length();
                }
                else {
                    while ((!s.empty()) && (precedence(prec) < precedence(s.top()))) {
                        prefix += s.top();
                        i+= s.top().length();
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