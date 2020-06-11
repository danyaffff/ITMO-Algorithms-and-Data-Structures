#include <fstream>
#include <vector>
 
int main() {
    int vertices;
    int edges;
     
    std::ifstream fin("input.txt");
     
    fin >> vertices >> edges;
     
    std::vector<int> degrees(vertices, 0);
     
    for (int i = 0; i < edges; i++) {
        int from;
        int to;
         
        fin >> from >> to;
         
        degrees[from - 1]++;
        degrees[to - 1]++;
    }
     
    fin.close();
     
    std::ofstream fout("output.txt");
     
    for (int i = 0; i < vertices; i++) {
        fout << degrees[i] << " ";
    }
}
