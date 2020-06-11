#include <vector>
#include <fstream>
using namespace std;
 
class Number {
public:
    string Key, Value;
    Number* Next;
 
    Number(int Hash, string Key, string Value) {
        Hash = 0;
        this->Key = Key;
        this->Value = Value;
        Next = nullptr;
    }
};
 
class HashMap {
    const int Size = 10000;
    vector<Number*> Table;
     
    int hash(string &Value) {
        unsigned long long Hash = 0;
        for (int i = (int)Value.size() - 1; i >= 0; i--)
            Hash = (Hash * 887 + Value[i]) % 10000;
        return static_cast<int> (Hash);
    }
     
    Number* getme(string &Key) {
        Number* Current = Table[hash(Key)];
        while (Current != nullptr) {
            if (Current->Key == Key)
                return Current;
            Current = Current->Next;
        }
        return nullptr;
    }
     
public:
    HashMap() {
        Table.resize(Size);
    }
     
    void add(string &Key, string &Value) {
        Number* Resetter = getme(Key);
        if (Resetter != nullptr) {
            Resetter->Value = Value;
            return;
        }
        int Hash = hash(Key);
        Number* Current = new Number(Hash, Key, Value);
        Current->Next = Table[Hash];
        Table[Hash] = Current;
    }
 
    string get(string &Key) {
        Number* Current = getme(Key);
        return Current != nullptr ? Current->Value : "none";
    }
 
    void remove(string &Key) {
        int Hash = hash(Key);
        Number* Current = Table[Hash];
        Number* Previous = nullptr;
        while (Current != nullptr) {
            if (Current->Key == Key) {
                if (Previous == nullptr)
                    Table[Hash] = Current->Next;
                else {
                    Previous->Next = Current->Next;
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
    HashMap Map;
    ifstream fin("map.in");
    ofstream fout("map.out");
    while (!fin.eof()) {
        string Command, Key;
        fin >> Command >> Key;
        if (Command == "put") {
            string Value;
            fin >> Value;
            Map.add(Key, Value);
        }
        if (Command == "delete")
            Map.remove(Key);
        if (Command == "get")
            fout << Map.get(Key) << '\n';
    }
}
