#include<bits/stdc++.h>
using namespace std;
//using set prims algo for mst 
void prims_algo_set(vector<vector<pair<int,int>>>&adj,vector<bool>&visit,vector<int>&mst,int &cost,vector<int>&parent){
    set<pair<int,int>>s1;// u can also use priority queue in oreder to store the pair 
    s1.insert({0,0});
    while(!s1.empty()){
        auto it=s1.begin();
        int node=it->second;// we are using this as because after deleting the pointer or iterator we cannot directly access the value pointer by the iterator so we have to store the value of the variable pointed by the iterator before erasing it from the set as the iterator becomes invalid after erasing it from the set
        int wt=it->first;//same here
        s1.erase(it);// after deleting the iterator from the set the iterator itself become invalid so we cannot directly access the value like it->first or it->second
        if(!visit[node]){
            cost+=wt;
            mst.push_back(node);
            visit[node]=1;
            for(int i=0;i<adj[node].size();i++){
                if(!visit[adj[node][i].first]){
                    s1.insert({adj[node][i].second,adj[node][i].first});
                    parent[adj[node][i].first]=node;//just update the parent of each node as the parent is the index at which the edges are stored for other vertices after insertion in the set or min heap or priority queue 
                }
            }
        }
    }
    return;
}
//using set kruskal algo for mst
void kruskal_algo(vector<vector<pair<int,int>>>&adj,vector<int>&mst,int &cost,vector<int>group){
    set<pair<int,pair<int,int>>>s1;// set having a pair of (wt,pair of the edges having the weight(u,v))
    for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){   //                                      0->0->(u1,wt1) =>(0,u1,wt1)
            if(i<adj[i][j].first){  //to remove the duplicate value from the queue  0->1->(u2,wt2)
                s1.insert({adj[i][j].second,{i,adj[i][j].first}});// adding all the edges in the min heap or the priority queue using set 
            }
        }
    }
    while(mst.size()<group.size()-1){// as the size of group is equal to v which is 9 so we want to stop at the point where the size of our mst becomes equal to 8 
        auto it=s1.begin();
        int wt=it->first;
        int u=it->second.first;
        int v=it->second.second;
        s1.erase(it);
        int gu = group[u];
        int gv = group[v];
        if(gu != gv){// this step increases the time complexity of the algorithm so we will use the methord called as the union of the disjoint set on the basis of rank including steps like find ultimate parent and then merge by rank , path compression
            mst.push_back(v); 
            cost += wt;
            for(int i = 0; i < group.size(); i++) {// bring all the element having the group value=v becomes a part of the group u
                if(group[i] == gv) {
                    group[i] = gu;
                }
            }
        }
    }
    return;
}
int find_parent(vector<int>&parent,int u){
    if(parent[u]==u){
        return u;
    }
    return parent[u]=find_parent(parent,parent[u]);
}
bool union_by_rank(int u,int v,vector<int>&parent,vector<int>&rank){
    int pu=find_parent(parent,u);
    int pv=find_parent(parent,v);
    if(pu==pv){
        return false;
    }
    if(rank[pu]>rank[pv]){
        parent[pv]=pu;
    }
    else if(rank[pu]<rank[pv]){
        parent[pu]=pv;
    }
    else if(rank[pu]==rank[pv]){
        parent[pu]=pv;
        rank[pu]++;
    }
    return true;
}
void kruskal_algo_opt(vector<vector<pair<int,int>>>&adj,vector<int>&mst,int &cost,vector<int>&parent,vector<int>&rank){
    set<pair<int,pair<int,int>>>s1;
    for(int i=0;i<adj.size();i++){
        for(int j=0;j<adj[i].size();j++){
            if(i<adj[i][j].first){// to remove duplicate edges from the set as in undirected graph one edge gets added to the set twice therefore the second edge has v<u hence using this condition we avoid the insertion of the second edge
                s1.insert({adj[i][j].second,{i,adj[i][j].first}});
            }
        }
    }
    while(mst.size()<parent.size()-1){
        auto it=s1.begin();
        int u=it->second.first;
        int v=it->second.second;
        int wt=it->first;
        s1.erase(it);
        if(union_by_rank(u,v,parent,rank)){
            mst.push_back(v);
            cost+=wt;
        }
    }
    return;
}
int main(){
    int u,v;
    cout<<"enter the number of edges and vertices:\n";
    cin>>u>>v;
    vector<vector<pair<int,int>>>adj(v);
    cout<<"enter the edges and there weights:\n";
    for(int i=0;i<u;i++){
        int v1,v2,weight;
        cin>>v1>>v2>>weight;
        adj[v1].push_back(make_pair(v2,weight));
        adj[v2].push_back(make_pair(v1,weight));
    }
    vector<bool>visit(v,0);
    vector<int>mst;
    vector<int>parent(v,-1);// the only need for this parent array is that we can make the mst using this array like  we did in the dijkstra algo for printing the path or the root 
    int cost=0;
    int choise;
    cout<<"enter the choise:"<<endl;
    cin>>choise;
    if(choise==1){
        prims_algo_set(adj,visit,mst,cost,parent);
        cout<<"the cost of the mst:\n"<<cost<<endl;
        for(auto it:mst){
            cout<<it<<" ";
        }
        cout<<endl;
        for(int i=0;i<parent.size();i++){
            cout<<i<<" Parent="<<parent[i]<<endl;
        }
    }
    else if(choise==2){
        vector<int>set(v);
        for(int i=0;i<v;i++){
            set[i]=i;
        }
        kruskal_algo(adj,mst,cost,set);
        cout<<"the cost of the mst:\n"<<cost<<endl;
        for(auto it:mst){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    else if(choise==3){
        vector<int>parent1(v);
        vector<int>rank(v,0);
        for(int i=0;i<v;i++){
            parent1[i]=i;
        }
        kruskal_algo_opt(adj,mst,cost,parent1,rank);
        cout<<"the cost of the mst:"<<cost<<endl;
        cout<<"the edges of the mst:";
        for(auto it:mst){
            cout<<it<<" ";
        }
        cout<<endl;
    }

    return 0;
}