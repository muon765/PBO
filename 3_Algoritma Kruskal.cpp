#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Struktur untuk menyimpan sisi (edge)
struct Edge {
    char src, dest;
    int weight;
};


// Union-Find (Disjoint Set) untuk mendeteksi siklus
struct DisjointSets {
    vector<int> parent, rank;


    DisjointSets(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }


    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }


    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v])
                parent[u] = v;
            else if (rank[u] > rank[v])
                parent[v] = u;
            else {
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};


int main() {
    vector<Edge> edges = {
        {'D','E',1}, {'D','G',2}, {'G','E',3}, {'H','G',3},
        {'F','C',3}, {'C','D',3}, {'F','B',4}, {'C','B',4},
        {'H','B',4}, {'B','E',4}, {'A','H',5}, {'F','D',6},
        {'A','B',8}, {'A','F',10}
    };


    // Jumlah simpul (A-H = 8)
    int V = 8;


    // Urutkan sisi berdasarkan bobot
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });


    DisjointSets ds(V);
    vector<Edge> result;
    int totalWeight = 0;


    // Fungsi bantu untuk konversi huruf ke indeks
    auto idx = [](char c) { return c - 'A'; };


    for (auto &e : edges) {
        int u = idx(e.src);
        int v = idx(e.dest);
        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            result.push_back(e);
            totalWeight += e.weight;
        }
    }


    cout << "Minimum Spanning Tree (Algoritma Kruskal):\n";
    for (auto &e : result)
        cout << e.src << " - " << e.dest << " = " << e.weight << endl;


    cout << "Total bobot minimum = " << totalWeight << endl;
    return 0;
}

