#include <fstream>
#include <vector>
using namespace std;
  
int danyasort(vector<int>& Array, int Low, int High, int k) {
    int Mid = (Low + High) / 2, MiddleElement = Array[Mid], i = Low, j = High;
    while (i <= j) {
        while (Array[i] < MiddleElement) {
            i++;
        }
        while (Array[j] > MiddleElement) {
            j--;
        }
        if (i <= j) {
            swap(Array[i], Array[j]);
            i++;
            j--;
        }
    }
    if (Low <= k && k <= j) {
        return danyasort(Array, Low, j, k);
    }
    if (i <= k && k <= High) {
        return danyasort(Array, i, High, k);
    }
    return Array[k];
}

int main() {
    ifstream fin("kth.in");
    int n, k, A, B, C;
    fin >> n >> k >> A >> B >> C;
    k--;
    vector<int>Array(n);
    for (int i = 0; i < 2; i++) {
        fin >> Array[i];
    }
    fin.close();
    for (int i = 2; i < n; i++) {
        Array[i] = A * Array[i - 2] + B * Array[i - 1] + C;
    }
    int kNumber = danyasort(Array, 0, n - 1, k);
    ofstream fout("kth.out");
    fout << kNumber;
    fout.close();
}
