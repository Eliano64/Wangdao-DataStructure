#include "./graph.h"
#include "graph.h"
#include <deque>
#include <map>
#include <utility>

static std::deque<int> queue;

/// @brief init an adjacent list
/// @param relation int **, relation between vertex and vertex
/// @param total int, len(relation)
/// @param rowLens int *, rowLen[i] = len(relation[i]) = 1, 2
/// @param amount int, amount of vertex
/// @example input: {{1},{2,3}}, 2, {1,2}, 3
graph::graph(int **relation, int total, int *rowLens, int amount) {
    vertices = new vertex[amount];
    this->amount = amount;
    this->eNum = total;
    for (int i = 0; i < amount; ++i) {
        vertices[i].from = i;
    }
    for (int i = 0; i < total; ++i) {
        if (rowLens[i] < 2) {
            continue;
        }
        vertex &from = vertices[relation[i][0]];
        edge *e = new edge(relation[i][1]);
        e->next = from.first;
        from.first = e;
    }
}

graph::~graph() {
    for (int i = 0; i < amount; ++i) {
        for (edge *cur = vertices[i].first; cur != nullptr;) {
            edge *nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    delete[] vertices;
}

void graph::_bfs(int from, int *visited) {
    queue.push_back(from);
    visited[from] = 1;
    while (!queue.empty()) {
        int from = queue.front();
        queue.pop_front();
        for (edge *cur = vertices[from].first; cur != nullptr;
             cur = cur->next) {
            if (!visited[cur->to]) {
                queue.push_back(cur->to);
                visited[cur->to] = 1;
            }
        }
    }
}
/// @brief entrance of true bfs
/// @return amount of connected components
int graph::bfsEntrance() {
    int cnt = 0;
    int *visited = new int[amount]();
    for (int i = 0; i < amount; ++i) {
        visited[i] = 0;
    }
    for (int i = 0; i < amount; ++i) {
        if (visited[i] == 0) {
            ++cnt;
            _bfs(i, visited);
        }
    }
    delete[] visited;
    return cnt;
}

void graph::_dfs(int from, int *visited) {
    visited[from] = 1;
    for (edge *cur = vertices[from].first; cur != nullptr; cur = cur->next) {
        if (!visited[cur->to]) {
            _dfs(cur->to, visited);
        }
    }
}

int graph::dfsEntrance() {
    int cnt = 0;
    int *visited = new int[amount]();
    for (int i = 0; i < amount; ++i) {
        visited[i] = 0;
    }
    for (int i = 0; i < amount; ++i) {
        if (visited[i] == 0) {
            ++cnt;
            _dfs(i, visited);
        }
    }
    delete[] visited;
    return cnt;
}

/// @brief 拓扑排序
/// @return 点的序列
int *AOE::_topologicalSort() {
    std::deque<int> vertexStack;
    int *in = new int[amount]();
    int *ans = new int[amount]();
    for (int i = 0; i < amount; ++i) {
        for (edge *cur = vertices[i].first; cur != nullptr; cur = cur->next) {
            in[cur->to]++;
        }
    }
    for (int i = 0; i < amount; ++i) {
        if (in[i] == 0) {
            vertexStack.push_back(i);
        }
    }
    int t = 0;
    while (!vertexStack.empty()) {
        int v = vertexStack.back();
        ans[t++] = v;
        vertexStack.pop_back();
        for (edge *cur = vertices[v].first; cur != nullptr; cur = cur->next) {
            --in[cur->to];
            if (in[cur->to] == 0) {
                vertexStack.push_back(cur->to);
            }
        }
    }
    delete[] in;
    return ans;
}

void AOE::_dfs(int v, int *visited, int *ans, int &t) {
    for (edge *cur = vertices[v].first; cur != nullptr; cur = cur->next) {
        if (!visited[cur->to]) {
            _dfs(cur->to, visited, ans, t);
        }
    }
    ans[t++] = v;
    visited[v] = 1;
}

/// @brief 使用dfs的逆拓扑排序
/// @return 点的序列
int *AOE::_reverseTopologicalSort() {
    int *visited = new int[amount]();
    int *ans = new int[amount]();
    int t = 0;
    for (int i = 0; i < amount; ++i) {
        if (!visited[i]) {
            _dfs(i, visited, ans, t);
        }
    }
    delete[] visited;
    return ans;
}

/// @brief 关键路径
/// @return 二维数组 path[i][0] = 序号为i的边的from path[i][1] = 序号为j的边的to
int **AOE::criticalPath() {
    // 1. 计算事件的e和l
    // 1.1. 计算e
    int *topoList = _topologicalSort();
    int *eV = new int[amount]();
    eV[topoList[0]] = 0;
    for (int i = 1; i < amount; ++i) {
        int t = 0;
        for (int j = 0; j < i; ++j) { // 在已知e的节点中找
            int t1 = eV[topoList[j]];
            for (edge *cur = vertices[topoList[j]].first; cur != nullptr;
                 cur = cur->next) {
                if (cur->to == topoList[i]) {
                    t = std::max(t, t1 + cur->weight);
                    break;
                }
            }
        }
        eV[topoList[i]] = t;
    }
    // 1.2. 计算l
    int *rTopoList = _reverseTopologicalSort();
    int *lV = new int[amount]();
    lV[rTopoList[0]] = eV[topoList[amount - 1]];
	delete[] topoList;
    for (int i = 1; i < amount; ++i) {
        int t = 2147483647;
        for (edge *cur = vertices[rTopoList[i]].first; cur != nullptr;
             cur = cur->next) {
            t = std::min(lV[cur->to] - cur->weight, t);
        }
        lV[rTopoList[i]] = t;
    }
	delete[] rTopoList;
    // 2. 计算活动的e和l
    // 2.1. 活动的e
    // 为了方便，采用哈希表存<<from, to>, e>
    std::map<std::pair<int, int>, int> eE;
    for (int i = 0; i < amount; ++i) {
        for (edge *cur = vertices[i].first; cur != nullptr; cur = cur->next) {
            eE.emplace(std::make_pair(i, cur->to), eV[i]);
        }
    }
    // 2.2. 活动的l
    std::map<std::pair<int, int>, int> lE;
    for (int i = 0; i < amount; ++i) {
        for (edge *cur = vertices[i].first; cur != nullptr; cur = cur->next) {
            lE.emplace(std::make_pair(i, cur->to), lV[cur->to] - cur->weight);
        }
    }
    delete[] eV;
    delete[] lV;
    // 3. 计算时间余量，为0者为关键活动
    int **path = new int *[eNum];
    for (int i = 0; i < eNum; ++i) {
        path[i] = new int[2]();
    }
    int i = 0;
    for (auto [k, v] : eE) {
        if (lE[k] - v == 0) {
            path[i][0] = k.first;
            path[i][1] = k.second;
            i++;
        }
    }
    return path;
}
