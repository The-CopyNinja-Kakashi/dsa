#include <bits/stdc++.h>
using namespace std;
 
class Solution {
public:
    // Function to find the sum of weights of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Min-heap priority queue: {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);  // Visited array
        int sum = 0;
 
        pq.push({0, 0}); // Start from node 0 with weight 0
 
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;
 
            if (vis[node]) continue;
 
            vis[node] = 1;
            sum += wt;
 
            for (auto& neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edgeWeight = neighbor[1];
                if (!vis[adjNode]) {
                    pq.push({edgeWeight, adjNode});
                }
            }
        }
 
        return sum;
    }
};
 
int main() {
    int V = 9;
    vector<vector<int>> adj[V];
 
    // Graph from the image (edges with weights)
    vector<vector<int>> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11},
        {2, 3, 7}, {2, 8, 2}, {2, 5, 4}, {3, 4, 9},
        {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 8, 6},
        {6, 7, 1}, {7, 8, 7}
    };
 
    // Building the adjacency list
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    }
 
    Solution obj;
    int totalCost = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights in the MST: " << totalCost << endl;
 
    return 0;
}