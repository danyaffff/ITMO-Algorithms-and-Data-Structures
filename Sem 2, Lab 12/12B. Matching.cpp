 #include <iostream>
 #include <vector>
 #include <fstream>
 #include <algorithm>
  
 enum Color {
     pink,
     red,
 };
  
 class Graph {
     std::vector<std::vector<int>> graph;
     std::vector<Color> color;
     std::vector<int> isMatched;
      
     int firstPart;
     int secondPart;
      
     bool doKhunAlgoritm(int firstPartVertex) {
         for (int secondPartVertex = 0; secondPartVertex < secondPart; secondPartVertex++) {
             if (graph[firstPartVertex][secondPartVertex] == 1 && color[secondPartVertex] == pink) {
                 color[secondPartVertex] = red;
                 if (isMatched[secondPartVertex] == -1 || doKhunAlgoritm(isMatched[secondPartVertex])) {
                     isMatched[secondPartVertex] = firstPartVertex;
                     return true;
                 }
             }
         }
         return false;
     }
      
 public:
     Graph(int firstPart, int secondPart): firstPart(std::move(firstPart)), secondPart(std::move(secondPart)) {
         color.resize(this->firstPart);
         isMatched.resize(this->secondPart, -1);
          
         graph.resize(this->firstPart);
         for (int i = 0; i < this->firstPart; i++) {
             graph[i].resize(this->secondPart);
         }
     }
      
     ~Graph() {
         for (int i = 0; i < firstPart; i++) {
             graph[i].clear();
         }
         graph.clear();
         color.clear();
         isMatched.clear();
     }
      
     void input(std::ifstream & fin, int edges) {
         for (int i = 0; i < edges; i++) {
             int from;
             int to;
              
             fin >> from >> to;
              
             graph[from - 1][to - 1] = 1;
         }
     }
      
     int findMaxMatching() {
         for (int i = 0; i < firstPart; i++) {
             color.assign(secondPart, pink);
             doKhunAlgoritm(i);
         }
          
         return secondPart - static_cast<int>(std::count(isMatched.begin(), isMatched.end(), -1));
     }
 };
  
 int main() {
     std::ifstream fin("matching.in");
      
     int firstPart;
     int secondPart;
     int edges;
      
     fin >> firstPart >> secondPart >> edges;
      
     Graph graph(firstPart, secondPart);
      
     graph.input(fin, edges);
      
     fin.close();
      
     std::ofstream fout("matching.out");
      
     fout << graph.findMaxMatching();
      
     fout.close();
 }
