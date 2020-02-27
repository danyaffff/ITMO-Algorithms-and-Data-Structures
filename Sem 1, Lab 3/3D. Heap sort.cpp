#include <fstream>
using namespace std;
 
void siftdown(int* Array, int ArraySize, int i) {
    int Left, Right, Largest;
    Left = 2 * i + 1;
    Right = 2 * i + 2;
    Largest = i;
    if (Left < ArraySize && Array[Left] > Array[Largest]) {
        Largest = Left;
    }
    if (Right < ArraySize && Array[Right] > Array[Largest]) {
        Largest = Right;
    }
    if (Largest != i) {
        swap(Array[i], Array[Largest]);
        siftdown(Array, ArraySize ,Largest);
    }
}
 
void heapsort(int* Array, int ArraySize) {
    for (int i = ArraySize / 2 - 1; i >= 0; i--) {
        siftdown(Array, ArraySize, i);
    }
    for (int i = ArraySize - 1; i >= 0; i--) {
        swap(Array[0], Array[i]);
        siftdown(Array, i, 0);
    }
}
 
int main() {
    int Array[100000], ArraySize;
    ifstream fin("sort.in");
    fin >> ArraySize;
    for (int i = 0; i < ArraySize; i++) {
        fin >> Array[i];
    }
    fin.close();
    heapsort(Array, ArraySize);
    ofstream fout("sort.out");
    for (int i = 0; i < ArraySize; i++) {
        fout << Array[i] << " ";
    }
    fout.close();
}
