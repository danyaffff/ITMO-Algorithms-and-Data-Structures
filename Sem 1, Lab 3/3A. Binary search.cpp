#include <fstream>
using namespace std;
 
int lowSearch(int* array, int request, int left, int right) {
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
 
int highSearch(int* array, int request, int left, int right) {
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
    int size;
    int requests;
    int request; 
 
    ifstream fin("binsearch.in");
    fin >> size;
    for (int i = 0; i < size; i++) {
        fin >> array[i];
    }
    fin >> requests;
    ofstream fout("binsearch.out");
    for (int i = 0; i < requests; i++) {
        fin >> request;
        fout << lowSearch(array, request, 0, size - 1) + 1 << " " << highSearch(array, request, 0, size - 1) + 1 << endl;
    }
    fin.close();
    fout.close();
}
