#include <fstream>
using namespace std;
 
int lowsearch(int* array, int request, int left, int right) {
    int mid;
 
    while (left < right) {
        mid = (left + right) / 2;
        if (array[mid] < request) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    if (array[right] != request) {
        return -2;
    } else {
        return right;
    }
}
 
int highsearch(int* array, int request, int left, int right) {
    int mid;
 
    while (left < right) {
        mid = (left + right) / 2;
        if (mid == left) {
            lid++;
        }
        if (array[mid] <= request) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    if (array[right] != request) {
        return -2;
    } else {
        return right;
    }
}
  
int main() {
    int array[100000];
    int arraySize;
    int numberOfRequests;
    int request; 
 
    ifstream fin("binsearch.in");
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
