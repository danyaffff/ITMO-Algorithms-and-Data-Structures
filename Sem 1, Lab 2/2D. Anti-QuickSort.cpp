#include <fstream>
#include <vector>
using namespace std;
 
int main() {
    int ArraySize;
    ifstream fin("antiqs.in");
    fin >> ArraySize;
    fin.close();
    vector<int> Array(ArraySize);
    for (int i = 0; i < ArraySize; i++) {
        Array[i] += i + 1;
    }
    for (int i = 2; i < ArraySize; i++) {
        int temp = Array[i];
        Array[i] = Array[i / 2];
        Array[i / 2] = temp;
    }
    ofstream fout("antiqs.out");
    for (int i = 0; i < ArraySize; i++) {
        fout << Array[i] << " ";
    }
    fout.close();
}
