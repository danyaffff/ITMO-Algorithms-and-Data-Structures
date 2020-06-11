#include <vector>
#include <fstream>
using namespace std;
 
class Number {
public:
    string Key, Value;
    Number *Next, *NextLink, *PrevLink;
 
    Number(string Key, string Value, Number* PreviousElement, Number* NextElement) {
        NextLink = NextElement;
        PrevLink = PreviousElement;
        Next = nullptr;
        this->Key = Key;
        this->Value = Value;
    }
};
 
class LinkedHashMap {
    const unsigned int Size = 10000;
    vector<Number*> Table;
    Number *Header, *PrevLink, *NextLink;
    
    int hash(string& Value) {
        unsigned long long Hash = 0;
        for (int i = (int)Value.size() - 1; i >= 0; i--)
            Hash = (Hash * 887 + Value[i]) % 10000;
        return static_cast<int> (Hash);
    }
   
    Number* getfromtable(string &Key) {
        Number* Current = Table[hash(Key)];
        while (Current != nullptr) {
            if (Current->Key == Key)
                return Current;
            Current = Current->Next;
        }
        return nullptr;
    }
 
public:
    LinkedHashMap() {
        Table.resize(Size);
        NextLink = nullptr;
        PrevLink = nullptr;
        Header = new Number("none", "none", nullptr, nullptr);
        Header->PrevLink = Header;
        Header->NextLink = Header;
    }
 
    void add(string &Key, string &Value) {
        Number* Check = getfromtable(Key);
        if (Check != nullptr) {
            Check->Value = Value;
            return;
        }
        int Hash = hash(Key);
        Number* Current = new Number(Key, Value, Header->PrevLink, Header);
        Header->PrevLink->NextLink = Current;
        Current->Next = Table[Hash];
        Table[Hash] = Current;
        Header->PrevLink = Current;
    }
 
    string next(string &Key) {
        Number* Current = getfromtable(Key);
        return Current != nullptr ? Current->NextLink->Value : "none";
    }
 
    string prev(string &Key) {
        Number* Current = getfromtable(Key);
        return Current != nullptr ? Current->PrevLink->Value : "none";
    }
 
    string get(string &Key) {
        Number* Current = getfromtable(Key);
        return Current != nullptr ? Current->Value : "none";
    }
 
    void remove(string &Key) {
        int Hash = hash(Key);
        Number* Current = Table[Hash];
        Number* PrevLink = nullptr;
        while (Current != nullptr) {
            if (Current->Key == Key) {
                Current->NextLink->PrevLink = Current->PrevLink;
                Current->PrevLink->NextLink = Current->NextLink;
                if (PrevLink == nullptr) {
                    Table[Hash] = Current->Next;
                }
                else {
                    PrevLink->Next = Current->Next;
                    Current->Next = nullptr;
                }
                return;
            }
            PrevLink = Current;
            Current = Current->Next;
        }
    }
};
 
int main() {
    LinkedHashMap LinkedHashMap;
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");
    while (!fin.eof()) {
        string Command, Key;
        fin >> Command >> Key;
        if (Command == "put") {
            string Value;
            fin >> Value;
            LinkedHashMap.add(Key, Value);
        }
        if (Command == "delete")
            LinkedHashMap.remove(Key);
        if (Command == "get")
            fout << LinkedHashMap.get(Key) << '\n';
        if (Command == "prev")
            fout << LinkedHashMap.prev(Key) << '\n';
        if (Command == "next")
            fout << LinkedHashMap.next(Key) << '\n';
    }
}
