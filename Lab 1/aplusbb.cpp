#include <fstream>
using namespace std;
 
int main() {
    long long a;
    long long b;
    ifstream fin("aplusbb.in");
    fin >> a >> b;
    fin.close();
    ofstream fout("aplusbb.out");
    fout << a + b * b;
    fout.close();
}
