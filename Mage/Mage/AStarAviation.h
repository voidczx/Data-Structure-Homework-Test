#ifndef ASTARAVIATION_H_INCLUDED
#define ASTARAVIATION_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIDE_LENGTH 7

typedef struct node01{
    struct node01* parent;
    int costValue;
    int distanceValue;
    int roadFlag;
    int openRoadFlag;
    int positionX;
    int positionY;
} roadNode;

void CreatRoad(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], int x, int y, roadNode* terminal){
    roadNode* road;
    road = theMap[x][y];
    road->positionX = x;
    road->positionY = y;
    int distanceValue = (abs(y - terminal->positionY) + abs(x - terminal->positionX)) * 10;
    road->distanceValue = distanceValue;
    road->parent = NULL;
    road->roadFlag = 1;
    road->openRoadFlag = 1;
}

void CreatWall(roadNode** wall, int x, int y){
    *wall = (roadNode*)malloc(sizeof(roadNode));
    (*wall)->positionX = x;
    (*wall)->positionX = y;
    (*wall)->parent = NULL;
    (*wall)->roadFlag = 0;
}

void openUpInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionX <= 0){
        return;
    }
    roadNode *up = *(*(theMap + current->positionX - 1) + current->positionY);
    if(up->roadFlag == 0 || up->openRoadFlag == 0)
        return;
    up->costValue = current->costValue + 10;
    up->parent = current;
}

void openLeftInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionY <= 0){
        return;
    }
    roadNode *left = *(*(theMap + current->positionX) + current->positionY - 1);
    if(left->roadFlag == 0 || left->openRoadFlag == 0)
        return;
    left->costValue = current->costValue + 10;
    left->parent = current;
}

void openDownInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionX >= MAX_SIDE_LENGTH - 1){
        return;
    }
    roadNode *down = *(*(theMap + current->positionX + 1) + current->positionY);
    if(down->openRoadFlag == 0 || down->roadFlag == 0)
        return;
    down->costValue = current->costValue + 10;
    down->parent = current;
}

void openRightInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionY >= MAX_SIDE_LENGTH - 1){
        return;
    }
    roadNode *right = *(*(theMap + current->positionX) + current->positionY + 1);
    if(right->openRoadFlag == 0 || right->roadFlag == 0)
        return;
    right->costValue = current->costValue + 10;
    right->parent = current;
}

void openNeighberInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    openUpInitialize(theMap, current);
    openDownInitialize(theMap, current);
    openLeftInitialize(theMap, current);
    openRightInitialize(theMap, current);
}

roadNode* roadStartInitialize(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], int x, int y){
    roadNode* start;
    start = *(*(theMap + x) + y);
    start->roadFlag = 1;
    start->openRoadFlag = 1;
    start->costValue = 0;
    start->positionX = x;
    start->positionY = y;
    start->parent = NULL;
    return start;
}

roadNode* upSelect(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionX <= 0){
        return NULL;
    }
    roadNode *up = *(*(theMap + current->positionX - 1) + current->positionY);
    if(up->roadFlag == 0 || up->openRoadFlag == 0)
        return NULL;
    return up;
}

roadNode* leftSelect(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionY <= 0){
        return NULL;
    }
    roadNode *left = *(*(theMap + current->positionX) + current->positionY - 1);
    if(left->roadFlag == 0 || left->openRoadFlag == 0)
        return NULL;
    return left;
}

roadNode* downSelect(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionX >= MAX_SIDE_LENGTH - 1){
        return NULL;
    }
    roadNode *down = *(*(theMap + current->positionX + 1) + current->positionY);
    if(down->openRoadFlag == 0 || down->roadFlag == 0)
        return NULL;
    return down;
}

roadNode* rightSelect(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    if(current->positionY >= MAX_SIDE_LENGTH - 1){
        return NULL;
    }
    roadNode *right = *(*(theMap + current->positionX) + current->positionY + 1);
    if(right->openRoadFlag == 0 || right->roadFlag == 0)
        return NULL;
    return right;
}

roadNode* roadSelect(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* current){
    current->openRoadFlag = 0;
    openNeighberInitialize(theMap, current);
    int index;
    int temp = 5000;
    roadNode* up = upSelect(theMap, current);
    roadNode* left = leftSelect(theMap, current);
    roadNode* down = downSelect(theMap, current);
    roadNode* right = rightSelect(theMap, current);
    if(up != NULL){
        if(up->costValue + up->distanceValue <= temp){
            temp = up->costValue + up->distanceValue;
            index = 1;
        }
    }
    if(left != NULL){
        if(left->costValue + left->distanceValue <= temp){
            temp = left->costValue + left->distanceValue;
            index = 2;
        }
    }
    if(down != NULL){
        if(down->costValue + down->distanceValue <= temp){
            temp = down->costValue + down->distanceValue;
            index = 3;
        }
    }
    if(right != NULL){
        if(right->costValue + right->distanceValue <= temp){
            temp = right->costValue + right->distanceValue;
            index = 4;
        }
    }
    if(up == NULL && left == NULL && down == NULL && right == NULL){
        return current->parent;
    }

    switch(index){
    case 1:
        return up;
    case 2:
        return left;
    case 3:
        return down;
    case 4:
        return right;
    }
}

void VisualMap(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], roadNode* terminate, roadNode* start){
    for(int i = 0; i < MAX_SIDE_LENGTH; i++){
        for(int j = 0; j < MAX_SIDE_LENGTH; j++){
            if(i == terminate->positionX && j == terminate->positionY){
                printf("%c", '%');
            }
            else if(i == start->positionX && j == start->positionY){
                printf("%c", '!');
            }
            else if((*(*(theMap + i) + j))->roadFlag == 1){
                printf("%c", 'H');
            }
            else{
                printf("%c", '-');
            }
        }
        printf("\n");
    }
}

roadNode* GenerateTerminal(roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH], int x, int y){
    roadNode* terminal;
    terminal = theMap[x][y];
    terminal->distanceValue = 0;
    terminal->parent = NULL;
    terminal->openRoadFlag = 1;
    terminal->roadFlag = 1;
    terminal->positionX = x;
    terminal->positionY = y;
}


#endif // ASTARAVIATION_H_INCLUDED
