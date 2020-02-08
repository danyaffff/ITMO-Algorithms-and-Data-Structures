#include <fstream>
 
using namespace std;
void merge(string* Country, int* Index, int Low, int Mid, int High) {
    int NewIndex[100000];
    int i = Low, NewMid = Mid, NewArrayIndex = 0;
    while ((i < Mid) && (NewMid < High)) {
        if (Country[Index[i]] <= Country[Index[NewMid]]) {
            NewIndex[NewArrayIndex] = Index[i];
            i++;
        } else {
            NewIndex[NewArrayIndex] = Index[NewMid];
            NewMid++;
        }
        NewArrayIndex++;
    }
    for (i; i < Mid; i++) {
        NewIndex[NewArrayIndex] = Index[i];
        NewArrayIndex++;
    }
    for (NewMid; NewMid < High; NewMid++) {
        NewIndex[NewArrayIndex] = Index[NewMid];
        NewArrayIndex++;
    }
    for (int i = 0; i < NewArrayIndex; i++) {
        Index[Low + i] = NewIndex[i];
    }
}
 
void mergesort(string* Country, int* Index, int Low, int High) {
    if (Low + 1 < High) {
        int Mid = (Low + High) / 2;
        mergesort(Country, Index, Low, Mid);
        mergesort(Country, Index, Mid, High);
        merge(Country, Index, Low, Mid, High);
    }
}
 
int main() {
    ifstream fin("race.in");
    int NumberOfPersons;
    int Index[100000];
    string Surname[100000], Country[100000];
    fin >> NumberOfPersons;
    for (int i = 0; i < NumberOfPersons; i++) {
        fin >> Country[i] >> Surname[i];;
        Index[i] = i;
    }
    fin.close();
    mergesort(Country, Index, 0, NumberOfPersons);
    ofstream fout("race.out");
    fout << "=== " << Country[Index[0]] << " ===" << endl;
    fout << Surname[Index[0]] << endl;
    for (int i = 1; i < NumberOfPersons; i++) {
        if (Country[Index[i - 1]] != Country[Index[i]]) {
            fout << "=== " << Country[Index[i]] << " ===" << endl;
        }
        fout << Surname[Index[i]] << endl;
    }
    fout.close();
}
