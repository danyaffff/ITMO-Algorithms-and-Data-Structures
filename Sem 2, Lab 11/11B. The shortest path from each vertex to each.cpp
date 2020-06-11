 #include <fstream>
 #include <vector>
 #include <limits>
  
 class Graph {
     std::vector<std::vector<std::pair<int, int>>> graph;
     long INF = std::numeric_limits<long>::max();
     long size;
     long edges;
      
 public:
     Graph(long size, long edges): size(std::move(size)), edges(std::move(edges)) {
         graph.resize(this->size);
     }
      
     void input(std::ifstream & fin) {
         for (long i = 0; i < edges; i++) {
             long from;
             long to;
             long weight;
             fin >> from >> to >> weight;
          
             graph[from - 1].push_back({to - 1, weight});
         }
     }
      
     std::vector<std::vector<long long>> doFloydWarshallAlgorithm() {
         std::vector<std::vector<long long>> dist(size);
       
         for (long i = 0; i < size; i++) {
             dist[i].resize(size, INF);
       
             dist[i][i] = 0;
       
             for (auto edge : graph[i]) {
                 dist[i][edge.first] = edge.second;
             }
         }
       
         for (size_t k = 0; k < size; k++) {
             for (size_t i = 0; i < size; i++) {
                 for (size_t j = 0; j < size; j++) {
                     dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                 }
             }
         }
       
         return dist;
     }
      
     void print(std::ofstream & fout) {
         auto dist = doFloydWarshallAlgorithm();
          
         for (long i = 0; i < size; i++) {
             for (long j = 0; j < size; j++) {
                 fout << dist[i][j] << ' ';
             }
             fout << std::endl;
         }
     }
 };
  
 int main() {
     std::ifstream fin("pathsg.in");
   
     long vertices;
     long edges;
     fin >> vertices >> edges;
   
     Graph graph(vertices, edges);
   
     graph.input(fin);
      
     fin.close();
      
     std::ofstream fout("pathsg.out");
      
     graph.print(fout);
      
     fout.close();
 }
