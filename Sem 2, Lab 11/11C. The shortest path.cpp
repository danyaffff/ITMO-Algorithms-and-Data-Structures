#include <fstream>
#include <vector>
#include <limits>
#include <set>
 
class Graph {
    std::vector<std::vector<std::pair<int, int>>> graph;
    const long INF = std::numeric_limits<long>::max();
    int size;
    int edges;
     
public:
    Graph(int size, int edges): size(std::move(size)), edges(std::move(edges)) {
        graph.resize(this->size);
    }
     
    void input(std::ifstream & fin) {
        for (int i = 0; i < edges; i++) {
               int from;
               int to;
               int weight;
         
               fin >> from >> to >> weight;
         
               graph[from - 1].emplace_back(to - 1, weight);
               graph[to - 1].emplace_back(from - 1, weight);
           }
    }
     
    std::vector<long> dijkstra(int start) {
        std::vector<long> dist(graph.size(), INF);
        std::set<std::pair<int, int>> queue;
      
        dist[start] = 0;
        queue.insert({0, start});
      
        while (!queue.empty()) {
            auto minimalEdge = *queue.begin();
            queue.erase(queue.begin());
      
            auto from = minimalEdge.second;
      
            for (auto edge : graph[from]) {
                int to = edge.first;
                int weight = edge.second;
      
                if (dist[to] > dist[from] + weight) {
                    queue.erase({dist[to], to});
                    dist[to] = dist[from] + weight;
                    queue.insert({dist[to], to});
                }
            }
        }
      
        return dist;
    }
     
    void print(std::ofstream & fout) {
        auto dist = dijkstra(0);
         
        for (auto vertex : dist) {
            fout << vertex << ' ';
        }
    }
};
 
int main() {
    std::ifstream fin("pathbgep.in");
  
    int vertices;
    int edges;
    fin >> vertices >> edges;
  
    Graph graph(vertices, edges);
     
    graph.input(fin);
     
    fin.close();
     
    std::ofstream fout("pathbgep.out");
     
    graph.print(fout);
     
    fout.close();
}
