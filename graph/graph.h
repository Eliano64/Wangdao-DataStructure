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

  public:
    vertex *vertices;
    int amount;
    graph(int **relation, int total, int *rowLens, int amount);
    ~graph();
    int bfsEntrance();
};

#endif
