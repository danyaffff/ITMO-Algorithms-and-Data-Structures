#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
 
class Graph {
    vector<vector <int>> graph;
    vector<bool> color;
    vector<int> path;
     
    int size;
     
    enum Color {
        pink,
        red,
    };
     
    void doDFS(int from) {
        color[from] = red;
        for (int i = 0; i < graph[from].size(); i++) {
            int to = graph[from][i];
            if (color[to] == pink) {
                doDFS(to);
            }
        }
        path.push_back(from);
    }
     
    bool isPathExists(int from, int to) {
        for (int child : graph[from]) {
            if (child == to) {
                return true;
            }
        }
        return false;
    }
     
    bool isThereAHamiltonianPath() {
        for (int i = 0; i < size; i++) {
            if (color[i] == pink) {
                doDFS(i);
            }
        }
        for (int i = size - 1; i > 0; i--) {
            if (!isPathExists(path[i], path[i - 1])) {
                return false;
            }
        }
        return true;
    }
     
public:
    Graph(int size): size(size) {
        graph.resize(size);
        color.resize(size, pink);
    }
     
    void input(ifstream & fin, int edges) {
        for (int i = 0; i < edges; i++) {
            int from;
            int to;
            fin >> from >> to;
            graph[from - 1].push_back(to - 1);
        }
    }
     
    void print(ofstream & fout) {
        isThereAHamiltonianPath() ? fout << "YES" : fout << "NO";
    }
};
 
int main() {
    ifstream fin("hamiltonian.in");
    int verteces, edges;
    fin >> verteces >> edges;
    Graph graph(verteces);
    graph.input(fin, edges);
    fin.close();
    ofstream fout("hamiltonian.out");
    graph.print(fout);
    fout.close();
}
