#include <iostream>
#include <vector>
#include <fstream>

class Stack {
    std::vector<int> stack;
    int size = 0;
    
public:
    Stack(unsigned long stackSize) {
        stack.resize(stackSize);
    }
    
    void push(int number) {
        stack[++size] = number;
    }
    
    int pop() {
        return stack[size--];
    }
    
    int result(int a, char operation, int b) {
        if (operation == '+') {
            return a + b;
        }
        if (operation == '-') {
            return a - b;
        }
        if (operation == '*') {
            return a * b;
        } else {
            return 0;
        }
    }
};
 
int main() {
    std::string term;
    std::ifstream fin("postfix.in");
    getline(fin, term);
    fin.close();
    Stack stack(term.size());
    for (char & element : term) {
        if (element == ' ')
            continue;
        if (isdigit(element)) {
            stack.push(element - '0');
        } else {
            stack.push(stack.result(stack.pop(), element, stack.pop()));
        }
    }
    std::ofstream fout("postfix.out");
    fout << stack.pop();
    fout.close();
}
