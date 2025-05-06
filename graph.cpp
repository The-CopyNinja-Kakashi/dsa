#include<bits/stdc++.h>
using namespace std;
void BFS_traversal(vector<vector<pair<int,int>>>&adj,vector<int>&ans,int source){//TC=O(V+2E) each edge will be included twice  SC=O(V)
    vector<bool>visit(adj.size(),0);//NOTE: sometime what happens is that the graph is devided into peices ie the part of the graph are not connected to each other therfore we have to apply traversal for each node individualy in the graph
    queue<int>q1;
    q1.push(source);
    visit[source]=1;
    while(!q1.empty()){
        int top=q1.front();
        q1.pop();
        ans.push_back(top);
        for(int i=0;i<adj[top].size();i++){
            if(!visit[adj[top][i].first]){
                q1.push(adj[top][i].first);
                visit[adj[top][i].first]=1;
            }
        }
    }
}
void DFS_traversal(vector<int>&ans,vector<vector<pair<int,int>>>&adj,int x,vector<bool>&visit){//TC=O(v+e) SC=O(v)
    if(visit[x]){
        return ;
    }
    ans.push_back(x);
    visit[x]=1;
    for(int i=0;i<adj[x].size();i++){
        DFS_traversal(ans,adj,adj[x][i].first,visit);
    }
    return ;
}
void DFS_stack(vector<int>&ans,vector<vector<pair<int,int>>>&adj,int x,vector<bool>&visit){
    stack<int>s1;
    s1.push(x);
    visit[x]=1;
    while(!s1.empty()){
        int x=s1.top();
        s1.pop();
        ans.push_back(x);
        for(int i=0;i<adj[x].size();i++){
            if(!visit[adj[x][i].first]){
                s1.push(adj[x][i].first);
                visit[adj[x][i].first]=1;
            }
        }
    }
}
bool detect_cycle(vector<vector<pair<int,int>>>&adj,vector<bool>&visit,int curr,int prev ){
    visit[curr]=1;
    for(int i=0;i<adj[curr].size();i++){
        if(adj[curr][i].first==prev){
            continue;
        }
        else if(visit[adj[curr][i].first]==1){
            return true;
        }
        if(detect_cycle(adj,visit,adj[curr][i].first,curr)){
            return true;
        }
    }
    return false;
}
bool detect_cycle_d(vector<vector<pair<int,int>>>&adj,vector<bool>&path,int i){
    if(path[i]==1){
        return true;
    }
    path[i]=1;
    for(int j=0;j<adj[i].size();j++){
        if(path[adj[i][j].first]==1){
            return true;
        }
        path[adj[i][j].first]=1;
        if(detect_cycle_d(adj,path,adj[i][j].first)){
            return true;
        }
        path[adj[i][j].first]=0;
    }
    return false;
}
int main(){
    /*int u,v;
    cout<<"enter the number of vertex and edges:"<<endl;
    cin>>u>>v;
    vector<vector<bool>>adj_matrix(u,vector<bool>(u,0));
    for(int i=0;i<v;i++){
        int j,k;
        cout<<"enter the vertex having the edge between them\n";
        cin>>j>>k;
        adj_matrix[j][k]=1;
        adj_matrix[k][j]=1;
    }
    for(int i=0;i<u;i++){
        for(int j=0;j<u;j++){
            cout<<adj_matrix[i][j]<<" ";
        }
        cout<<endl;
    }*/
    int u,v;
    cout<<"enter the number of node and edges:\n";
    cin>>u>>v;
    vector<vector<pair<int,int>>>adj(u);
    for(int i=0;i<v;i++){
        int x,y,weight;
        cin>>x>>y>>weight;
        adj[x].push_back({y,weight});
        adj[y].push_back({x,weight});
    }
    for(int i=0;i<u;i++){
        cout<<i<<"->";
        for(int j=0;j<adj[i].size();j++){
            cout<<"{"<<adj[i][j].first<<","<<adj[i][j].second<<"}"<<" ";
        }
        cout<<endl;
    }
    cout<<"menu:\n 1.BFS traversal on graph\n 2.DFS traversal on graph \n";
    int choise;
    cout<<"enter the choise:\n";
    cin>>choise;
    if(choise==1){
        int x;
        cout<<"enter the source:\n";
        cin>>x;
        cout<<"the BFS traversal on graph from source "<<x<<":\n";
        vector<int>ans;
        BFS_traversal(adj,ans,x);
        for(auto it:ans){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    else if(choise==2){
        int x;
        cout<<"enter the source:\n";
        cin>>x;
        cout<<"the BFS traversal on graph from source "<<x<<":\n";
        vector<int>ans;
        vector<bool>visit(u);
        DFS_traversal(ans,adj,x,visit);
        for(auto it:ans){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    else if(choise==3){
        int x;
        cout<<"enter the source:\n";
        cin>>x;
        cout<<"the BFS traversal on graph from source "<<x<<":\n";
        vector<int>ans;
        vector<bool>visit(u);
        DFS_stack(ans,adj,x,visit);
        for(auto it:ans){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    else if(choise==4){
        vector<bool>visit(u,0);
        bool ans=false;
        for(int i=0;i<u;i++){
            ans=detect_cycle(adj,visit,i,-1);
            if(ans){
                break;
            }
        }
        cout<<ans<<endl;
    }
    else if(choise==5){
        //topological sort (works only on directed acyclic graph only)
    }
    else if(choise==6){
        vector<bool>visit(v,0);
        vector<bool>path(v,0);
        for(int i=0;i<v;i++){
            if(!visit[i] && detect_cycle_d(adj,path,i)){
                cout<<"YES\n";
            }
        }
        cout<<"NO cycle\n";
    }
    return 0;
}