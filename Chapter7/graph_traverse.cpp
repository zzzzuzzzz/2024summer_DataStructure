//图的遍历
//洛谷P3916

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
int A[100001];

void dfs(int index, int start);

int main(){
    int n, m;
    cin>>n>>m;
    graph.resize(n+1);
    for (int i=0; i<m; i++)
    {
        int u, v;
        cin>>u>>v;
        graph[v].push_back(u);   //反向建边
    }
    for (int i=n; i>0; i--)
    {
        dfs(i, i);
    }
    for (int i=1; i<=n; i++)
    {
        cout<<A[i]<<' ';
    }
    return 0;
}

void dfs(int index, int start){
    if (A[index]) return;
    A[index] = start;
    for (int i: graph[index])
    {
        if (A[i]==0)
        {
            dfs(i, start);
        }
    }
}