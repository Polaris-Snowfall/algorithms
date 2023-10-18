#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct Edge
{
    unsigned int val,dst;
}Edge;

typedef struct Node
{
    vector<Edge> edges;
}Node;

vector<Node> nodes;
vector<unsigned int> dist;
vector<int> vis;

bool if_end()
{
    for(auto i : vis)
    {
        if(i==false)
            return false;
    }
    return true;
}

void Dijkstra(int s)
{
    dist[s] = 0;
    vis[s] = true;
    for(auto edge:nodes[s].edges)
    {
        dist[edge.dst] = edge.val;
    }

    while(true)
    {
        int min;
        int i,j;
        //初始化min
        for(j = 0;j<dist.size();++j)
        {
            if(vis[j]==false)
            {
                min = j;
                break;
            }
        }
        //找出不在S中的结点到s的路径最短的一个Vj
        for(j = 0;j<dist.size();++j)
        {
            if(vis[j]==false&&dist[j]<dist[min])
            {
                min = j;
            }
        }
        j = min;
        vis[j] = true;
        if(if_end())
            break;
        //遍历不在每个集合S中的Vi,以经过Vj的路径验证其dist中路径是否最短.
        for(i = 0;i<dist.size();++i)
        {
            if(vis[i]==false)
            {
                for(auto edge:nodes[j].edges)
                {
                    if(edge.dst==i)
                    {
                        if(dist[j]==-1)
                            break;
                        if(dist[j]+edge.val<dist[i])
                        {
                            dist[i] = dist[j]+edge.val;
                        }
                    }
                }
            }
        }
    }
}

unsigned int parse()
{
    ifstream infile("data");
    unsigned int src,val,dst,count,s;
    infile >> count >> s;
    nodes.resize(count);
    dist.resize(count);
    vis.resize(count);
    while(infile >> src >> val >>dst)    
    {
        nodes[src].edges.push_back(Edge({val,dst}));
    }
    for(auto& i : dist)
        i = -1;
    for(auto& i : vis)
        i = false;
    return s;
}

void output()
{
    for(auto e : dist)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    unsigned int s = parse();
    Dijkstra(s);
    output();
    return 0;
}