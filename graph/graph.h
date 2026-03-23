#ifndef graph_H
#define graph_H

class edge {
  public:
    int to;
    edge *next;
    int weight;
    edge(int t, int w = 1) : to(t), next(nullptr), weight(w) {};
};

class vertex {
  public:
    int from;
    edge *first;
    vertex(int t = 0) : from(t), first(nullptr) {};
};

class graph {
    void _bfs(int, int *);
    void _dfs(int, int *);

  public:
    vertex *vertices;
    int amount;
    int eNum;
    graph(int **relation, int total, int *rowLens, int amount);
    ~graph();
    int bfsEntrance();
    int dfsEntrance();
};

class  AOE : public graph {
    void _dfs(int, int *, int *, int&);
    int *_topologicalSort();
    int *_reverseTopologicalSort();

  public:
    AOE(int **relation, int total, int *rowLens, int amount)
        : graph(relation, total, rowLens, amount) {};
    int **criticalPath();
};

#endif
