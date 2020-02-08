#include <fstream>
using namespace std;
 
int main() {
    int ArraySize;
    ifstream fin("sortland.in");
    fin >> ArraySize;
    double Min, Mid, Max, Array[ArraySize], SortArray[ArraySize];
    for (int i = 0; i < ArraySize; i++) {
        fin >> Array[i];
        SortArray[i] = Array[i];
    }
    fin.close();
    for (int i = 0; i < ArraySize - 1; i++) {
        for (int j = 0; j < ArraySize - i - 1; j++) {
            if (SortArray[j] > SortArray[j + 1]) {
                swap(SortArray[j], SortArray[j + 1]);
            }
        }
    }
    Min = SortArray[0];
    Mid = SortArray[(ArraySize - 1) / 2];
    Max = SortArray[ArraySize - 1];
    for (int i = 0; i < ArraySize; i++) {
        if (Min == Array[i]) {
            Min = ++i;
            break;
        }
    }
    for (int i = 0; i < ArraySize; i++) {
        if (Mid == Array[i]) {
            Mid = ++i;
            break;
        }
    }
    for (int i = 0; i < ArraySize; i++) {
        if (Max == Array[i]) {
            Max = ++i;
            break;
        }
    }
    ofstream fout("sortland.out");
    fout << Min << " " << Mid << " " << Max;
    fout.close();
}
