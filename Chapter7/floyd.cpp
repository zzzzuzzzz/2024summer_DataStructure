//最短路(floyd)
//洛谷P3647

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int m, n;
int dist[101][101];

void floyd();

int main(){
    cin>>n>>m;
    for (int i=1; i<=n; i++)
        for (int j=i+1; j<=n; j++)
            dist[i][j] = dist[j][i] = INT_MAX;
    for (int i=0; i<m; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        if (w<dist[u][v])
        {
            dist[u][v] = dist[v][u] = w;
        }
    }
    floyd();
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            cout<<dist[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}

void floyd(){
    for (int k=1; k<=n; k++)
    {
        for (int u=1; u<=n; u++)
        {
            for (int v=1; v<=n; v++)
            {
                if (dist[u][v] > dist[u][k] + dist[k][v] && dist[u][k] + dist[k][v] > 0) //防止溢出
                {
                    dist[u][v] = dist[v][u] = dist[u][k] + dist[k][v];
                }
            }
        }
    }
}