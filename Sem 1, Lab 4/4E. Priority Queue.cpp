#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
 
class HeapElement {
public:
    int value;
    int number;
    
    HeapElement(): value(0), number(0) {}
    HeapElement(int value, int number): value(value), number(number) {}
    
    bool operator<(const HeapElement &sifts) const {
        return this->value < sifts.value;
    }
    
    bool operator==(int searched) const {
        return this->number == searched;
    }
    
    HeapElement &operator=(int decreased) {
        this->value = decreased;
        return *this;
    }
};
 
class Queue {
    vector<HeapElement> heap;
     
    void siftUp(unsigned long i) {
        while (true) {
            unsigned long parent = i == 0 ? 0 : (i - 1) / 2;
            if (heap[i] < heap[parent]) {
                swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }
     
    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        
        if (left < heap.size() && heap[left] < heap[i]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }
     
    int find(int key) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] == key) {
                return i;
            }
        }
        return 0;
    }
 
public:
    void push(HeapElement element) {
        heap.push_back(element);
        siftUp(heap.size() - 1);
    }
     
    bool extractMin(HeapElement &minimal) {
        if (heap.empty()) {
            return false;
        }
        minimal = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        siftDown(0);
        return true;
    }
 
    void decreaseKey(int Key, int Value) {
        int i = find(Key);
        heap[i] = Value;
        siftUp(i);
    }
};
 
int main() {
    Queue queue;
    int number = 0;
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");
    
    while (!cin.eof()) {
        number++;
        string command;
        cin >> command;
        if (command == "push") {
            int value;
            cin >> value;
            queue.push(HeapElement(value, number));
        } else if (command == "extract-min") {
            HeapElement minimalKey;
            if (queue.extractMin(minimalKey)) {
                cout << minimalKey.value << endl;
            } else {
                cout << "*" << endl;
            }
        } else if (command == "decrease-key") {
            int number, value;
            cin >> number >> value;
            queue.decreaseKey(number, value);
        }
    }
}
