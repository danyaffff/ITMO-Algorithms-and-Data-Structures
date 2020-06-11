#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class graph {
    vector<vector<int>> g;
    vector<bool> visited;
    vector<int> path;
    int component = 0;
    int size;
    
    void bfs(int node) {
        queue<int> notVisited;
        notVisited.push(node);
        visited[node] = true;
        while (notVisited.size() != 0) {
            int from = notVisited.front();
            notVisited.pop();
            for (int i = 0; i < g[from].size(); i++) {
                int to = g[from][i];
                if (!visited[to]) {
                    visited[to] = true;
                    notVisited.push(to);
                    path[to] = path[from] + 1;
                }
            }
        }
    }
    
public:
    graph(int size): size(size) {
        g.resize(size);
        path.assign(size, -1);
        visited.assign(size, false);
    }
    
    void set(int ribs) {
        for (int i = 0; i < ribs; i++) {
            int a;
            int b;
            cin >> a >> b;
            g[a - 1].push_back(b - 1);
            g[b - 1].push_back(a - 1);
        }
    }
    
    void searchPath(int node) {
        path[node] = 0;
        bfs(node);
        for (int i = 0; i < size; i++) {
            cout << path[i] << " ";
        }
    }
};

int main() {
    freopen("pathbge1.in", "r", stdin);
    int nodes;
    int ribs;
    cin >> nodes >> ribs;
    graph g(nodes);
    g.set(ribs);
    freopen("pathbge1.out", "w", stdout);
    g.searchPath(0);
}
