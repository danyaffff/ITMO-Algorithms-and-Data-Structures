#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
   
class Node {
public:
    int Data;
    Node *Prev, *Left, *Right;
};
   
class Tree {
    Node *Root = nullptr;
public:
    void insert(int Value) {
        Node *NewNode = new Node;
        Node *Current = Root;
        if (exists(Value)) return;
        NewNode->Data = Value;
        NewNode->Prev = NewNode->Left = NewNode->Right = nullptr;
        while (Current != nullptr) {
            NewNode->Prev = Current;
            if (NewNode->Data < Current->Data) Current = Current->Left;
            else Current = Current->Right;
        }
        if (NewNode->Prev == nullptr) Root = NewNode;
        else if (NewNode->Data < NewNode->Prev -> Data) NewNode->Prev -> Left = NewNode;
        else NewNode->Prev->Right = NewNode;
    }
      
    void remove(int Value) {
        Node *Node1, *Node2;
        Node *deleted = search(Value);
        if (deleted == nullptr) return;
        if (deleted->Left == nullptr || deleted->Right == nullptr) Node1 = deleted;
        else Node1 = next(Value);
        if (Node1->Left != nullptr) Node2 = Node1->Left;
        else Node2 = Node1->Right;
        if (Node2 != nullptr) Node2->Prev = Node1->Prev;
        if (Node1->Prev == nullptr) Root = Node2;
        else if (Node1 == Node1->Prev->Left) Node1->Prev->Left = Node2;
        else Node1->Prev->Right = Node2;
        if (Node1 != deleted) deleted->Data = Node1->Data;
        delete Node1;
    }
      
    Node* search(int Value) {
        Node *Current = Root;
        while (Current != nullptr && Value != Current->Data)
            if (Value < Current->Data) Current = Current->Left;
            else Current = Current->Right;
        return Current;
    }
      
    bool exists(int Value) {
        return search(Value) != nullptr;
    }
      
    Node* next(int Value) {
        Node *Current = Root, *Next = nullptr;
        while (Current != nullptr)
            if (Current->Data > Value) {
                Next = Current;
                Current = Current->Left;
            }
            else Current = Current->Right;
        return Next;
    }
      
    Node* prev(int Value) {
        Node *Current = Root, *Prev = nullptr;
        while (Current != nullptr)
            if (Current->Data < Value) {
                Prev = Current;
                Current = Current->Right;
            }
            else Current = Current->Left;
        return Prev;
    }
};
   
int main() {
    Tree tree;
    int Value;
    string Command;
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");
    while (fin >> Command >> Value) {
        if (Command == "insert") tree.insert(Value);
        if (Command == "delete") tree.remove(Value);
        if (Command == "exists") {
            if (tree.search(Value)) fout << "true\n";
            else fout << "false\n";
        }
        if (Command == "next") {
            if (tree.next(Value) == nullptr) fout << "none\n";
            else fout << tree.next(Value) -> Data << "\n";
        }
        if (Command == "prev") {
            if (tree.prev(Value) == nullptr) fout << "none\n";
            else fout << tree.prev(Value) -> Data << "\n";
        }
    }
    fin.close();
    fout.close();
}
