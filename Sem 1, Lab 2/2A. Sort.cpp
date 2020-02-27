#include <fstream>
using namespace std;
 
int ArraySize;
  
void merge(int *Array , int Low, int High, int Mid) {
    int FirstArrayIndex = Low, SecondArrayIndex = Mid + 1, MergedArrayIndex = Low, NewArray[ArraySize];
    while (FirstArrayIndex <= Mid && SecondArrayIndex <= High) {
        if (Array[FirstArrayIndex] <= Array[SecondArrayIndex]) {
            NewArray[MergedArrayIndex] = Array[FirstArrayIndex];
            MergedArrayIndex++;
            FirstArrayIndex++;
        } else {
            NewArray[MergedArrayIndex] = Array[SecondArrayIndex];
            MergedArrayIndex++;
            SecondArrayIndex++;
        }
    }
    for (FirstArrayIndex; FirstArrayIndex <= Mid; FirstArrayIndex++, MergedArrayIndex++) {
        NewArray[MergedArrayIndex] = Array[FirstArrayIndex];
    }
    for (SecondArrayIndex; SecondArrayIndex <= High; SecondArrayIndex++, MergedArrayIndex++) {
        NewArray[MergedArrayIndex] = Array[SecondArrayIndex];
    }
    for (FirstArrayIndex = Low; FirstArrayIndex < MergedArrayIndex; FirstArrayIndex++) {
        Array[FirstArrayIndex] = NewArray[FirstArrayIndex];
    }
}
  
void mergesort (int *Array, int Low, int High) {
    if (Low < High) {
        int Mid = (Low + High) / 2;
        mergesort(Array, Low, Mid);
        mergesort(Array, Mid + 1, High);
        merge(Array, Low, High, Mid);
    }
}
  
int main() {
    ifstream fin("sort.in");
    fin >> ArraySize;
    int Array[ArraySize], Low = 0, High = ArraySize - 1;
    for (int i = 0; i < ArraySize; i++) {
        fin >> Array[i];
    }
    fin.close();
    mergesort(Array, Low, High);
    ofstream fout("sort.out");
    for (int i = 0; i < ArraySize; i++) {
        fout << Array[i] << " ";
    }
    fout.close();
}
