// Thompson construction algorithm (RE to NFA)
#include <iostream>
#include <stack>
#include <list>

using namespace std;

// store from, to, and transition symbol
class Transition {
public:
    int from, to;
    char symbol;

    Transition(int from, int to, char symbol) {
        this->from = from;
        this->to = to;
        this->symbol = symbol;
    }
};

class Validator {
public:
    static bool isAlphabet(char c) {
        return true;
    }
    static bool isValidRegex(string regex) {
        return true;
    }
};

class NFA {
public:
    list<int> states;
    list<Transition*> transitions;
    int finalState = 0;

    NFA();
    NFA(int size) {
        this->setStateSize(size);
    }
    NFA(char c) {
        this->setStateSize(2);
        this->finalState = 1;
        this->transitions.push_back(new Transition(0, 1, c));
    }

    void setStateSize(int size) {
        for (int i = 0; i < size; i++)
            this->states.push_back(i);
    }

    void displayDefinition() {
        // TODO: Print NFA definition here...
        for (auto t: transitions){
            printf("%d ------ %c ------> %d\n", t->from, t->symbol, t->to);
        }
    }
};

NFA* star(NFA* operand) {

}

NFA* concat(NFA* n, NFA* m) {
    m->states.remove(0);

    // Copy new state from m to n and shift state number
    for (auto t: m->transitions){
        n->transitions.push_back(new Transition(t->from + n->states.size() - 1, t->to + n->states.size() - 1, t->symbol));
    }
    for (auto s: m->states){
        n->states.push_back(s + n->states.size() + 1);
    }
    n->finalState = n->states.size() + m->states.size() - 2;

    return n;
}

// actually this is union
NFA* U(NFA* a, NFA* b) {

}

NFA* compile(string regex) {
    if (!Validator::isValidRegex(regex)) {
        printf("[Error] Invalid regular expression\n");
        exit(1);
    }

    stack<char> operators;
    stack<NFA*> operands;
    stack<NFA*> concatStack;
    bool ccflag = false;
    char op, currentChar;
    int parenthesesCounter = 0;
    NFA* nfa1;
    NFA* nfa2;

    for (int i = 0; i < regex.length(); ++i) {
        currentChar = regex[i];
        if (Validator::isAlphabet(currentChar)) {
            operands.push(new NFA(currentChar));
            if (ccflag) {
                operators.push('.');
            } else {
                ccflag = true;
            }
        } else {
            if (currentChar == ')') {
                ccflag = false;
                if (parenthesesCounter == 0) {
                    printf("[Error] Parentheses error\n");
                    exit(1);
                } else {
                    --parenthesesCounter;
                }
                while (!operators.empty() && operators.top()) {
                    op = operators.top(); operators.pop();
                    if (op == '.') {
                        nfa2 = operands.top(); operands.pop();
                        nfa1 = operands.top(); operands.pop();
                        operands.push(concat(nfa1, nfa2));
                    } else if (op == '|') {
                        nfa2 = operands.top(); operands.pop();

                        if (!operators.empty() && operators.top() == '.') {
                            concatStack.push(operands.top()); operands.pop();
                            while (!operators.empty() && operators.top() == '.'){
                                concatStack.push(operands.top()); operands.pop();
                                operators.pop();
                            }

                            NFA* a = concatStack.top(); concatStack.pop();
                            NFA* b = concatStack.top(); concatStack.pop();
                            nfa1 = concat(a, b);

                            while (concatStack.size() > 0){
                                nfa1 = concat(nfa1, concatStack.top());
                                concatStack.pop();
                            }
                        } else {
                            nfa1 = operands.top(); operands.pop();
                        }

                        operands.push(U(nfa1, nfa2));
                    }
                }
            } else if (currentChar == '*') {
                operands.push(star(operands.top()));
                operands.pop();
                ccflag = true;
            } else if (currentChar == '(') {
                operators.push(currentChar);
                ++parenthesesCounter;
            } else if (currentChar == '|') {
                operators.push(currentChar);
                ccflag = false;
            }
        }
    }

    while (!operators.empty()){
        if (operands.empty()){
            printf("[Error] Imbalance in operands and operators");
            exit(1);
        }
        op = operators.top(); operators.pop();
        if (op == '.'){
            nfa2 = operands.top(); operands.pop();
            nfa1 = operands.top(); operands.pop();
            operands.push(concat(nfa1, nfa2));
        }
        else if (op == '|'){
            nfa2 = operands.top(); operands.pop();
            if( !operators.empty() && operators.top() == '.'){
                concatStack.push(operands.top()); operands.pop();
                while (!operators.empty() && operators.top() == '.'){
                    concatStack.push(operands.top()); operands.pop();
                    operators.pop();
                }
                NFA* a = concatStack.top(); concatStack.pop();
                NFA* b = concatStack.top(); concatStack.pop();
                nfa1 = concat(a, b);
                while (concatStack.size() > 0){
                    nfa1 =  concat(nfa1, concatStack.top());
                    concatStack.pop();
                }
            }
            else{
                nfa1 = operands.top();
                operands.pop();
            }
            operands.push(U(nfa1, nfa2));
        }
    }

    return operands.top();
}

int main() {
    printf("Enter a regular expression: ");
    string regex; cin >> regex;

    NFA* nfa = compile(regex);
    nfa->displayDefinition();

    return 0;
}