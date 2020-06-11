#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
 
class Graph {
    vector<vector<int>> graph;
    vector<int> topsorted;
    vector<int> color;
     
    int size;
     
    enum Color {
        white,
        gray,
        black,
    };
public:
    Graph(int size): size(size) {
        graph.resize(size);
        color.resize(size, white);
    }
     
    bool isDFS(int parent) {
        color[parent] = gray;
 
        for (auto child : graph[parent]) {
            if (color[child] == gray || (color[child] == white && isDFS(child))) {
                return true;
            }
        }
 
        topsorted.push_back(parent);
        color[parent] = black;
        return false;
    }
     
    void push(unsigned int from, unsigned int to) {
        graph[from].push_back(to);
    }
     
    bool isTopsorted() {
        for (int i = 0; i < size; i++) {
            if (color[i] == white) {
                if (isDFS(i)) {
                    return false;
                }
            }
        }
        return true;
    }
     
    void reverse() {
        std::reverse(topsorted.begin(), topsorted.end());
    }
     
    void print(ofstream &fout) {
        for (int node : topsorted) {
            fout << node + 1 << " ";
        }
    }
};
 
int main() {
    ifstream fin("topsort.in");
 
    unsigned int vertices = 0;
    unsigned int edges = 0;
     
    fin >> vertices >> edges;
     
    Graph graph(vertices);
 
    for (int i = 0; i < edges; i++) {
        unsigned int from = 0;
        unsigned int to = 0;
         
        fin >> from >> to;
 
        graph.push(from - 1, to - 1);
    }
     
    fin.close();
     
    ofstream fout("topsort.out");
 
    if (!graph.isTopsorted()) {
        fout << "-1" << endl;
    } else {
        graph.reverse();
        graph.print(fout);
    }
    fout.close();
}
