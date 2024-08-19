//最短路(dijkstra)
//洛谷P3371

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Edge{
    int end, weight; //记录边的终点和权重
};

int m, n, s;
vector<vector<Edge>> graph;
int dist[100001]; //记录每个点到源的最短距离
bool done[100001]; //记录每个点是否已经确定了最短距离

void dijkstra();

int main(){
    cin>>n>>m>>s;
    graph.resize(n+1);
    for (int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        Edge e{v, w};
        graph[u].push_back(e);
    }
    dijkstra();
    for (int i=1; i<=n; i++)
    {
        cout<<dist[i]<<' ';
    }
    return 0;
}

void dijkstra(){
    //初始化
    for (int i=1; i<=n; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;
    
    for (int i=1; i<=n-1; i++)
    {
        int minimum = INT_MAX, index = 0;
        for (int j=1; j<=n; j++)
        {
            if (!done[j] && dist[j]<minimum)
            {
                minimum = dist[j];
                index = j;
            }
        }
        done[index] = true;
        //将index加入最短路后更新与其他点的距离
        for (auto e: graph[index])
        {
            if (!done[e.end] && minimum + e.weight < dist[e.end])
            {
                dist[e.end] = minimum + e.weight;
            }
        }
    }
}