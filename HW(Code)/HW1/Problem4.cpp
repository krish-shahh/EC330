// Krish Shah, U75802512, kshah26@bu.edu

/* Course of Action:
    - 
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool legalBrackets(const string& line) {
    stack<char> bracketStack;

    for (char ch : line) {
        if (ch == '(' || ch == '{' || ch == '[') {
            bracketStack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (bracketStack.empty()) {
                return false;
            }

            char top = bracketStack.top();
            bracketStack.pop();

            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }

    return bracketStack.empty(); 
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_string>" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (legalBrackets(argv[i])) {
            cout << "legal" << endl;
        } else {
            cout << "illegal" << endl;
        }
    }

    return 0;
}

// g++ -std=c++17 Problem4.cpp -o Problem4
