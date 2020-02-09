#include <fstream>
#include <iomanip>
using namespace std;
 
int main() {
    int Lamps;
    double StartHeight, Left = 0, Middle, Right, LastHeight, PreviousHeight, CurrentHeight, NextHeight;
    bool Ground;
    ifstream fin("garland.in");
    fin >> Lamps >> StartHeight;
    fin.close();
    Right = StartHeight;
    while ((Right - Left) > 0.01 / (Lamps - (double)1)) {
        Middle = (Left + Right) / 2;
        PreviousHeight = StartHeight;
        CurrentHeight = Middle;
        Ground = (CurrentHeight >= 0);
        for (int i = 3; i <= Lamps; i++) {
            NextHeight = 2 * CurrentHeight - PreviousHeight + 2;
            Ground &= NextHeight >= 0;
            PreviousHeight = CurrentHeight;
            CurrentHeight = NextHeight;
        }
        if (Ground) {
            Right = Middle;
            LastHeight = CurrentHeight;
        } else {
            Left = Middle;
        }
    }
    ofstream fout("garland.out");
    fout << fixed << setprecision(2) << LastHeight;
    fout.close();
}
