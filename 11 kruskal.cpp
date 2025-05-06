#include<bits/stdc++.h>
using namespace std;
 
class DisjointSet{
    vector<int>parent ,size;
 
    public:
 
    DisjointSet(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i=0 ;i<n ;i++){
            parent[i]=i;
        }
    }
 
    int findUPar(int node){
        if(node==parent[node]) return node;
        return parent[node]= findUPar(parent[node]);
    }
 
    void unionBySize(int u ,int v){
        int u_ulp= findUPar(u);
        int v_ulp= findUPar(v);
        if(size[u_ulp]=size[v_ulp]) return;
        if(size[u_ulp]>size[v_ulp]){
            parent[v_ulp]= u_ulp;
            size[u_ulp]+=size[v_ulp];
        }
        else {
            parent[u_ulp]= v_ulp;
            size[v_ulp]+=size[u_ulp];
        }
    }
};
 
class Solution{
    public:
      int spanningTree(int V , vector<vector<int>>adj[]){
        vector<pair<int ,pair<int ,int>>>edges;
 
 
        for(int i=0 ;i<V ;i++){
            for(auto it: adj[i]){
                int adjNode= it[0];
                int w= it[1];
            if(i<adjNode){
                edges.push_back({w ,{i,adjNode}});
            }
            }
        }
 
            sort(edges.begin(), edges.end());
 
        DisjointSet ds(V);
           int mstWt = 0;
 
        for(auto it :edges){
            int wt= it.first;
            int u= it.second.first;
            int v= it.second.second;
 
            if(ds.findUPar(u)!=ds.findUPar(v)){
                    mstWt += wt;
                    ds.unionBySize(u,v);
            }
 
        }
         return mstWt;
    }
};
 
int main(){
   int V = 5; // Example: 5 vertices
    vector<vector<int>> adj[5];
 
    // Example Graph
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 6});
    adj[1].push_back({0, 2});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 8});
    adj[1].push_back({4, 5});
    adj[2].push_back({1, 3});
    adj[2].push_back({4, 7});
    adj[3].push_back({0, 6});
    adj[3].push_back({1, 8});
    adj[4].push_back({1, 5});
    adj[4].push_back({2, 7});
      Solution sol;
    cout << "Minimum Spanning Tree Weight: " << sol.spanningTree(V, adj) << endl;
 
    return 0;
 
}
