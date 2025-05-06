#include <bits/stdc++.h>
using namespace std;
 
 
class Solution{
    public:
 
vector<int>Dijkstra(int V , vector<vector<int>>adj[] ,int S){
    priority_queue<pair<int ,int> ,vector<pair<int ,int>> ,greater<pair<int,int>>>pq;
 
    vector<int>dis(V ,INT_MAX);
 
    dis[S]=0;
 
    pq.push({0,S});
 
 
    while(!pq.empty()){
        int distance= pq.top().first;
        int node= pq.top().second;
        pq.pop();
 
        for(auto it: adj[node]){
            int adjNode= it[0];
            int weight= it[1];
 
            if(distance+ weight < dis[adjNode]){
                dis[adjNode]= distance+weight;
                pq.push({dis[adjNode] ,adjNode});
            }
        }
    }
    return dis;
}
};
 
int main(){
    int V=9;
    vector<vector<int>>adj[9];
      adj[0].push_back({1, 4});
    adj[0].push_back({7, 8});
    adj[1].push_back({0, 4});
    adj[1].push_back({2, 8});
    adj[1].push_back({7, 11});
    adj[2].push_back({1, 8});
    adj[2].push_back({3, 7});
    adj[2].push_back({8, 2});
    adj[2].push_back({5, 4});
    adj[3].push_back({2, 7});
    adj[3].push_back({4, 9});
    adj[3].push_back({5, 14});
    adj[4].push_back({3, 9});
    adj[4].push_back({5, 10});
    adj[5].push_back({2, 4});
    adj[5].push_back({3, 14});
    adj[5].push_back({4, 10});
    adj[5].push_back({6, 2});
    adj[6].push_back({5, 2});
    adj[6].push_back({7, 1});
    adj[6].push_back({8, 6});
    adj[7].push_back({0, 8});
    adj[7].push_back({1, 11});
    adj[7].push_back({6, 1});
    adj[7].push_back({8, 7});
    adj[8].push_back({2, 2});
    adj[8].push_back({6, 6});
    adj[8].push_back({7, 7});
 
    Solution sol;
    vector<int> distances = sol.Dijkstra(V, adj, 0);
 
    cout << "Shortest distances from source vertex 0:\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }
 
    return 0;
 
}