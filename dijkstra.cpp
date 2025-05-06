#include<bits/stdc++.h>
using namespace std;
/*
//using set to reduce the time complexity 
tc=eloge,elogv in case of complete graph as for complete graph E=v^2
SC=(v+v+E)=O(V+E) same in case of complete graph
no of edges in complete graph are nc2
void djkstra(vector<vector<pair<int,int>>>&adj,vector<bool>&exp,vector<int>&path,int src){
    set<pair<int,int>>p;
    p.insert({0,src});
    path[src]=0;
    while(!p.empty()){
        auto it=p.begin();
        int node = it->second;
        p.erase(it);
        if(!exp[node]){
            exp[node]=1;
            for(int j=0;j<adj[node].size();j++){
                if(!exp[adj[node][j].first]){
                    path[adj[node][j].first]=min(path[adj[node][j].first],path[node]+adj[node][j].second);
                    p.insert({path[adj[node][j].first],adj[node][j].first});
                }
            }
        }
    }
    return ;
}
//using priority queue similar to that of set insert the changed distance and then find the min form the min heap and apply the same until the heap becomes empty
tc=eloge,elogv in case of complete graph as for complete graph E=v^2
SC=(v+v+E)=O(V+E) same in case of complete graph 
no of edges in complete graph are nc2

void djkstra(vector<vector<pair<int,int>>>&adj,vector<bool>&exp,vector<int>&path,int src){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>p;
    p.push({0,src});
    path[src]=0;
    while(!p.empty()){
        int node = p.top().second;
        p.pop();
        if(!exp[node]){
            exp[node]=1;
            for(int j=0;j<adj[node].size();j++){
                if(!exp[adj[node][j].first]){
                    path[adj[node][j].first]=min(path[adj[node][j].first],path[node]+adj[node][j].second);
                    p.push({path[adj[node][j].first],adj[node][j].first});
                }
            }
        }
    }
    return ;
}
*/
void dijkstra(vector<vector<pair<int,int>>>&adj,vector<bool>&exp,vector<int>&dist,int source,vector<int>&parent){
    dist[source]=0;
    for(int i=0;i<adj.size();i++){
        int x=-1;
        int mindi=INT_MAX;
        for(int j=0;j<adj.size();j++){
            if(!exp[j] && dist[j]<=mindi){
                mindi=dist[j];
                x=j;
            }
        }
        if(x==-1){
            break;
        }
        exp[x]=1;
        for(int k=0;k<adj[x].size();k++){
            if(!exp[adj[x][k].first]){
                if(dist[x]+adj[x][k].second<dist[adj[x][k].first]){
                    parent[adj[x][k].first]=x;
                }
                dist[adj[x][k].first]=min(dist[adj[x][k].first],dist[x]+adj[x][k].second);
            }
        }
    }
}
int main(){
    int u,v;
    cout<<"enter the number of edges and vertices:\n";
    cin>>u>>v;
    vector<vector<pair<int,int>>>adj(v);
    cout<<"enter the edge and the weight btw the vertices:\n";
    for(int i=0;i<u;i++){
        int v1,v2,weight;
        cin>>v1>>v2>>weight;
        adj[v1].push_back(make_pair(v2,weight));
        adj[v2].push_back(make_pair(v1,weight));
    }
    int source;
    cout<<"enter the source:\n";
    cin>>source;
    vector<bool>exp(v,0);
    vector<int>dist(v,INT_MAX);
    vector<int>parent(v,-1);
    dijkstra(adj,exp,dist,source,parent);
    for(auto it:dist){
        cout<<it<<" ";
    }
    cout<<endl;
    vector<int>path;
    for(int i=0;i<v;i++){
        int x=i;
        while(x!=source){
            path.push_back(x);
            x=parent[x];
            if(x==-1){
                break;
            }
        }
        if(x==source){
            path.push_back(source);
            reverse(path.begin(),path.end());
            for(int j=0;j<path.size()-1;j++){
                cout<<path[j]<<"->";
            }
            cout << path[path.size() - 1] << endl;
        }
        path.clear();
    }
    return 0;
}