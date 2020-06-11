#include <vector>
#include <fstream>
using namespace std;
  
class Number {
    int Hash;
public:
    int Value;
    Number* Next;
  
    Number(int Hash, int Value) {
        this->Hash = Hash;
        this->Value = Value;
        Next = nullptr;
    }
};
  
class HashSet {
    const int Size = 10000;
    vector<Number*> Table;
      
    int hashing(int Value) {
        Value = abs(Value) % Size;
        return Value;
    }
      
    Number* get(int GettingValue) {
        Number* Current = Table[hashing(GettingValue)];
        while (Current != nullptr) {
            if (Current->Value == GettingValue) {
                return Current;
            }
            Current = Current->Next;
        }
        return nullptr;
    }
public:
    HashSet() {
        Table.resize(Size);
    }
      
    void add(int Value) {
        if (exists(Value)) {
            return;
        }
        int Hash = hashing(Value);
        Number* Current = new Number(Hash, Value);
        Current->Next = Table[Hash];
        Table[Hash] = Current;
    }
  
    bool exists(int Value) {
        return (get(Value) != nullptr);
    }
  
    void remove(int Value) {
        int Hash = hashing(Value);
        Number* Current = Table[Hash];
        Number* Previous = nullptr;
        while (Current != nullptr) {
            if (Current->Value == Value) {
                if (Previous == nullptr)
                    Table[Hash] = Current -> Next;
                else {
                    Previous->Next = Current -> Next;
                    Current->Next = nullptr;
                }
                return;
            }
            Previous = Current;
            Current = Current->Next;
        }
    }
};
  
int main() {
    HashSet Set;
    ifstream fin("set.in");
    ofstream fout("set.out");
    while (!fin.eof()) {
        string Command;
        int Value;
        fin >> Command >> Value;
        if (Command == "insert")
            Set.add(Value);
        if (Command == "delete")
            Set.remove(Value);
        if (Command == "exists")
            fout << (Set.exists(Value) ? "true" : "false") << '\n';
    }
}
