//拓扑排序
//洛谷P3644

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<int>> graph;
vector<int> indeg; //记录每个点的入度

void TopologicalSort();

int main(){
    cin>>n;
    graph.resize(n+1);
    indeg.resize(n+1);
    for (int i=1; i<=n; i++)
    {
        int a;
        cin>>a;
        while (a)
        {
            graph[i].push_back(a);
            indeg[a] ++;
            cin>>a;
        }
    }
    TopologicalSort();
    return 0;
}

void TopologicalSort(){
    queue<int> q;
    for (int i=1; i<=n; i++)
    {
        if (indeg[i]==0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int x = q.front();
        cout<<x<<' ';
        q.pop();
        for (int i: graph[x])
        {
            indeg[i] --;
            if (indeg[i]==0)
            {
                q.push(i);
            }
        }
    }
    
}