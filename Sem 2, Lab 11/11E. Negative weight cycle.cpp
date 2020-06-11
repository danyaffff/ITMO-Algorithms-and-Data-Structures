#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
  
class Graph {
    std::vector<std::vector<std::pair<int, long>>> graph;
    std::vector<int> negativeCycle;
    const long INF = std::numeric_limits<long>::max();
    int size;
     
public:
    Graph(int size): size(std::move(size)) {
        graph.resize(size);
    }
     
    void input(std::ifstream & fin) {
        for (int from = 0; from < size; from++) {
               for (int to = 0; to < size; to++) {
                   long weight;
                   fin >> weight;
         
                   if (weight == INF) {
                       continue;
                   }
         
                   graph[from].emplace_back(to, weight);
               }
           }
    }
     
    bool findCycle(int s) {
        std::vector<long> distances(graph.size(), INF);
        std::vector<int> parents(graph.size(), -1);
      
        distances[s] = 0;
        int start = -1;
      
        for (int n = 0; n < graph.size(); n++) {
            for (int from = 0; from < graph.size(); from++) {
                for (auto edge : graph[from]) {
      
                    if (distances[edge.first] > distances[from] + edge.second) {
                        if (n == graph.size() - 1) {
                            start = edge.first;
                        }
                        distances[edge.first] = distances[from] + edge.second;
                        parents[edge.first] = from;
                    }
                }
            }
        }
      
        if (start == -1) {
            return false;
        } else {
            for (int i = 0; i < graph.size(); ++i) {
                start = parents[start];
            }
      
            int current = start;
      
            while (!(current == parents[start] && negativeCycle.size() > 1)) {
                negativeCycle.push_back(current);
                current = parents[current];
            }
 
            std::reverse(negativeCycle.begin(), negativeCycle.end());
            return true;
        }
    }
     
    void print(std::ofstream & fout) {
        if (findCycle(0)) {
               if (!negativeCycle.empty()) {
                   fout << "YES" << std::endl << negativeCycle.size() << std::endl;
                   for (auto vertex : negativeCycle) {
                       fout << vertex + 1 << " ";
                   }
                   fout << std::endl;
                   return;
               }
           }
         
           fout << "NO" << std::endl;
    }
};
  
int main() {
    std::ifstream fin("negcycle.in");
  
    int vertices;
    fin >> vertices;
     
    Graph graph(vertices);
     
    graph.input(fin);
     
    fin.close();
     
    std::ofstream fout("negcycle.out");
     
    graph.print(fout);
     
    fout.close();
}
