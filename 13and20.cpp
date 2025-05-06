#include <bits/stdc++.h>
using namespace std;
 
// ---------- DFS Topological Sort ----------
void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfs(it, adj, vis, st);
    }
    st.push(node);
}
 
vector<int> TopoDFS(int V, vector<vector<int>>& adj) {
    vector<int> vis(V, 0);
    stack<int> st;
 
    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs(i, adj, vis, st);
    }
 
    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}
 
// ---------- BFS Topological Sort (Kahn’s Algorithm) ----------
vector<int> TopoBFS(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
 
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }
 
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }
 
    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);
 
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }
 
    return topo;
}
 
int main() {
    int V = 6;
    vector<vector<int>> adj(V);
 
    // Edges
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);
 
    // DFS-based Topological Sort
    vector<int> resultDFS = TopoDFS(V, adj);
    cout << "Topological Sort using DFS:\n";
    for (int node : resultDFS) cout << node << " ";
    cout << "\n";
 
    // BFS-based Topological Sort (Kahn's Algorithm)
    vector<int> resultBFS = TopoBFS(V, adj);
    cout << "Topological Sort using BFS (Kahn’s Algorithm):\n";
    for (int node : resultBFS) cout << node << " ";
    cout << "\n";
 
    return 0;
}