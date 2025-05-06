#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
class Graph {
    int n;
    vector<vector<int>> adjMatrix;
    vector<bool> visited;
 
public:
    Graph(int nodes) : n(nodes), adjMatrix(n, vector<int>(n, 0)), visited(n, false) {}
 
    void addEdge(int u, int v) {
        adjMatrix[u][v] = adjMatrix[v][u] = 1;
    }
 
    void DFS(int v) {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < n; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i])
                DFS(i);
        }
    }
 
    void BFS(int start) {
        fill(visited.begin(), visited.end(), false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
 
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            for (int i = 0; i < n; i++) {
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
 
    int countConnectedComponents() {
        int components = 0;
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS(i);
                components++;
                cout << endl;
            }
        }
        return components;
    }
};
 
int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges: ";
    cin >> nodes >> edges;
 
    Graph g(nodes);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
 
    cout << "\nDFS traversal (connected components shown):\n";
    int components = g.countConnectedComponents();
    cout << "Number of connected components: " << components << endl;
 
    cout << "\nBFS traversal from node 0:\n";
    g.BFS(0);
 
    cout << "\n\nGraph is " << (components == 1 ? "Connected" : "Not Connected") << endl;
 
    return 0;
}