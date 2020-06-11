#include <vector>
#include <fstream>
using namespace std;
    
class Node {
public:
    Node() {}
    int Data, Left, Right;
    
    void go(vector<Node> &Tree, vector<int> &Keys, int Root) {
        if (Root != -1) {
            go(Tree, Keys, Tree[Root].Left);
            Keys.push_back(Tree[Root].Data);
            go(Tree, Keys, Tree[Root].Right);
        }
    }
    
    int check(vector <Node> &Tree) {
        vector <int> Keys;
        go(Tree, Keys, 0);
        for (int i = 1; i < Keys.size(); ++i)
            if (Keys[i - 1] >= Keys[i]) return 0;
        return 1;
    }
};
    
int main() {
    Node node;
    int Summits;
    ifstream fin("check.in");
    fin >> Summits;
    vector<Node> Tree(Summits);
    for (int i = 0; i < Summits; i++) {
        fin >> Tree[i].Data >> Tree[i].Left >> Tree[i].Right;
        Tree[i].Left--;
        Tree[i].Right--;
    }
    fin.close();
    ofstream fout("check.out");
    if (Summits == 0 || node.check(Tree)) fout << "YES";
    else fout << "NO";
    fout.close();
}
