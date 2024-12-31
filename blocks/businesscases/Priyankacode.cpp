//JOB VACANCY DATABASE MANAGEMENT USING QUICK SORT

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to hold job details
struct Job {
    string industry;
    double salary;
    string requiredSkill;
};

// Function to partition the array
int partition(vector<Job>& jobs, int low, int high) {
    double pivot = jobs[high].salary;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (jobs[j].salary <= pivot) {
            i++;
            swap(jobs[i], jobs[j]);
        }
    }
    swap(jobs[i + 1], jobs[high]);
    return i + 1;
}

// Quick Sort implementation
void quickSort(vector<Job>& jobs, int low, int high) {
    if (low < high) {
        int pi = partition(jobs, low, high);
        quickSort(jobs, low, pi - 1);
        quickSort(jobs, pi + 1, high);
    }
}

// Function to display the jobs
void displayJobs(const vector<Job>& jobs) {
    for (const auto& job : jobs) {
        cout << "Industry: " << job.industry
             << ", Salary: " << job.salary
             << ", Required Skill: " << job.requiredSkill << endl;
    }
}

int main() {
    vector<Job> jobs = {
        {"IT", 70000, "C++"},
        {"Healthcare", 50000, "Nursing"},
        {"Education", 40000, "Teaching"},
        {"Finance", 60000, "Accounting"},
        {"Retail", 30000, "Sales"}
    };

    cout << "Before Sorting:" << endl;
    displayJobs(jobs);

    quickSort(jobs, 0, jobs.size() - 1);

    cout << "\nAfter Sorting by Salary:" << endl;
    displayJobs(jobs);

    return 0;
}

//JOB VACANCY DATABASE MANAGEMENT USING MERGE SORT
#include <iostream>
#include <vector>
using namespace std;

struct Job {
    int id;
    string industry;
    int salary;
    string requiredSkills;
};

void merge(vector<Job> &jobs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Job> leftArr(n1), rightArr(n2);
    for (int i = 0; i < n1; i++) leftArr[i] = jobs[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = jobs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].salary <= rightArr[j].salary) {
            jobs[k++] = leftArr[i++];
        } else {
            jobs[k++] = rightArr[j++];
        }
    }
    while (i < n1) jobs[k++] = leftArr[i++];
    while (j < n2) jobs[k++] = rightArr[j++];
}

void mergeSort(vector<Job> &jobs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(jobs, left, mid);
        mergeSort(jobs, mid + 1, right);
        merge(jobs, left, mid, right);
    }
}

void displayJobs(const vector<Job> &jobs) {
    for (const auto &job : jobs) {
        cout << "ID: " << job.id << ", Industry: " << job.industry
             << ", Salary: " << job.salary
             << ", Skills: " << job.requiredSkills << endl;
    }
}

int main() {
    vector<Job> jobs;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Job job;
        cin >> job.id >> job.industry >> job.salary >> job.requiredSkills;
        jobs.push_back(job);
    }

    mergeSort(jobs, 0, jobs.size() - 1);
    displayJobs(jobs);

    return 0;}


//UNEMPLOYMENT RATE CALCULATION USING DIJKSTRA'S ALGORITHM

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int nodes, vector<vector<Edge>> &graph, int start, vector<int> &dist) {
    dist.assign(nodes, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;

        for (const Edge &edge : graph[currentNode]) {
            int newDist = currentDist + edge.weight;
            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                pq.push({newDist, edge.to});
            }
        }
    }
}

int main() {
    int nodes, edges, start;
    cin >> nodes >> edges;

    vector<vector<Edge>> graph(nodes);
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Assuming undirected graph
    }

    cin >> start;

    vector<int> dist;
    dijkstra(nodes, graph, start, dist);

    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < nodes; i++) {
        cout << "To node " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
    }

    return 0;
}

//UNEMPLOYMENT RATE CALCULATION USING BELLMANFORD ALGORITHM

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int from, to, weight;
};

bool bellmanFord(int nodes, int edges, vector<Edge> &graph, int start, vector<int> &dist) {
    dist.assign(nodes, INT_MAX);
    dist[start] = 0;

    for (int i = 1; i < nodes; i++) {
        for (const Edge &edge : graph) {
            if (dist[edge.from] != INT_MAX && dist[edge.from] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (const Edge &edge : graph) {
        if (dist[edge.from] != INT_MAX && dist[edge.from] + edge.weight < dist[edge.to]) {
            return false; // Negative cycle detected
        }
    }

    return true;
}

int main() {
    int nodes, edges, start;
    cin >> nodes >> edges;

    vector<Edge> graph(edges);
    for (int i = 0; i < edges; i++) {
        cin >> graph[i].from >> graph[i].to >> graph[i].weight;
    }

    cin >> start;

    vector<int> dist;
    if (bellmanFord(nodes, edges, graph, start, dist)) {
        cout << "Shortest distances from node " << start << ":\n";
        for (int i = 0; i < nodes; i++) {
            cout << "To node " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
        }
    } else {
        cout << "Negative-weight cycle detected.\n";
    }

    return 0;
}

//ECONOMIC INEQUALITY REPORTING USING BFS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to perform BFS to explore economic inequality relationships
void BFS(const vector<vector<int>>& graph, int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[current][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

// Function to report economic inequality relationships
void economicInequalityReport(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);

    cout << "Economic Inequality Relationships Report:\n";
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            cout << "Group connected to region " << i << ": ";
            BFS(graph, i, visited);
            cout << endl;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of regions or groups: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix (1 for direct inequality relationship, 0 otherwise):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    economicInequalityReport(graph);

    return 0;
}

//ECONOMIC INEQUALITY REPORTING USING WARSHALL'S

#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9 // Represents no direct connection

// Warshall's Algorithm to compute the transitive closure (reachability matrix)
void warshallAlgorithm(vector<vector<int>>& graph, int n) {
    vector<vector<int>> reach = graph;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }

    cout << "Economic Inequality Reachability Matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << reach[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of regions or groups: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix (1 for direct inequality relationship, 0 otherwise):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    warshallAlgorithm(graph, n);

    return 0;
}
