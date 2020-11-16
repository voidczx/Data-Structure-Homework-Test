#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define GraphDim 10
#define Infinite 9999

typedef struct{
    SeqList point;
    int lines[GraphDim][GraphDim];
    int lineSize;
} Graph;

void GraphInitialize(Graph* theGraph){
    theGraph->lineSize = 0;
    for(int i = 0; i < GraphDim; i++){
        for(int j = 0; j < GraphDim; j++){
            theGraph->lines[i][j] = Infinite;
        }
    }
    SeqListInitialize(&theGraph->point);
}

void GraphAddPoint(Graph* theGraph, SeqListDataType x){
    SeqListAppend(&theGraph->point, x);
}

void GraphAddDirectionLine(Graph* theGraph, int start, int over, int weight){
    if(theGraph->lines[start][over] >= Infinite)
        theGraph->lineSize++;
    theGraph->lines[start][over] = weight;
}

void GraphAddNoDirectionLine(Graph* theGraph, int start, int over,int weight){
    if(theGraph->lines[start][over] >= Infinite)
        theGraph->lineSize++;
    theGraph->lines[start][over] = weight;
    theGraph->lines[over][start] = weight;
}

void GraphDeleteDirectionLine(Graph* theGraph, int start, int over){
    if(theGraph->lines[start][over] >= Infinite)
        return;
    theGraph->lines[start][over] = Infinite;
    theGraph->lineSize--;
}

void GraphDeleteNoDirectionLine(Graph* theGraph, int start, int over){
    if(theGraph->lines[start][over] >= Infinite)
        return;
    theGraph->lines[start][over] = Infinite;
    theGraph->lines[over][start] = Infinite;
    theGraph->lineSize--;
}

void VisualGraphLines(Graph theGraph){
    int pointSize = theGraph.point.theSize;
    for(int i = 0; i < pointSize; i++){
        for(int j = 0; j < pointSize; j++){
            if(theGraph.lines[i][j] >= Infinite){
                printf("N ");
                continue;
            }
            printf("%d ", theGraph.lines[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


#endif // GRAPH_H_INCLUDED
