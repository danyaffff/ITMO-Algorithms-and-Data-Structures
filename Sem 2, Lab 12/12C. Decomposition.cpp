#define NO_PATH -1
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <fstream>
#include <list>
using decomposition_type = typename std::pair<long, std::list<int>>;

struct Edge {
    int from;
    int to;
    long capacity;
    long flow;
    int number;
    
    Edge(int from, int to, long capacity, long flow, int number): from(from), to(to), capacity(capacity), flow(flow), number(number) {}

    long availableCapacity() {
        return capacity - flow;
    }
};

class Graph {
    std::vector<decomposition_type> decompositions;
    std::vector<std::vector<int>> graph;
    std::vector<Edge> edges;
    std::vector<int> levels;
    std::vector<int> ptr;
    
    int amountOfEdges;
    
    void add_edge(int from, int to, long cap, int number) {
        graph[from].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(from, to, cap, 0, number);
        graph[to].push_back(static_cast<int>(edges.size()));
        edges.emplace_back(to, from, 0, 0, number);
    }
    
    bool bfs(int source, int sink) {
        levels.assign(graph.size(), -1);

        std::queue<int> queue;

        queue.push(source);
        levels[source] = 0;

        while (!queue.empty() && levels[sink] == -1) {
            int from = queue.front();
            queue.pop();

            for (auto id : graph[from]) {
                int to = edges[id].to;

                if (levels[to] == -1 && edges[id].availableCapacity() > 0) {
                    queue.push(to);
                    levels[to] = levels[from] + 1;
                }
            }
        }

        return levels[sink] != -1;
    }
    
    long dfs(int current, int sink, long flow) {
        if (flow == 0) {
            return 0;
        }
        if (current == sink) {
            return flow;
        }

        while (ptr[current] < graph[current].size()) {
            int currentEdge = graph[current][ptr[current]];
            int next = edges[currentEdge].to;

            if (levels[current] + 1 != levels[next]) {
                ptr[current]++;
                continue;
            }

            long pushedFlow = dfs(next, sink, std::min(flow, edges[currentEdge].availableCapacity()));

            if (pushedFlow != 0) {
                edges[currentEdge].flow += pushedFlow;
                edges[currentEdge ^ 1].flow -= pushedFlow;
                return pushedFlow;
            }

            ptr[current]++;
        }

        return 0;
    }
    
    void simpleDecomposition(int start, decomposition_type & paths) {
        paths.first = NO_PATH;
        paths.second.clear();

        std::vector<bool> visited(graph.size());
        int current = start;

        while (!visited[current]) {
            if (current == graph.size() - 1) {
                break;
            }

            int currentEdge = -1;
            for (auto next : graph[current]) {
                if (edges[next].flow > 0) {
                    currentEdge = next;
                    break;
                }
            }

            if (currentEdge == -1) {
                paths.first = NO_PATH;
                paths.second.clear();
                return;
            }

            paths.second.push_back(currentEdge);
            visited[current] = 1;
            current = edges[currentEdge].to;
        }

        if (visited[current]) {
            while (edges[paths.second.front()].from != current) {
                paths.second.pop_front();
            }
        }

        long decompositedFlow = std::numeric_limits<int64_t>::max();
        for (auto currentEdge : paths.second) {
            if (edges[currentEdge].flow < decompositedFlow) {
                decompositedFlow = edges[currentEdge].flow;
            }
        }


        for (auto currentEdge : paths.second) {
            edges[currentEdge].flow -= decompositedFlow;
        }

        paths.first = decompositedFlow;
    }
    
public:
    Graph(int vertices, int edges): amountOfEdges(edges) {
        graph.resize(vertices);
        levels.resize(vertices);
        ptr.resize(vertices);
    }
    
    void input(std::ifstream & fin) {
        for (int i = 0; i < amountOfEdges; i++) {
            int from;
            int to;
            long capacity;
            
            fin >> from >> to >> capacity;
            
            add_edge(from - 1, to - 1, capacity, i + 1);
        }
    }
    
    long dinic(int source, int sink) {
        long maxFlow = 0;

        while (true) {
            if (!bfs(source, sink)) {
                break;
            }

            ptr.assign(graph.size(), 0);

            long flow = dfs(source, sink, std::numeric_limits<long>::max());
            while (flow != 0) {
                maxFlow += flow;
                flow = dfs(source, sink, std::numeric_limits<long>::max());
            }
        }

        return maxFlow;
    }

    long size() {
        return graph.size();
    }

    void fullDecomposition() {
        decomposition_type paths;
        simpleDecomposition(0, paths);

        while (paths.first != NO_PATH) {
            decompositions.emplace_back(paths.first, paths.second);
            simpleDecomposition(0, paths);
        }
    }
    
    void output(std::ofstream & fout) {
        fout << decompositions.size() << std::endl;
        
        for (auto decomposition : decompositions) {
            fout << decomposition.first << ' ' << decomposition.second.size() << ' ';
            
            for (auto currentEdge : decomposition.second) {
                fout << edges[currentEdge].number << ' ';
            }
            
            fout << std::endl;
        }
    }
};

int main() {
    std::ifstream fin("decomposition.in");
    
    int vertices;
    int edges;
    
    fin >> vertices >> edges;

    Graph graph(vertices, edges);

    graph.input(fin);
    
    fin.close();

    graph.dinic(0, static_cast<int>(graph.size() - 1));
    
    std::ofstream fout("decomposition.out");

    graph.fullDecomposition();
    
    graph.output(fout);
    
    fout.close();
}
