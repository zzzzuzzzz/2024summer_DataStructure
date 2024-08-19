//最小生成树
//洛谷P3366

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int prim();
int kruskal();
int find(int x);
void join(int x, int y);

int graph[5001][5001];
int pre[5001];
int n, m;

struct Edge{
    int x, y, weight;
};

int main(){
    cin>>n>>m;
    for (int i=1; i<=n; i++)
        for (int j=i+1; j<=n; j++)
            graph[i][j] = graph[j][i] = INT_MAX;
    for (int i=0; i<m; i++)
    {
        int x, y, z;
        cin>>x>>y>>z;
        if (z<graph[x][y]) graph[x][y] = graph[y][x] = z;
    }
    int res = kruskal();
    if (res) cout<<res<<endl;
    else cout<<"orz"<<endl;
    return 0;
}

int prim(){
    //初始化
    int res = 0;
    int prev[n+1];
    for (int i=1; i<=n; i++) prev[i] = 1;
    int min_dist[n+1];
    for (int i=1; i<=n; i++) min_dist[i] = graph[1][i];
    for (int i=1; i<=n-1; i++)
    {
        int minimum = INT_MAX;
        int temp_index = 1; //暂时记录可以取得最短距离的点的下标
        for (int j=1; j<=n; j++)
        {
            //cout<<j<<endl;
            if (min_dist[j]!=0 && min_dist[j]<minimum)
            {
                minimum = min_dist[j];
                temp_index = j;
                //cout<<minimum<<endl;
            }
        }
        if (temp_index==1) return 0; //图非连通
        //将本轮找到的最短的边加入最小生成树中
        else
        {
            //cout<<temp_index<<" and "<<prev[temp_index]<<" with weight"<<minimum<<" are added into mst"<<endl;
            res += min_dist[temp_index];
            min_dist[temp_index] = 0;
            //更新prev和min_dist数组
            for (int j=1; j<=n; j++)
            {
                if (graph[j][temp_index]!=0 && graph[j][temp_index]<min_dist[j])
                {
                    prev[j] = temp_index;
                    min_dist[j] = graph[j][temp_index];
                }
            }
        }
    }
    return res;
}

int kruskal(){
    int res = 0, cnt = 0;
    for (int i=1; i<=n; i++)
        pre[i] = i;
    //将邻接矩阵转化为边列表
    vector<Edge> edge;
    for (int i=1; i<=n; i++)
    {
        for (int j=i+1; j<=n; j++)
        {
            if (graph[i][j]<INT_MAX)
            {
                Edge e{i, j, graph[i][j]};
                edge.push_back(e);
            }
        }
    }
    //按边权排序
    sort(edge.begin(), edge.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    for (int i=0; i<edge.size(); i++)
    {
        if (find(edge[i].x) != find(edge[i].y))
        {
            cnt ++;
            res += edge[i].weight;
            join(edge[i].x, edge[i].y);
        }
    }
    if (cnt<n-1) return 0;
    return res;
}

int find(int x){
    int r = x;
    while (r!=pre[r])
    {
        r = pre[r];
    }
    int y = x;
    while (y!=r)
    {
        y = pre[y];
        pre[x] = r;
        x = y;
    }
    return r;
}

void join(int x, int y){
    pre[find(x)] = find(y);
}