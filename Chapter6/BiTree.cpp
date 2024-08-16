//二叉树的遍历
//洛谷P3642

#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int lchild, rchild;
};

void PreOrderTraverse(vector<Node>& BiTree, int index);
void InOrderTraverse(vector<Node>& BiTree, int index);
void PostOrderTraverse(vector<Node>& BiTree, int index);

int main(){
    int n;
    cin>>n;
    vector<Node> BiTree;
    BiTree.resize(n+1);
    for (int i=1; i<=n; i++)
    {
        int l, r;
        cin>>l>>r;
        BiTree[i].lchild = l;
        BiTree[i].rchild = r;
    }
    PreOrderTraverse(BiTree, 1);
    cout<<endl;
    InOrderTraverse(BiTree, 1);
    cout<<endl;
    PostOrderTraverse(BiTree, 1);
    return 0;
}

void PreOrderTraverse(vector<Node>& BiTree, int index){
    if (index==0) return;
    cout<<index<<' ';
    PreOrderTraverse(BiTree, BiTree[index].lchild);
    PreOrderTraverse(BiTree, BiTree[index].rchild);
}

void InOrderTraverse(vector<Node>& BiTree, int index){
    if (index==0) return;
    InOrderTraverse(BiTree, BiTree[index].lchild);
    cout<<index<<' ';
    InOrderTraverse(BiTree, BiTree[index].rchild);
}

void PostOrderTraverse(vector<Node>& BiTree, int index){
    if (index==0) return;
    PostOrderTraverse(BiTree, BiTree[index].lchild);
    PostOrderTraverse(BiTree, BiTree[index].rchild);
    cout<<index<<' ';
}