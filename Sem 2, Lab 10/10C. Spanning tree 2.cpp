#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
  
class Node {
    int x;
    int y;
      
public:
    Node(int x, int y): x(std::move(x)), y(std::move(y)) {}
      
    int getX() {
        return x;
    }
      
    int getY() {
        return y;
    }
};
  
class Graph {
    std::vector<Node> graph;
    std::vector<double> distance;
    std::vector<bool> color;
      
    enum Color {
        pink,
        red,
    };
      
    int size;
      
    double getLength(Node from, Node to) {
        return  (to.getX() - from.getX()) * (to.getX() - from.getX()) + (to.getY() - from.getY()) * (to.getY() - from.getY());
    }
      
public:
    Graph(int size): size(std::move(size)) {
        distance.resize(this->size, std::numeric_limits<double>::max());
        color.resize(this->size, pink);
    }
      
    void input(std::ifstream & fin) {
        for (int i = 0; i < size; i++) {
            int x;
            int y;
            fin >> x >> y;
            graph.push_back({x, y});
        }
    }
      
    void doPrimsAlgorithm() {
        distance[0] = 0;
        for (int i = 0; i < size; i++) {
            int vertex = -1;
            for (int j = 0; j < size; j++) {
                if (color[j] == pink && (vertex == -1 || distance[j] < distance[vertex])) {
                    vertex = j;
                }
            }
            color[vertex] = red;
            for (int j = 0; j < size; j++) {
                double length = getLength(graph[j], graph[vertex]);
                if (color[j] == pink && distance[j] > length) {
                    distance[j] = length;
                }
            }
        }
    }
      
    void print(std::ofstream & fout) {
        double mst = 0;
        for (double x : distance) {
            mst += sqrt(x);
        }
        fout << std::setprecision(10) << mst;
    }
};
  
int main() {
    std::ifstream fin("spantree.in");
      
    int vertices;
      
    fin >> vertices;
      
    Graph graph(vertices);
    graph.input(fin);
      
    fin.close();
      
    graph.doPrimsAlgorithm();
      
    std::ofstream fout("spantree.out");
      
    graph.print(fout);
      
    fout.close();
}
