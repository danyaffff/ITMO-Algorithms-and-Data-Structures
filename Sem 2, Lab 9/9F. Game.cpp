#include <fstream>
#include <vector>
using namespace std;

class Graph {
    vector<vector <int>> graph;
    vector<bool> vertex;
    vector<bool> visited;
    
    enum Color {
        pink,
        red,
    };
    
    enum Statement {
        firstPlayerWins,
        secondPlayerWins,
    };
    
public:
    Graph(int size) {
        graph.resize(size);
        vertex.resize(size);
        visited.resize(size, pink);
    }
    
    void input(ifstream & fin, int edges) {
        for (int i = 0; i < edges; i++) {
            int from;
            int to;
            fin >> from >> to;
            graph[from - 1].push_back(to - 1);
        }
    }
    
    void dfs(int from) {
        visited[from] = red;
        bool status = secondPlayerWins;
        for (int to : graph[from]) {
            if (visited[to] == pink) {
                dfs(to);
            }
            if (vertex[to] == secondPlayerWins) {
                status = firstPlayerWins;
            }
        }
        vertex[from] = status;
    }
    
    void print(ofstream & fout, int position) {
        !vertex[position - 1] ? fout <<  "First player wins" << endl : fout << "Second player wins" << endl;
    }
};

int main() {
    ifstream fin("game.in");
    int verteces, edges, position;
    fin >> verteces >> edges >> position;
    Graph graph(verteces);
    graph.input(fin, edges);
    fin.close();
    graph.dfs(position - 1);
    ofstream fout("game.out");
    graph.print(fout, position);
    fout.close();
    return 0;
}
