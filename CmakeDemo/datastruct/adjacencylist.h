//
// Created by peter on 2020/1/21.
//

#ifndef CMAKEDEMO_ADJACENCYLIST_H
#define CMAKEDEMO_ADJACENCYLIST_H

#define MAX 100
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class EData
{
public:
    char start;
    char end;
    int weight;

    EData() {}
    EData(char s, char e, int w) : start(s), end(e), weight(w) {}
};

class ListUDG
{
private:
    class ENode
    {
        int ivex;
        int weight;
        ENode* next;
        friend class ListUDG;
    };

    class VNode
    {
        char data;
        ENode* first = nullptr;
        VNode() {}
        friend class ListUDG;
    };

    int vex_num;
    int edge_num;
    VNode m_vexs[MAX];
public:
    ListUDG() {}
    ListUDG(char vexs[], int vlen, EData* edges[], int elen);
    ~ListUDG() {}
    void dfs();
    void dfs(int i, vector<bool>&);
    void bfs();
    void print();
    void prim();
    void kruskal();
    void dijkstra(int vs);
    void floyd(int vs);
    int get_vex_pos(char);
    int get_weight(int, int);
    void link_last(ENode* list, ENode* node);
};

void ListUDG::floyd(int vs)
{
    vector<vector<int>> D(vex_num, vector<int>(vex_num, 0));
    vector<vector<int>> P(vex_num, vector<int>(vex_num, 0));
    for (int i = 0; i < vex_num; ++i)
    {
        for (int j = 0; j < vex_num; ++j)
        {
            D[i][j] = get_weight(i, j);
            P[i][j] = j;
        }
    }

    for (int k = 0; k < vex_num; ++k)
    {
        for (int i = 0; i < vex_num; ++i)
        {
            for (int j = 0; j < vex_num; ++j)
            {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }

    cout << "floyd(" << m_vexs[vs].data << ")" << endl;
    for (int i = 0; i < vex_num; ++i)
    {
        cout << "  shortest(" << m_vexs[vs].data << ", " << m_vexs[i].data << ")=" << D[vs][i] << endl;

        string path;
        path += m_vexs[vs].data;
        vector<int> tmp;
        int p = P[vs][i];
        tmp.push_back(p);
        while (tmp.back() != P[vs][p])
        {
            p = P[vs][p];
            tmp.push_back(p);
        }
        for (int i = tmp.size() - 1; i >= 0; --i)
        {
            path += m_vexs[tmp[i]].data;
        }
        path += m_vexs[i].data;
        cout << path << endl;
    }


    cout << "test" << endl;
}

void ListUDG::dijkstra(int vs)
{
    vector<int> dist(vex_num, 0);
    vector<bool> flag(vex_num, false);

    flag[vs] = true;

    for (int i = 0; i < vex_num; ++i)
    {
        dist[i] = get_weight(vs, i);
    }

    for (int i = 1; i < vex_num; ++i)
    {
        int min = INF;
        int k;
        for (int j = 0; j < vex_num; ++j)
        {
            if (!flag[j] && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }

        flag[k] = true;

        for (int j =0; j < vex_num; ++j)
        {
            int tmp = get_weight(k, j);
            tmp = (tmp == INF) ? INF : (tmp + min);
            if (!flag[j] && tmp < dist[j])
            {
                dist[j] = tmp;
            }
        }
    }

    cout << "dijkstra(" << m_vexs[vs].data << ")" << endl;
    for (int i = 0; i < vex_num; ++i)
    {
        cout << "  shortest(" << m_vexs[vs].data << ", " << m_vexs[i].data << ")=" << dist[i] << endl;
    }
}

int ListUDG::get_weight(int start, int end)
{
    if (start == end)
    {
        return 0;
    }
    ENode* p = m_vexs[start].first;
    while (p != nullptr)
    {
        if (end == p->ivex)
        {
            return p->weight;
        }
        p = p->next;
    }

    return INF;
}

void ListUDG::dfs(int i, vector<bool>& visited)
{
    cout << m_vexs[i].data << '\t';
    ENode* p = m_vexs[i].first;
    visited[i] = true;
    while (p != nullptr)
    {
        if (!visited[p->ivex])
        {
            dfs(p->ivex, visited);
        }
        p = p->next;
    }
}

void ListUDG::dfs()
{
    vector<bool> visited(vex_num, false);
    for (int i = 0; i < vex_num; ++i)
    {
        if (!visited[i])
        {
            dfs(i, visited);
        }
    }
}

void ListUDG::bfs()
{
    queue<int> Q;
    vector<bool> visited(vex_num, false);

    for (int i = 0; i < vex_num; ++i)
    {
        if (!visited[i])
        {
            visited[i] = true;
            cout << m_vexs[i].data << '\t';
            Q.push(i);
        }

        while (!Q.empty())
        {
            int j = Q.front();
            Q.pop();
            ENode* p = m_vexs[j].first;
            while (p != nullptr)
            {
                int k = p->ivex;
                if (!visited[k])
                {
                    visited[k] = true;
                    cout << m_vexs[k].data << '\t';
                    Q.push(k);
                }
                p = p->next;
            }
        }
    }
    cout << endl;
}

void ListUDG::link_last(ENode* list, ENode* node)
{
    ENode* p = list;
    while (p->next)
    {
        p = p->next;
    }
    p->next = node;
}
int ListUDG::get_vex_pos(char ch)
{
    for (int i = 0; i < vex_num; ++i)
    {
        if (m_vexs[i].data == ch)
        {
            return i;
        }
    }
    return -1;
}

ListUDG::ListUDG(char vexs[], int vlen, EData* edges[], int elen)
{
    vex_num = vlen;
    edge_num = elen;
    for (int i = 0; i < vlen; ++i)
    {
        m_vexs[i].data = vexs[i];
        m_vexs[i].first = nullptr;
    }

    char s1, s2;
    int p1, p2;
    int weight;
    ENode* enode;
    for (int i = 0; i < elen; ++i)
    {
        s1 = edges[i]->start;
        s2 = edges[i]->end;
        weight = edges[i]->weight;
        p1 = get_vex_pos(s1);
        p2 = get_vex_pos(s2);
        enode = new ENode();
        enode->ivex = p2;
        enode->weight = weight;
        if (m_vexs[p1].first == nullptr)
        {
            m_vexs[p1].first = enode;
        }
        else
        {
            link_last(m_vexs[p1].first, enode);
        }

        enode = new ENode();
        enode->ivex = p1;
        enode->weight = weight;
        if (m_vexs[p2].first == nullptr)
        {
            m_vexs[p2].first = enode;
        }
        else
        {
            link_last(m_vexs[p2].first, enode);
        }

    }

}

void test()
{
    int prev[MAX] = { 0 };
    int dist[MAX] = { 0 };
    // 顶点
    char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
    // 边
    EData* edges[] = {
        // 起点 终点 权
 new EData('A', 'B', 12),
 new EData('A', 'F', 16),
 new EData('A', 'G', 14),
 new EData('B', 'C', 10),
 new EData('B', 'F',  7),
 new EData('C', 'D',  3),
 new EData('C', 'E',  5),
 new EData('C', 'F',  6),
 new EData('D', 'E',  4),
 new EData('E', 'F',  2),
 new EData('E', 'G',  8),
 new EData('F', 'G',  9),
    };
    int vlen = sizeof(vexs) / sizeof(vexs[0]);
    int elen = sizeof(edges) / sizeof(edges[0]);
    ListUDG* pG;

    // 自定义"图"(输入矩阵队列)
    //pG = new ListUDG();
    // 采用已有的"图"
    pG = new ListUDG(vexs, vlen, edges, elen);
    pG->bfs();
    pG->dfs();
    pG->dijkstra(3);
    pG->floyd(3);
}

#endif