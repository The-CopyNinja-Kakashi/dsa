#include<bits/stdc++.h>//topo sort oly works for directed acyclic graph only 
using namespace std;
void topo_sort(vector<vector<int>>&adj,stack<int>&s1,vector<bool>&visit,int i){
    if(visit[i]){
        return;
    }
    visit[i]=1;
    for(int j=0;j<adj[i].size();j++){
        topo_sort(adj,s1,visit,adj[i][j]);
    }
    s1.push(i);
}
void topo_sort_b(vector<vector<int>>&adj,vector<int>&indegree,vector<bool>&visit,vector<int>&ans){
    queue<int>q1;
    for(int j=0;j<indegree.size();j++){
        if(indegree[j]==0){
            q1.push(j);
        }
    }
    while(!q1.empty()){
        int top=q1.front();
        q1.pop();
        for(int i=0;i<adj[top].size();i++){
            indegree[adj[top][i]]--;
            if(indegree[adj[top][i]]==0){
                visit[adj[top][i]]=1;
                q1.push(adj[top][i]);
            }
        }
        ans.push_back(top);
    }
}
int main(){
    int u,v;
    cout<<"enter the edges and vertex:\n";
    cin>>u>>v;
    vector<vector<int>>adj(v);
    for(int i=0;i<u;i++){
        cout<<"enter the edges: ";
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
    }
    int choise;
    cout<<"menu:\n 1.toposort using dfs\n 2.toposort using bfs\n";
    cout<<"enter the choise :\n";
    cin>>choise;
    while(choise){
        if(choise==1){
            stack<int>s1;
            cout<<"the topo sort of the given adj list: \n";
            vector<bool>visit(v,0);
            for(int i=0;i<v;i++){
                if(!visit[i]){
                    topo_sort(adj,s1,visit,i);
                }
            }
            while(!s1.empty()){
                cout<<s1.top()<<" ";
                s1.pop();
            }
            cout<<"enter the choise:\n";
            cin>>choise;
        }
        else if(choise==2){
            vector<bool>visit(v,0);
            vector<int>indegree(v,0);
            vector<int>ans;
            for(int i=0;i<v;i++){
                for(int j=0;j<adj[i].size();j++){
                    indegree[adj[i][j]]++;
                }
            }
            for(int i=0;i<v;i++){// no need of this as because int he topo code u see theat we push all the node having zero indegree so all the disconnected component of the graph are include in the queue ther fore no need for check the visit of each node
                if(!visit[i]){
                    topo_sort_b(adj,indegree,visit,ans);//u can directly call this function similary no need to see the visit vecotr as we are not checking the visit of each node in the bfs traversal 
                }
            }
            cout<<"the topo sort of the given adj list using bfs traversal or kahn algorithm : \n";//in kahn algorithm we calculate the indegree as the node with 0 indegree are independent of the other vertex so it becomes easy to topt sort
            for(auto it:ans){
                cout<<it<<" ";
            }
            cout<<"enter the choise:\n";
            cin>>choise;
        }
    }
}