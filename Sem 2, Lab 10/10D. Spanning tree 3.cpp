#include <fstream>
#include <vector>
#include <algorithm>
  
class Graph {
    std::vector<std::pair<int, std::pair<int, int>>> graph;
    std::vector<unsigned int> parents;
      
    int size;
    long long mst = 0;
      
    int find_set(int a) {
        return parents[a] == a ? a : parents[a] = find_set(parents[a]);
    }
      
    void union_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            parents[b] = a;
        }
    }
      
public:
    Graph(int size): size(std::move(size)) {
        parents.resize(this->size);
        for (int i = 0; i < this->size; i++) {
            parents[i] = i;
        }
    }
      
    void input(std::ifstream & fin, int edges) {
        for (int i = 0; i < edges; i++) {
            int from;
            int to;
            int weight;
              
            fin >> from >> to >> weight;
              
            graph.push_back({weight, {from - 1, to - 1}});
        }
          
        std::sort(graph.begin(), graph.end());
    }
      
    void dsu() {
        for (auto edge : graph) {
            if (find_set(edge.second.first) != find_set(edge.second.second)) {
                union_set(edge.second.first, edge.second.second);
                mst += edge.first;
            }
        }
    }
      
    void print(std::ofstream & fout) {
        fout << mst;
    }
};
   
int main() {
    std::ifstream fin("spantree3.in");
      
    int vertices = 0;
    int edges = 0;
      
    fin >> vertices >> edges;
      
    Graph graph(vertices);
      
    graph.input(fin, edges);
      
    fin.close();
      
    graph.dsu();
      
    std::ofstream fout("spantree3.out");
      
    graph.print(fout);
      
    fout.close();
}
