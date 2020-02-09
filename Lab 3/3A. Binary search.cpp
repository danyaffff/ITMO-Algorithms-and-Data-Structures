#include <fstream>
using namespace std;
 
int lowsearch(int* Array, int Request, int Left, int Right) {
    int Mid;
    while (Left < Right) {
        Mid = (Left + Right) / 2;
        if (Array[Mid] < Request) {
            Left = Mid + 1;
        } else {
            Right = Mid;
        }
    }
    if (Array[Right] != Request) {
        return -2;
    } else {
        return Right;
    }
}
 
int highsearch(int* Array, int Request, int Left, int Right) {
    int Mid;
    while (Left < Right) {
        Mid = (Left + Right) / 2;
        if (Mid == Left) {
            Mid++;
        }
        if (Array[Mid] <= Request) {
            Left = Mid;
        } else {
            Right = Mid - 1;
        }
    }
    if (Array[Right] != Request) {
        return -2;
    }
    else {
        return Right;
    }
}
  
int main() {
    ifstream fin("binsearch.in");
    int ArraySize, NumberOfRequests, Request, ArrayOfNumbers[100000];
    fin >> ArraySize;
    for (int i = 0; i < ArraySize; i++) {
        fin >> ArrayOfNumbers[i];
    }
    fin >> NumberOfRequests;
    ofstream fout("binsearch.out");
    for (int i = 0; i < NumberOfRequests; i++) {
        fin >> Request;
        fout << lowsearch(ArrayOfNumbers, Request, 0, ArraySize - 1) + 1 << " " << highsearch(ArrayOfNumbers, Request, 0, ArraySize - 1) + 1 << endl;
    }
    fin.close();
    fout.close();
}
