#include <fstream>
using namespace std;
 
typedef int matrix;
 
int main() {
    int v, e, a, b;
    ifstream fin("input.txt");
    fin >> v >> e;
    matrix m[v][v];
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            m[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++) {
        fin >> a >> b;
        m[a - 1][b - 1] = 1;
    }
    fin.close();
    ofstream fout("output.txt");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            fout << m[i][j] << " ";
        }
        fout << endl;
    }
    fout.close();
}
