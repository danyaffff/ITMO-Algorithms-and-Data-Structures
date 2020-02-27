#include <fstream>
using namespace std;
 
long long InvCounter = 0;
 
void merge(int* Array, int Low, int High, int Mid) {
    int Index = Low, EMid = Mid + 1, NewArrayIndex = Low, NewArray[100000];
    while (Index <= Mid && EMid <= High) {
        if (Array[Index] <= Array[EMid]) {
            NewArray[NewArrayIndex] = Array[Index];
            NewArrayIndex++;
            Index++;
        } else {
            NewArray[NewArrayIndex] = Array[EMid];
            NewArrayIndex++;
            EMid++;
            InvCounter += Mid - Index + 1;
        }
    }
    for (Index; Index <= Mid; Index++, NewArrayIndex++) {
        NewArray[NewArrayIndex] = Array[Index];
    }
    for (EMid; EMid <= High; EMid++, NewArrayIndex++) {
        NewArray[NewArrayIndex] = Array[EMid];
    }
     
    for (Index = Low; Index < NewArrayIndex; Index++) {
        Array[Index] = NewArray[Index];
    }
}
 
void mergesort (int* Array, int Low, int High) {
    if (Low < High) {
        int Mid = (Low + High) / 2;
        mergesort(Array, Low, Mid);
        mergesort(Array, Mid + 1, High);
        merge(Array, Low, High, Mid);
    }
}
 
int main() {
    int ArraySize;
    ifstream fin("inversions.in");
    fin >> ArraySize;
    int Array[100000], Low = 0, High = ArraySize - 1;
    for (int i = 0; i < ArraySize; i++) {
        fin >> Array[i];
    }
    fin.close();
    mergesort(Array, Low, High);
    ofstream fout("inversions.out");
    fout << InvCounter;
    fout.close();
}
