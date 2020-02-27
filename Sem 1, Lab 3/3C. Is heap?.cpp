#include <fstream>
using namespace std;
 
int main() {
    int ArraySize, Array[100000];
    ifstream fin("isheap.in");
    fin >> ArraySize;
    for (int i = 0; i < ArraySize; i++) {
        fin >> Array[i];
    }
    fin.close();
    bool Check = true;
    for (int i = 0; i < ArraySize / 2; i++) {
        if (2 * i + 1 < ArraySize) {
            if (Array[i] > Array[2 * i + 1]) {
                Check = false;
                break;
            }
        }
        if (2 * i + 2 < ArraySize) {
            if (Array[i] > Array[2 * i + 2]) {
                Check = false;
                break;
            }
        }
    }
    ofstream fout("isheap.out");
    if (Check == true) {
        fout << "YES";
    } else {
        fout << "NO";
    }
    fout.close();
}
