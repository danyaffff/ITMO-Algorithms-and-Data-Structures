#include <fstream>
using namespace std;
   
class Node {
    public:
    int Data, Left, Right;
    Node() {}
    int height(Node* Tree, int Root) {
        if (Root <= -1) return 0;
        int Right = height(Tree, Tree[Root].Right);
        int Left = height(Tree, Tree[Root].Left);
        if (Left > Right) return (Left + 1);
        else return (Right + 1);
    }
};
   
int main() {
    int Summits;
    ifstream fin("height.in");
    fin >> Summits;
    Node* Tree = new Node[Summits];
    for (int i = 0; i < Summits; ++i) {
        fin >> Tree[i].Data >> Tree[i].Left >> Tree[i].Right;
        Tree[i].Right--;
        Tree[i].Left--;
    }
    fin.close();
    Node node;
    ofstream fout("height.out");
    if (Summits !=0)
        fout << node.height(Tree, 0);
    else fout << 0;
    fout.close();
}
