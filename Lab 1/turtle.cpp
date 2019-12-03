#include <fstream>
#include <vector>
using namespace std;
 
int main() {
    int ArrSizeHeight, ArrSizeWidth;
    ifstream fin("turtle.in");
    fin >> ArrSizeHeight >> ArrSizeWidth;
    vector<vector<int>> Matrix(ArrSizeHeight);
    vector<vector<int>> NewMatrix(ArrSizeHeight);
    vector<int> Line(ArrSizeWidth);
    for (int i = 0; i < ArrSizeHeight; i++) {
        Matrix[i] = NewMatrix[i] = Line;
        for (int j = 0; j < ArrSizeWidth; j++)
            fin >> Matrix[i][j];
    }
    fin.close();
    NewMatrix[ArrSizeHeight - 1][0] = Matrix[ArrSizeHeight - 1][0];
    for (int i = ArrSizeHeight - 2; i >= 0; i--)
        NewMatrix[i][0] = NewMatrix[i + 1][0] + Matrix[i][0];
    for (int i = 1; i < ArrSizeWidth; i++)
        NewMatrix[ArrSizeHeight - 1][i] = NewMatrix[ArrSizeHeight - 1][i - 1] + Matrix[ArrSizeHeight - 1][i];
    for (int i = ArrSizeHeight - 2; i >= 0; i--)
        for (int j = 1; j < ArrSizeWidth; j++)
            NewMatrix[i][j] = Matrix[i][j] + max(NewMatrix[i + 1][j], NewMatrix[i][j - 1]);
    ofstream fout("turtle.out");
    fout << NewMatrix[0][ArrSizeWidth - 1];
    fout.close();
}
