#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
  
class Graph {
    vector<vector<int>> graph;
    vector<int> parents;
    vector<int> color;
      
    int size;
      
    enum Color {
        white,
        gray,
        black,
    };
      
    int dfs(int parent) {
        color[parent] = gray;
        for (int child : graph[parent]) {
            if (color[child] == gray) {
                parents[child] = parent;
                return parent;
            }
            if (color[child] == white) {
                parents[child] = parent;
                int last = dfs(child);
                if (last != -1) {
                    return last;
                }
            }
        }
        color[parent] = black;
        return -1;
    }
      
public:
    Graph(int size): size(size) {
        graph.resize(size);
        parents.resize(size, -1);
        color.resize(size, white);
    }
      
    void push(int from, int to) {
        graph[from].push_back(to);
    }
      
    void lookForACycleAndPrintIt(ofstream &fout) {
        for (int i = 0; i < size; i++) {
            if (color[i] == white) {
                int last = dfs(i);
                if (last != -1) {
                    fout << "YES" << endl;
                    vector<int> cycle;
                    cycle.push_back(last + 1);
                    for (int v = parents[last]; v != last; v = parents[v]) {
                        cycle.push_back(v + 1);
                    }
                    reverse(cycle.begin(), cycle.end());
                    for (int vertex : cycle) {
                        fout << vertex << " ";
                    }
                    return;
                }
            }
        }
        fout << "NO" << endl;
    }
};
   
int main() {
    ifstream fin("cycle.in");
    int vertices = 0;
    int edges = 0;
    fin >> vertices >> edges;
    Graph graph(vertices);
    for (int i = 0; i < edges; i++) {
        int from = 0;
        int to = 0;
        fin >> from >> to;
        graph.push(from - 1, to - 1);
    }
    fin.close();
    ofstream fout("cycle.out");
    graph.lookForACycleAndPrintIt(fout);
    fout.close();
}
