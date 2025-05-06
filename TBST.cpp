#include<bits/stdc++.h>
using namespace std;
class tbst_node{
    private:
        int data;
        tbst_node* left;
        tbst_node* right;
        bool leftchild;
        bool rightchild;
    public:
        tbst_node(int x){
            data=x;
            left=nullptr;
            right=nullptr;
            leftchild=0;
            rightchild=0;
        }
        friend class tbst_tree;
};
class tbst_tree{
    private:
        tbst_node* dummy;
    public:
        tbst_tree(){
            dummy=new tbst_node(1000);
            dummy->left=dummy;
            dummy->right=dummy;
            dummy->leftchild=0;
            dummy->rightchild=0;
        }
        tbst_node*insert(tbst_node*root,int num){//this is simple
            if(!root){
                return new tbst_node(num);
            }
            if(root->data>num){
                root->left=insert(root->left,num);
                root->leftchild=1;
            }
            else if(root->data<num){
                root->right=insert(root->right,num);
                root->rightchild=1;
            }
            return root;
        }
        tbst_node* create_bst(tbst_node*dummy1){
            cout<<"menu:\n"<<"0.exit\n"<<"1.insert in bst\n";
            int choise;
            cin>>choise;
            while(choise){
                int n;
                cout<<"enter the number to be inserted in the bst:\n";
                cin>>n;
                if(!dummy1->leftchild){
                    dummy1->left=insert(nullptr,n);
                    dummy1->leftchild=1;
                }
                else{
                    dummy1->left=insert(dummy1->left,n);
                }
                cout<<"again enter the choise:\n";
                cin>>choise;
            }
            return dummy1;
        }
        void inorder(tbst_node*root1,vector<tbst_node*>&v){
            if(!root1){
                return ;
            }
            inorder(root1->left,v);
            v.push_back(root1);
            inorder(root1->right,v);
        }
        tbst_node*convert_bst(tbst_node*dummy1){
            if(!dummy1->leftchild){
                return dummy1;
            }
            tbst_node*root1=dummy1->left;
            vector<tbst_node*>v;
            inorder(root1,v);
            int n=v.size();
            v[0]->left=dummy1;
            v[0]->leftchild=0;//this is important as because if the node does not have a child then the left child should be equal to zero as we mark it to the inoreder predecessor which is not a child of the node
            v[n-1]->right=dummy1;
            v[n-1]->rightchild=0;//same here
            for(int i=0;i<n;i++){
                if(!v[i]->leftchild && i>0){//&& condition are important 
                    v[i]->left=v[i-1];
                    v[i]->leftchild=0;
                }
                if(!v[i]->rightchild && i<n-1){//same here
                    v[i]->right=v[i+1];
                    v[i]->rightchild=0;
                }
            }
            return dummy1;
        }
        tbst_node*insert_tbst(tbst_node*dummy1,int num){
            if(!dummy1->leftchild){
                tbst_node*root=new tbst_node(num);
                dummy1->left=root;
                dummy1->leftchild=1;
                root->left=dummy1;//this is genral condition
                root->right=dummy1;//this is also important as because the right remains null which gives segmentation fault for the recursive and nn recursive traversal
                return dummy1;
            }
            tbst_node*temp=dummy1->left;
            while(true){
                if(num<temp->data && !temp->leftchild){
                    tbst_node*newnode=new tbst_node(num);
                    newnode->left=temp->left;
                    newnode->right=temp;
                    temp->left=newnode;
                    temp->leftchild=1;
                    break;
                }
                else if(temp->data>num){
                    temp=temp->left;
                }
                if(num>temp->data && !temp->rightchild){
                    tbst_node*newnode=new tbst_node(num);
                    newnode->right=temp->right;
                    newnode->left=temp;
                    temp->right=newnode;
                    temp->rightchild=1;
                    break;
                }
                else if(temp->data<num){
                    temp=temp->right;
                }
            }
            return dummy1;
        }
        tbst_node*create_tbst(tbst_node*dummy1){
            int choise;
            cout<<"menu:\n 0.exit\n 1.insert in tbst\n";
            cout<<"enter the choise:\n";
            cin>>choise;
            while(choise){
                int x;
                cout<<"enter the number to be inserted:\n";
                cin>>x;
                dummy1=insert_tbst(dummy1,x);
                cout<<"enter the choise:\n";
                cin>>choise;
            }
            return dummy1;
        }
        void inorder_tbst(tbst_node* dummy1) {
            tbst_node* current = dummy1->left;
        
            // Go to the leftmost node
            while (current->leftchild) {
                current = current->left;
            }
        
            while (current != dummy1) {
                cout << current->data << " ";
                
                // If the right pointer is a thread
                if (!current->rightchild) {
                    current = current->right;
                } else {
                    // Else, go to the leftmost node in the right subtree
                    current = current->right;
                    while (current->leftchild) {
                        current = current->left;
                    }
                }
            }
        }        
        void preorder_tbst(tbst_node*dummy1){
            if(dummy1->left==dummy1){
                return;
            }
             tbst_node*temp=dummy1->left;
             while(temp!=dummy1){
                while(temp->leftchild==1){
                    cout<<temp->data<<" ";
                    temp=temp->left;
                }
                cout<<temp->data<<" ";
                while(temp->rightchild==0){
                    if(temp->right==dummy){
                        break;
                    }
                    temp=temp->right;
                }
                temp=temp->right;
             }
        }
        void recursive_preorder(tbst_node* node) {
            if (node == nullptr || node == dummy) return;
        
            cout << node->data << " ";
        
            if (node->leftchild)
                recursive_preorder(node->left);
        
            if (node->rightchild)
                recursive_preorder(node->right);
        }
        void recursive_inorder(tbst_node* node) {
            if (node == nullptr || node == dummy) return;
        
            if (node->leftchild)
                recursive_inorder(node->left);
        
            cout << node->data << " ";
        
            if (node->rightchild)
                recursive_inorder(node->right);
        }
        tbst_node*getdummy(){
            return this->dummy;
        }
        void putdummy(tbst_node*dummy1){
            this->dummy=dummy1;
            return;
        }
        tbst_node*getdummy_left(){
            return this->dummy->left;
        }
};
int main(){
    cout<<"menu:\n 1.create_bst\n 2.convert bst to tbst \n 3.create tbst \n 4.inorder travesal of tbst\n 5.preorder traversal of tbst\n 6.exit\n";
    int choise;
    cout<<"enter the choise:\n";
    cin>>choise;
    tbst_tree t1;
    while(choise){
        if(choise==1){
            t1.putdummy(t1.create_bst(t1.getdummy()));
            t1.recursive_inorder(t1.getdummy_left());
            cout<<endl;
        }
        else if(choise==2){
            t1.putdummy(t1.convert_bst(t1.getdummy()));
            t1.inorder_tbst(t1.getdummy());
            cout<<endl;
            t1.recursive_inorder(t1.getdummy_left());
            cout<<endl;
        }
        else if(choise==3){
            tbst_tree t2;
            t2.putdummy(t2.create_tbst(t2.getdummy()));
            t2.recursive_inorder(t2.getdummy_left());
            cout<<endl;
            t2.inorder_tbst(t2.getdummy());
            t2.preorder_tbst(t2.getdummy());
            t2.recursive_preorder(t2.getdummy_left());
            cout<<endl;
        }
        else if(choise==4){
            t1.inorder_tbst(t1.getdummy());
            cout<<endl;
        }
        else{
            t1.preorder_tbst(t1.getdummy());
            cout<<endl;
        }
        cout<<"enter the choise:\n";
        cin>>choise;
    }
    return 0;
}