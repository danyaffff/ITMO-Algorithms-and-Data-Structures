#define NO_FLOW -1
#define NO_PREVIOUS -1
#include <vector>
#include <unordered_map>
#include <fstream>
 
struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
     
    Edge(int from, int to, int capacity, int flow): from(std::move(from)), to(std::move(to)), capacity(std::move(capacity)), flow(std::move(flow)) {}
 
    int availableCapacity() const {
        return capacity - flow;
    }
};
 
class Graph {
    std::vector<std::vector<int>> graph;
    std::vector<Edge> edges;
    int numberOfEdges;
     
    void addEdge(int from, int to, int capacity) {
        graph[from].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(from, to, capacity, 0);
        graph[to].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(to, from, 0, 0);
    }
     
    long addFlow(int source, int sink) {
        std::vector<int> path;
        std::unordered_map<int, int> previousFor = {{source, NO_PREVIOUS}};
         
        path.push_back(source);
         
        for (int i = 0; i < path.size(); i++) {
            int vertex = path[i];
            for (auto e : graph[vertex]) {
                auto edge = edges[e];
                 
                if (previousFor.find(edge.to) == previousFor.end() && edge.availableCapacity() > 0) {
                    path.push_back(edge.to);
                    previousFor.insert({edge.to, e});
                }
            }
        }
         
        path.clear();
         
        if (previousFor.find(sink) == previousFor.end()) {
            return NO_FLOW;
        }
         
        int current = sink;
        while (previousFor[current] != NO_PREVIOUS) {
            int e = previousFor[current];
            path.push_back(e);
            current = edges[e].from;
        }
         
        long flow = std::numeric_limits<long>::max();
        for (auto e : path) {
            if (edges[e].availableCapacity() < flow) {
                flow = edges[e].availableCapacity();
            }
        }
         
        for (auto e : path) {
            edges[e].flow += flow;
            edges[e ^ 1].flow -= flow;
        }
        return flow;
    }
     
public:
    Graph(int size, int numberOfEdges): numberOfEdges(std::move(numberOfEdges)) {
        graph.resize(size);
    }
     
    ~Graph() {
        graph.clear();
    }
     
    void input(std::ifstream & fin) {
        for (int i = 0; i < numberOfEdges; i++) {
            int from;
            int to;
            int capacity;
             
            fin >> from >> to >> capacity;
            addEdge(from - 1, to - 1, capacity);
        }
    }
     
    long findMaxFlow() {
        long maxFlow = 0;
         
        while (true) {
            long flow = addFlow(0, static_cast<int>(graph.size() - 1));
            if (flow == NO_FLOW) {
                break;
            }
            maxFlow += flow;
        }
        return maxFlow;
    }
};
 
int main() {
    int vertices;
    int edges;
     
    std::ifstream fin("maxflow.in");
     
    fin >> vertices >> edges;
 
    Graph graph(vertices, edges);
 
    graph.input(fin);
     
    fin.close();
 
    std::ofstream fout("maxflow.out");
     
    fout << graph.findMaxFlow();
     
    fout.close();
}
