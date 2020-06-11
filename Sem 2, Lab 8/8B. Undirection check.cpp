#include <fstream>
#include <iostream>
using namespace std;
 
typedef int matrix;
 
int main() {
    int s;
    bool flag = true;
    ifstream fin("input.txt");
    fin >> s;
    matrix m[s][s];
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            fin >> m[i][j];
        }
    }
    fin.close();
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if ((m[i][j] != m[j][i]) || (m[i][i] == 1)) {
                flag = false;
            }
        }
    }
    ofstream fout("output.txt");
    if (flag == 1) {
        fout << "YES";
    } else {
        fout << "NO";
    }
    fout.close();
}
