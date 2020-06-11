#include <fstream>
using namespace std;
 
int main() {
    int NumberOfStrings, Length, Iterations, CountingArray[26];
    string String[1000];
    ifstream fin("radixsort.in");
    fin >> NumberOfStrings >> Length >> Iterations;
    string SortedArray[1000];
    for (int i = 0; i < NumberOfStrings; i++) {
        fin >> String[i];
    }
    fin.close();
    for (int i = 1; i <= Iterations; i++) {
        for (int j = 0; j < 26; j++) {
            CountingArray[j] = 0;
        }
        for (int j = 0; j < NumberOfStrings; j++) {
            CountingArray[String[j][Length - i] - 97]++;
        }
        for (int j = 1; j < 26; j++) {
            CountingArray[j] += CountingArray[j - 1];
        }
        for (int j = NumberOfStrings - 1; j >= 0; j--) {
            CountingArray[String[j][Length - i] - 97]--;
            SortedArray[CountingArray[String[j][Length - i] - 97]] = String[j];
        }
        for (int j = 0; j < NumberOfStrings; j++) {
            String[j] = SortedArray[j];
        }
    }
    ofstream fout("radixsort.out");
    for (int i = 0; i < NumberOfStrings; i++) {
        fout << String[i] << endl;
    }
    fout.close();
}
