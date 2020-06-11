#include <vector>
#include <fstream>
using namespace std;
 
class Graph {
    vector<vector <int>> graph;
    vector<vector <int>> transposedGraph;
    vector<int> component;
    vector<bool> color;
    vector<int> order;
     
    int componentCount = 1;
    int size;
     
    enum Color {
        pink,  // Мой любимый цвет
        red,  // Любимый цвет моей девушки (на момент отправки, к сожалению, бывшей)
    };
     
    void print(ofstream & fout) {
        fout << componentCount - 1 << endl;
        for (int i = 0; i < size; i++)
            fout << component[i] << " ";
    }
     
    void doDFSInGraph(int from) {
        color[from] = red;
        for (int to : graph[from]) {
            if (color[to] == pink)
                doDFSInGraph(to);
        }
        order.push_back(from);
    }
     
    void doDFSInTransposedGraph(int from) {
        color[from] = red;
        component[from] = componentCount;
        for (int to : transposedGraph[from]) {
            if (color[to] == pink) {
                doDFSInTransposedGraph(to);
            }
        }
    }
     
public:
    Graph(int size): size(size) {
        graph.resize(size);
        transposedGraph.resize(size);
        color.resize(size, pink);
        component.resize(size);
    }
     
    void input(ifstream & fin, int edges) {
        for (int i = 0; i < edges; i++) {
            int from, to;
            fin >> from >> to;
            graph[from - 1].push_back(to - 1);
            transposedGraph[to - 1].push_back(from - 1);
        }
    }
     
    void condense(ofstream & fout) {
        for (int i = 0; i < size; i++) {
            if (color[i] == pink) {
                doDFSInGraph(i);
            }
        }
        color.assign(size, pink);
        for (int i = 0; i < size; i++) {
            int v = order[size - 1 - i];
            if (color[v] == pink) {
                doDFSInTransposedGraph(v);
                componentCount++;
            }
        }
        print(fout);
    }
};

int main() {
    int verteces, edges;
    ifstream fin("cond.in");
    fin >> verteces >> edges;
    Graph graph(verteces);
    graph.input(fin, edges);
    fin.close();
    ofstream fout("cond.out");
    graph.condense(fout);
    fout.close();
}
