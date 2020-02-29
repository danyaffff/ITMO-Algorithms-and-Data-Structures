#include <vector>
#include <fstream>
#include <iostream>
 
class Stack {
    std::vector<char> stack;
    int size = 0;
    
public:
    Stack(unsigned long stackSize) {
        stack.resize(stackSize);
    }
    
    void push(char number) {
        stack[size++] = number;
    }
    
    char pop() {
        return stack[--size];
    }
    
    char returnTop() {
        return stack[size - 1];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    int count() {
        return size;
    }
    
    int check(std::string brackets) {
        Stack stack(brackets.size());
        for (char bracket : brackets) {
            if ((stack.isEmpty() && bracket == ')') || (stack.isEmpty() && bracket == ']') || (stack.returnTop() == '(' && bracket == ']') || (stack.returnTop() == '[' && bracket == ')')) {
                return -1;
            }
            if (bracket == '(' || bracket == '[') {
                stack.push(bracket);
            }
            if ((stack.returnTop() == '(' && bracket == ')') || (stack.returnTop() == '[' && bracket == ']')) {
                stack.pop();
            }
        }
        return stack.count();
    }
};
 
int main() {
    std::ifstream fin("brackets.in");
    std::ofstream fout("brackets.out");
    std::string brackets;
    Stack stack(brackets.size());
    while (getline(fin, brackets)) {
        fout << (stack.check(brackets) == 0 ? "YES" : "NO") << std::endl;
    }
    fin.close();
    fout.close();
}
