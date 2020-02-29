#include <iostream>
#include <fstream>
#include <vector>
  
class Stack {
    std::vector<int> Stack;
    int size = 0;
    
public:
    Stack(int stackSize) {
        stack.resize(stackSize + 1);
    }
    
    void push(int number) {
        stack[size++] = number;
    }
    
    int pop() {
        return stack[--size];
    }
};
   
int main() {
    int stackSize;
    std::ifstream fin("stack.in");
    fin >> StackSize;
    Stack stack(stackSize);
    std::ofstream fout("stack.out");
    for (int i = 0; i < stackSize; i++) {
        std::string command;
        fin >> command;
        if (command == "+") {
            int number;
            fin >> number;
            s.push(number);
        } else {
            fout << s.pop() << std::endl;
        }
    }
    fin.close();
    fout.close();
}
