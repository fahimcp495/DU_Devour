## Floyd cycle finding algorithm for successor graph:
int hare = x0, tort = x0;
do {
    hare = succ(hare);
    hare = succ(hare);
    tort = succ(tort);
} while (hare != tort);


tort = x0;
while (tort != hare) {
    hare = succ(hare);
    tort = succ(tort);
}
// now hare and tort are the starting node of the cycle

int len = 0;
do {
  tort = succ(tort);
  len++;
} while (tort != hare);


## Number of basis simple cycle in an u-graph
E - V + number of connected components (using DSU)
Number of back-edge in dfs tree (using DFS)

## Number of eulerian subgraph in an u-graph
2^basis_cycle
