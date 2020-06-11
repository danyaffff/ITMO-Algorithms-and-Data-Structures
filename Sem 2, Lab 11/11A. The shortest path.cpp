#include <fstream>
#include <vector>
#include <limits>
#include <set>
 
class Graph {
    const long long INF = std::numeric_limits<long long>::max();
    std::vector<std::vector<std::pair<int, int>>> graph;
    long size;
    long start;
    long finish;
     
public:
    Graph(long size, long start, long finish): size(std::move(size)), start(std::move(start)), finish(std::move(finish)) {
        graph.resize(this->size);
    }
     
    void input(std::ifstream & fin) {
        for (int from = 0; from < size; from++) {
            for (int to = 0; to < size; to++) {
                int weight;
                 
                fin >> weight;
     
                if (from == to || weight == -1) {
                    continue;
                }
     
                graph[from].emplace_back(to, weight);
            }
        }
    }
     
    long long doDijkstraAlgorithm(long start, long finish) {
        std::vector<long long> dist(size, INF);
        std::set<std::pair<long, int>> queue;
         
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
      
        return dist[finish] == INF ? -1 : dist[finish];
    }
     
    void print(std::ofstream & fout) {
        long long dist = doDijkstraAlgorithm(start - 1, finish - 1);
        fout << dist;
    }
};
  
  
int main() {
    std::ifstream fin("pathmgep.in");
  
    long vertices;
    long start;
    long finish;
     
    fin >> vertices >> start >> finish;
  
    Graph graph(vertices, start, finish);
  
    graph.input(fin);
     
    std::ofstream fout("pathmgep.out");
     
    graph.print(fout);
  
    fout.close();
}
