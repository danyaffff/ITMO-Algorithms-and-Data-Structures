#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
 
class Graph {
    vector<vector<int>> graph;
    vector<int> color;
    bool checker = true;
     
    enum Color {
        pink,
        red,
    };
     
public:
    Graph(int size) {
        graph.resize(size);
        color.resize(size, -1);
    }
     
    void push(int from, int to) {
        graph[from].push_back(to);
    }
     
    void dfs (int parent, int colour) {
        if (!checker) return;
        color[parent] = colour;
        for (int child : graph[parent]) {
            if (color[child] == -1) {
                dfs(child, (colour + 1) % 2);
            } else if (color[child] != (colour + 1) % 2) {
                checker = false;
                return;
            }
        }
    }
     
    bool isBipartite(ofstream & fout) {
        for (int i = 1; i <= graph.size(); i++) {
            if (color[i] == -1) {
                dfs(i, pink);
            }
        }
        return checker;
    }
};
  
int main () {
    ifstream fin("bipartite.in");
    int vertices;
    int edges;
    fin >> vertices >> edges;
    Graph graph(vertices);
    for (int i = 0; i < edges; i++) {
        int from;
        int to;
        fin >> from >> to;
        graph.push(from - 1, to - 1);
        graph.push(to - 1, from - 1);
    }
    fin.close();
    ofstream fout("bipartite.out");
    graph.isBipartite(fout) ? fout << "YES" : fout << "NO";
    fout.close();
}
