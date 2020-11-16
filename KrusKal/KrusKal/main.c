#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"
#include "Graph.h"
#include "MergingSort.h"
#include "Krustal.h"

void main()
{
    Graph myGraph;
    GraphInitialize(&myGraph);
    GraphAddPoint(&myGraph, 'A');
    GraphAddPoint(&myGraph, 'B');
    GraphAddPoint(&myGraph, 'C');
    GraphAddPoint(&myGraph, 'D');
    GraphAddPoint(&myGraph, 'E');
    GraphAddPoint(&myGraph, 'F');
    GraphAddPoint(&myGraph, 'G');
    GraphAddNoDirectionLine(&myGraph, 0, 1, 50);
    GraphAddNoDirectionLine(&myGraph, 0, 2, 60);
    GraphAddNoDirectionLine(&myGraph, 1, 3, 65);
    GraphAddNoDirectionLine(&myGraph, 1, 4, 40);
    GraphAddNoDirectionLine(&myGraph, 2, 3, 52);
    GraphAddNoDirectionLine(&myGraph, 2, 6, 45);
    GraphAddNoDirectionLine(&myGraph, 3, 4, 50);
    GraphAddNoDirectionLine(&myGraph, 3, 5, 30);
    GraphAddNoDirectionLine(&myGraph, 3, 6, 42);
    GraphAddNoDirectionLine(&myGraph, 4, 5, 70);
    VisualGraphLines(myGraph);
    KrustalWeight* result;
    result = KrustalGenerate(&myGraph);
    for(int i = 0; i < myGraph.point.theSize-1; i++){
        KrustalWeight currentWeight = *(result + i);
        printf("The Weight: %d  The First Point: %c  The Second Point: %c", currentWeight.weight, *(myGraph.point.data + currentWeight.startPoint), *(myGraph.point.data + currentWeight.overPoint));
        printf("\n");
    }
    printf("\n");
}
