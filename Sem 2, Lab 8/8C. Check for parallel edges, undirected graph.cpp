#include <fstream>
using namespace std;
 
int main() {
    int v, e;
    ifstream fin("input.txt");
    fin >> v >> e;
    int m[v][v];
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            m[i][j] = 0;
        }
    }
    ofstream fout("output.txt");
    for (int i = 0; i < e; i++) {
        int a, b;
        fin >> a >> b;
        if ((m[a - 1][b - 1]) || (m[b - 1][a - 1])) {
            fout << "YES";
            return 0;
        }
        m[a - 1][b - 1] = 1;
    }
    fin.close();
    fout << "NO";
    fout.close();
}
