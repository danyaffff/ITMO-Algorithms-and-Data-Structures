#include <iostream>
#include <fstream>
#include <vector>

class Queue {
    std::vector<int> queue;
    int left = 0;
    int right = 0;
    
public:
    Queue(int queueSize) {
        queue.resize(queueSize + 1);
    }
     
    void push(int number) {
        queue[++right] = number;
    }
     
    int pop() {
        return queue[++left];
    }
};
  
int main() {
    int queueSize;
    std::ifstream fin("queue.in");
    fin >> queueSize;
    Queue s(queueSize);
    std::ofstream fout("queue.out");
    for (int i = 0; i < queueSize; i++) {
        std::string command;
        fin >> command;
        if (command == "+") {
            int number;
            fin >> number;
            s.push(number);
        } else if (command == "-") {
            fout << s.pop() << std::endl;
        }
    }
    fin.close();
    fout.close();
}
