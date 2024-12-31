//Job matching code for Rabin karp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int PRIME = 101;

long long calculateHash(const string &str, int length) {
    long long hash = 0;
    for (int i = 0; i < length; i++) {
        hash = (hash * 256 + str[i]) % PRIME;
    }
    return hash;
}

bool rabinKarp(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m > n) return false;

    long long patternHash = calculateHash(pattern, m);
    long long textHash = calculateHash(text, m);

    long long highestPower = 1;
    for (int i = 0; i < m - 1; i++) {
        highestPower = (highestPower * 256) % PRIME;
    }

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash && text.substr(i, m) == pattern) {
            return true;
        }

        if (i < n - m) {
            textHash = (256 * (textHash - text[i] * highestPower) + text[i + m]) % PRIME;
            if (textHash < 0) textHash += PRIME;
        }
    }

    return false;
}

int main() {
    int n, m;
    cin >> n;
    cin.ignore();
    vector<string> jobSeekersSkills(n);
    for (int i = 0; i < n; i++) {
        getline(cin, jobSeekersSkills[i]);
    }

    cin >> m;
    cin.ignore();
    vector<string> jobRequirements(m);
    for (int i = 0; i < m; i++) {
        getline(cin, jobRequirements[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (rabinKarp(jobSeekersSkills[i], jobRequirements[j])) {
                cout << "Job Seeker " << i + 1 << " matches Job " << j + 1 << endl;
            }
        }
    }

    return 0;
}

//Code for job distribution optimisation using kruskal algorithm
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
private:
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<Edge> graph(edges);
    for (int i = 0; i < edges; i++) {
        cin >> graph[i].u >> graph[i].v >> graph[i].weight;
    }

    sort(graph.begin(), graph.end(), compare);

    DisjointSet ds(nodes);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const auto &edge : graph) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    cout << "Minimum Spanning Tree (MST):\n";
    for (const auto &edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
    cout << "Total Weight: " << totalWeight << endl;

    return 0;
}
//Code for job distribution optimisation using prime algorithm
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int findMinVertex(vector<int> &weights, vector<bool> &inMST, int nodes) {
    int minVertex = -1;
    for (int i = 0; i < nodes; i++) {
        if (!inMST[i] && (minVertex == -1 || weights[i] < weights[minVertex])) {
            minVertex = i;
        }
    }
    return minVertex;
}

void primsAlgorithm(vector<vector<pair<int, int>>> &graph, int nodes) {
    vector<int> parent(nodes, -1);
    vector<int> weights(nodes, INT_MAX);
    vector<bool> inMST(nodes, false);

    weights[0] = 0;

    for (int i = 0; i < nodes - 1; i++) {
        int minVertex = findMinVertex(weights, inMST, nodes);
        inMST[minVertex] = true;

        for (const auto &neighbor : graph[minVertex]) {
            int adjVertex = neighbor.first;
            int edgeWeight = neighbor.second;

            if (!inMST[adjVertex] && edgeWeight < weights[adjVertex]) {
                weights[adjVertex] = edgeWeight;
                parent[adjVertex] = minVertex;
            }
        }
    }

    cout << "Minimum Spanning Tree (MST):\n";
    for (int i = 1; i < nodes; i++) {
        cout << parent[i] << " - " << i << " : " << weights[i] << endl;
    }
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<pair<int, int>>> graph(nodes);

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    primsAlgorithm(graph, nodes);

    return 0;
}
//Code for job distribution optimisation using floyds algorithm
Here is the C++ code for Job Distribution Optimization using Floyd's Algorithm:

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "Optimized Job Distribution Matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of locations: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix (use " << INF << " for no direct route):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    floydWarshall(graph, n);

    return 0;
}
