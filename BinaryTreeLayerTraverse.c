#include "BinaryTree.h"
#include "BinaryTreeLayerTraverseQueue.h"
#include<math.h>

void BinaryTreeLayerTraverse(BinaryTreeNode* root){
    NTSeqQueue* BinaryTreeNodeQueue;
    BinaryTreeNodeQueue = (NTSeqQueue*)malloc(sizeof(NTSeqQueue));
    BinaryTreeNode* p;
    p = root;
    NTSeqQueueInitialize(BinaryTreeNodeQueue);
    NTSeqQueueEnter(BinaryTreeNodeQueue, *p);
    int layerIndex = 0;
    while(BinaryTreeNodeQueue->counter > 0){
        NTSeqQueueQuit(BinaryTreeNodeQueue, p);
        if(p->leftChild != NULL || p->rightChild != NULL){
            if(p->leftChild != NULL)
                NTSeqQueueEnter(BinaryTreeNodeQueue, *(p->leftChild));
            else{
                BinaryTreeNode* temp = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
                temp->data = '#';
                temp->leftChild = NULL;
                temp->rightChild = NULL;
                temp->layerIndex = p->layerIndex + 1;
                NTSeqQueueEnter(BinaryTreeNodeQueue, *temp);
            }
            if(p->rightChild != NULL)
                NTSeqQueueEnter(BinaryTreeNodeQueue, *(p->rightChild));
            else{
                BinaryTreeNode* temp = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
                temp->data = '#';
                temp->leftChild = NULL;
                temp->rightChild = NULL;
                temp->layerIndex = p->layerIndex + 1;
                NTSeqQueueEnter(BinaryTreeNodeQueue, *temp);
            }
        }
        if(p->layerIndex > layerIndex){
            printf("\n");
            layerIndex = p->layerIndex;
        }
        printf("%c", p->data);
    }
}

void main(){
    BinaryTreeNode* root;
    BinaryTreeInitialize(&root, 'A');
    BinaryTreeNode* p;
    p = root;
    printf("tree is ok\n");
    BinaryTreeInsertLeft(p, 'B');
    BinaryTreeInsertRight(p, 'C');
    p = p->leftChild;
    BinaryTreeInsertLeft(p, 'D');
    p = p->leftChild;
    BinaryTreeInsertLeft(p, 'E');
    BinaryTreeInsertRight(p, 'F');
    BinaryTreeLayerTraverse(root);
}
