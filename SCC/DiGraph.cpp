#include <iostream>
#include <list>
#include <vector>
#include <fstream>

class DiGraph {
    using node_type = int;
    using graph_type = std::vector<std::vector<node_type> >;
    using used_nodes = std::vector<char>;
    using vector_nodes = std::vector<node_type>;
    graph_type graph, transpose_graph;
    used_nodes used;
    vector_nodes finished;
    std::list<int> component;
    std::list<std::list<int> > res;
    int N;
    bool is_changed;

    void dfs1(node_type v) {
        used[v] = true;
        for (const auto &node : graph[v]) {
            if (!used[node]) {
                dfs1(node);
            }
        }
        finished.push_back(v);
    }

    void dfs2(node_type v) {
        used[v] = true;
        component.push_back(v);
        for (const auto &node : transpose_graph[v]) {
            if (!used[node]) {
                dfs2(node);
            }
        }
    }

public:
    explicit DiGraph(const int n) : N(n) {
        graph.resize(n);
        transpose_graph.resize(n);
        used.resize(n);
        is_changed = true;
    }

    void add(const node_type a, const node_type b) {
        if (a != b) {
            graph[a].push_back(b);
            transpose_graph[b].push_back(a);
            is_changed = true;
        }
    }

    std::list<std::list<int> > scc() {
        if (!is_changed) {
            return res;
        }
        is_changed = false;
        used.assign(N, false);
        for (int i = 0; i < N; ++i) {
            if (!used[i]) {
                dfs1(i);
            }
        }
        used.assign(N, false);
        for (int i = 0; i < N; ++i) {
            auto v = finished[N - i - 1];
            if (!used[v]) {
                dfs2(v);
                res.push_back(std::move(component));
            }
        }
        return res;
    }
};


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Error argv" << std::endl;
        return 1;
    }
    auto fileName = argv[1];

    std::ifstream file(fileName);
    if (!file) {
        std::cout << "can't open file" << std::endl;
        return 1;
    }
    int n, v1, v2;
    file >> n;
    DiGraph diGraph(n);
    while (file.good()) {
        file >> v1 >> v2;
        if (v1 >= n || v2 >= n) {
            std::cout << "error node";
            return 1;
        }
        diGraph.add(v1, v2);
    }
    auto res = diGraph.scc();
    for (const auto &item : res) {
        for (const auto &item1 : item) {
            std::cout << item1 << " ";

        }
        std::cout << std::endl;
    }
    return 0;
}