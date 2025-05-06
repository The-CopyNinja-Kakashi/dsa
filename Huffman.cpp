#include<bits/stdc++.h>
using namespace std;
class node{
    private:
        char c;
        int freq;
        node*left;
        node*right;
    public:
        node(node*l,node*r,int f){
            c='#';
            left=l;
            right=r;
            freq=f;
        }
        node(char d,int f){
            c=d;
            left=nullptr;
            right=nullptr;
            freq=f;
        }
        friend void insert(map<char,int>&mp,vector<pair<node*,int>>&v);
        friend void exploit(vector<pair<node*,int>>&v);
        friend string printx(string s,char r,node*temp);
};
bool sort_pair(const pair<node*,int>&a,const pair<node*,int> &b){
    return a.second<b.second;
}
void insert(map<char,int>&mp,vector<pair<node*,int>>&v){
    if(mp.size()==0){
        v.push_back({nullptr,0});
        return ;
    }
    for(auto it:mp){
        node*newnode=new node(it.first,it.second);
        v.push_back({newnode,it.second});
    }
}
void exploit(vector<pair<node*,int>>&v){
    while(v.size()>1){
        sort(v.begin(),v.end(),sort_pair);
        node*l=v[0].first;
        node*r=v[1].first;
        int merge_freq=v[0].second+v[1].second;
        node*newnode=new node(l,r,merge_freq);
        v.erase(v.begin());
        v.erase(v.begin());
        v.push_back({newnode,merge_freq});
    }
}
string printx(string s,char r,node*temp){
    if(!temp){
        return "";
    }
    if(temp->c==r){
        return s;
    }
    string left=printx(s+'0',r,temp->left);
    if(!left.empty()){
        return left;
    }
    string right=printx(s+'1',r,temp->right);
    if(!right.empty()){
        return right;
    }
    return "";
}
int main(){
    map<char,int>mp;
    cout<<"enter the number of char you want to insert:\n";
    int n;
    cin>>n;
    while(n!=0){
        cout<<"enter the character and its frequency:\n";
        int freq;
        char c;
        cin>>c>>freq;
        if(mp.find(c)==mp.end()){
            mp[c]=freq;
        }
        else{
            cout<<"map already contains the character!!!\n";
        }
        n--;
    }
    vector<pair<node*,int>>p;
    insert(mp,p);
    exploit(p);
    char r;
    cout<<"enter the char for which you want the huffman code:\n";
    cin>>r;
    string s;
    if(r=='!'){
        for(auto it:mp){
            string code=printx("",it.first,p[0].first);
            cout<<it.first<<"->"<<code<<endl;
        }
    }
    else{
        string code=printx("",r,p[0].first);
        cout<<code<<endl;
    }
    return 0;
}