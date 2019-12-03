#include <fstream>
using namespace std;
 
int main() {
    int ArraySize, Array[10000];
    ifstream fin("smallsort.in");
    fin >> ArraySize;
    for (int i = 0; i < ArraySize; i++)
        fin >> Array[i];
    fin.close();
    for (int i = 0; i < ArraySize - 1; i++)
        for (int j = 0; j < ArraySize - i - 1; j++)
            if (Array[j] > Array[j + 1])
                swap(Array[j], Array[j + 1]);
    ofstream fout("smallsort.out");
    for (int i = 0; i < ArraySize; i++)
        fout << Array[i] << " ";
    fout.close();
}
