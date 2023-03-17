#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

int bfs(int rGraph[20][20], int s, int t, int parent[])
{

    bool visited[20];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;


    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<20; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }


    return (visited[t] == true);
}


void dfs(int rGraph[20][20], int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < 20; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}

void minCut(int graph[20][20], int s, int t)
{
    int u, v;
    int max_flow = 0;
    int rGraph[20][20];
    for (u = 0; u < 20; u++)
        for (v = 0; v < 20; v++)
             rGraph[u][v] = graph[u][v];
    int parent[20];
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);

        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    bool visited[20];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited);

    cout << max_flow<<endl;
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 20; j++)
         if (visited[i] && !visited[j] && graph[i][j])
              cout << i+1 << "  " << j+1 << endl;

    return;
}

int main()
{
    int vertexNum,edgeNum;
    cin>>vertexNum>>edgeNum;

    int graph[20][20]={0};

    for(int i=0;i<edgeNum;i++)
    {
        int u,v;
        cin>>u>>v;
        graph[u-1][v-1] = 1;
        graph[v-1][u-1] = 1;

    }
    cout << "*****************"<<endl;
    minCut(graph, 0, vertexNum-1);

    return 0;
}
