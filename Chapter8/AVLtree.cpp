//平衡二叉树
//洛谷P3369

#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct Node{
    int data;
    int height;
    Node* lchild, *rchild;
};

class AVLtree{
public:
    Node* root = nullptr;
    bool Insert(Node*& T, const int& x);
    void Delete(Node*& T, const int& x);
    int getRank(const int& x);
    int getNumbyRank(const int& rank);
    int getPre(const int& x);
    int getNext(const int& x);
};

int getHeight(Node* T); //获取树高
int getBF(Node* T); //获取平衡因子
void PreOrder(Node* root);
void InOrder(Node* root);
//四种旋转操作
void LL_Rotation(Node*& T);
void LR_Rotation(Node*& T);
void RR_Rotation(Node*& T);
void RL_Rotation(Node*& T);

int main(){
    int n;
    cin>>n;
    AVLtree T;
    for (int i=0; i<n; i++)
    {
        int op, x;
        cin>>op>>x;
        switch (op)
        {
        case 1:
            T.Insert(T.root, x);
            break;
        case 2:
            T.Delete(T.root, x);
            break;
        case 3:
            cout<<T.getRank(x)<<endl;
            break;
        case 4:
            cout<<T.getNumbyRank(x)<<endl;
            break;
        case 5:
            cout<<T.getPre(x)<<endl;
            break;
        case 6:
            cout<<T.getNext(x)<<endl;
            break;
        default:
            break;
        }
    }
    return 0;
}

int getHeight(Node* T){
    if (T==nullptr)
        return 0;
    return T->height;
}

int getBF(Node* T){
    return getHeight(T->lchild) - getHeight(T->rchild);
}

void LL_Rotation(Node*& T){
    Node* L = T->lchild;
    T->lchild = L->rchild;
    L->rchild = T;
    T->height = 1 + max(getHeight(T->lchild), getHeight(T->rchild));
    L->height = 1 + max(getHeight(L->lchild), getHeight(L->rchild));
    T = L;
}

void LR_Rotation(Node*& T){
    RR_Rotation(T->lchild);
    LL_Rotation(T);
}

void RR_Rotation(Node*& T){
    Node* R = T->rchild;
    T->rchild = R->lchild;
    R->lchild = T;
    T->height = 1 + max(getHeight(T->lchild), getHeight(T->rchild));
    R->height = 1 + max(getHeight(R->lchild), getHeight(R->rchild));
    T = R;
}

void RL_Rotation(Node*& T){
    LL_Rotation(T->rchild);
    RR_Rotation(T);
}

bool AVLtree::Insert(Node*& T, const int& x){
    if (T==nullptr)
    {
        T = new Node;
        T->data = x;
        T->lchild = T->rchild = nullptr;
        T->height = 1;
    }
    else
    {
        //cout<<"data:"<<T->data<<endl;
        if (x <= T->data) //尝试在左子树中插入
        {
            if (Insert(T->lchild, x)==false) return false;
        }
        else
        {
            if (Insert(T->rchild, x)==false) return false;
        }
    }
    //更新树高
    T->height = 1 + max(getHeight(T->lchild), getHeight(T->rchild));
    //当前节点的平衡因子
    int CurrentBF = getBF(T);
    //cout<<"Node "<<T->data<<" height: "<<T->height<<" bf: "<<CurrentBF<<endl;;
    //判断是否失衡
    //LL
    if (CurrentBF==2 && getBF(T->lchild)>0)
    {
        LL_Rotation(T);
    }
    //LR
    if (CurrentBF==2 && getBF(T->lchild)<0)
    {
        LR_Rotation(T);
    }
    //RR
    if (CurrentBF==-2 && getBF(T->rchild)<0)
    {
        RR_Rotation(T);
    }
    //RL
    if (CurrentBF==-2 && getBF(T->rchild)>0)
    {
        RL_Rotation(T);
    }
    return true;
}

void AVLtree::Delete(Node*& T, const int& x){
    if (T==nullptr) return;
    else
    {
        //cout<<"data: "<<T->data<<endl;
        if (x == T->data)
        {
            //只有左孩子
            if (T->rchild==nullptr)
            {
                Node* temp = T;
                T = T->lchild;
                delete temp;
            }
            //只有右孩子
            else if (T->lchild==nullptr)
            {
                Node* temp = T;
                T = T->rchild;
                delete temp;
            }
            //有左孩子和右孩子，则选择前驱来替代当前节点
            else
            {
                Node* pre = T;
                Node* now = T->lchild;
                while (now->rchild!=nullptr)
                {
                    pre = now;
                    now = now->rchild;
                }
                //cout<<"pre: "<<pre->data<<" now: "<<now->data<<endl;
                T->data = now->data;
                if (pre==T) 
                {
                    T->lchild = now->lchild;
                }
                else
                {
                    pre->rchild = now->lchild;
                }
                delete now;
            }
            return;
        }
        else if (x < T->data)
        {
            return Delete(T->lchild, x);
        }
        else
        {
            return Delete(T->rchild, x);
        }
    }
}

int AVLtree::getRank(const int& x){
    stack<Node*> s;
    int rank = 1;
    Node* cur = root;
    while (cur!=nullptr || !s.empty())
    {
        if (cur!=nullptr)
        {
            s.push(cur);
            cur = cur->lchild;
        }
        else
        {
            cur = s.top();
            if (cur->data < x) rank ++;
            else return rank;
            s.pop();
            cur = cur->rchild;
        }
    }
}

int AVLtree::getNumbyRank(const int& rank){
    stack<Node*> s;
    int cnt = 0;
    Node* cur = root;
    while (cur!=nullptr || !s.empty())
    {
        if (cur!=nullptr)
        {
            s.push(cur);
            cur = cur->lchild;
        }
        else
        {
            cur = s.top();
            cnt ++;
            if (cnt==rank) return cur->data;
            s.pop();
            cur = cur->rchild;
        }
    }
}

int AVLtree::getPre(const int& x){
    stack<Node*> s;
    Node* cur = root;
    while (cur!=nullptr || !s.empty())
    {
        if (cur!=nullptr)
        {
            s.push(cur);
            cur = cur->rchild;
        }
        else
        {
            cur = s.top();
            if (cur->data < x) return cur->data;
            s.pop();
            cur = cur->lchild;
        }
    }
}

int AVLtree::getNext(const int& x){
    stack<Node*> s;
    Node* cur = root;
    while (cur!=nullptr || !s.empty())
    {
        if (cur!=nullptr)
        {
            s.push(cur);
            cur = cur->lchild;
        }
        else
        {
            cur = s.top();
            if (cur->data > x) return cur->data;
            s.pop();
            cur = cur->rchild;
        }
    }
}

void PreOrder(Node* root){
    if (root==nullptr) return;
    cout<<root->data<<' ';
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void InOrder(Node* root){
    if (root==nullptr) return;
    InOrder(root->lchild);
    cout<<root->data<<' ';
    InOrder(root->rchild);
}