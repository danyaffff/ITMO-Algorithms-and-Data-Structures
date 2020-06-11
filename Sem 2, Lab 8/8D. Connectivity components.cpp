#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

class graph {
    vector<vector<int>> g;
    vector<bool> visited;
    vector<int> nodesInCurrentComponent;
    int component = 0;
    int size;
    
    void dfs(int node) {
        visited[node] = true;
        nodesInCurrentComponent.push_back(node);
        for (int i = 0; i < g[node].size(); i++) {
            int child = g[node][i];
            if (!visited[child])
                dfs(child);
        }
    }
    
public:
    graph(int size): size(size) {
        g.resize(size);
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
    
    void findComponent() {
        vector<int> result;
        result.resize(size);
        for (int node = 0; node < g.size(); node++) {
            if (!visited[node]) {
                nodesInCurrentComponent.clear();
                dfs(node);
                component++;
                for (int j = 0; j < nodesInCurrentComponent.size(); j++) {
                    result[nodesInCurrentComponent[j]] = component;
                }
            }
        }
        cout << component << endl;
        for (int i = 0; i < size; i++) {
            cout << result[i] << " ";
        }
    }
};

int main() {
    freopen("components.in", "r", stdin);
    int nodes;
    int ribs;
    cin >> nodes >> ribs;
    graph g(nodes);
    g.set(ribs);
    freopen("components.out", "w", stdout);
    g.findComponent();
}
