#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <malloc.h>
#include <stdio.h>

typedef char DataType;

typedef struct treenode{
    DataType data;
    struct treenode* leftChild;
    struct treenode* rightChild;
    int layerIndex;
}BinaryTreeNode;

void BinaryTreeInitialize(BinaryTreeNode** root, DataType x){
    *root = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    (*root)->data = x;
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;
    (*root)->layerIndex = 0;
}

void BinaryTreeInsertLeft(BinaryTreeNode* current, DataType x){
    if(current == NULL)
        return;

    BinaryTreeNode* s;
    s = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    BinaryTreeNode* t;

    t = current->leftChild;

    s->data = x;
    s->leftChild = t;
    s->rightChild = NULL;
    s->layerIndex = current->layerIndex + 1;

    current->leftChild = s;
}

void BinaryTreeInsertRight(BinaryTreeNode* current, DataType x){
    if(current == NULL)
        return;

    BinaryTreeNode* s;
    s = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    BinaryTreeNode* t;

    t = current->rightChild;

    s->data = x;
    s->rightChild = t;
    s->leftChild = NULL;
    s->layerIndex = current->layerIndex + 1;

    current->rightChild = s;
}

void BinaryTreeDestroy(BinaryTreeNode** current){
    if((*current)->leftChild != NULL)
       BinaryTreeDestroy(&((*current)->leftChild));
    if((*current)->rightChild != NULL)
        BinaryTreeDestroy(&((*current)->rightChild));
    free(*current);
}

void BinaryTreeDeleteLeft(BinaryTreeNode* current){
    if(current == NULL || current->leftChild == NULL)
        return;

    BinaryTreeDestroy(&(current->leftChild));
    current->leftChild = NULL;
}

void BinaryTreeDeleteRight(BinaryTreeNode* current){
    if(current == NULL || current->rightChild == NULL)
        return;

    BinaryTreeDestroy(&(current->rightChild));
    current->rightChild = NULL;
}

void BinaryTreeFrontTraverse(BinaryTreeNode* root){
    if(root == NULL)
        return;
    printf("%c ", root->data);
    BinaryTreeFrontTraverse(root->leftChild);
    BinaryTreeFrontTraverse(root->rightChild);
}

void BinaryTreeMiddleTraverse(BinaryTreeNode* root){
    if(root == NULL)
        return;
    BinaryTreeMiddleTraverse(root->leftChild);
    printf("%c ", root->data);
    BinaryTreeMiddleTraverse(root->rightChild);
}

void BinaryTreeHintTraverse(BinaryTreeNode* root){
    if(root == NULL)
        return;
    BinaryTreeHintTraverse(root->leftChild);
    BinaryTreeHintTraverse(root->rightChild);
    printf("%c ", root->data);
}

int BinaryTreeHeight(BinaryTreeNode* root){
    int index = root->layerIndex;
    int temp;
    if(root->leftChild == NULL && root->rightChild == NULL)
        return root->layerIndex;
    if(root->leftChild != NULL){
        temp = BinaryTreeHeight(root->leftChild);
        if(temp > index)
            index = temp;
    }
    if(root->rightChild != NULL){
        temp = BinaryTreeHeight(root->rightChild);
        if(temp > index)
            index = temp;
    }

    return index;
}


#endif // BINARYTREE_H_INCLUDED
