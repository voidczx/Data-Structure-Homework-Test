#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "AStarAviation.h"
#include "RSLNode.h"

int String2int(const char* theString){
    int index = strlen(theString);
    int result = 0;
    for(int i = 0; i < index; i++){
        int tenPower = index - i - 1;
        int number = *(theString + i) - '0';
        result += pow(10, tenPower) * number;
    }
    return result;
}

int main()
{
    roadNode* theMap[MAX_SIDE_LENGTH][MAX_SIDE_LENGTH];
    roadNode* terminal;
    roadNode* start;
    RSLNode* roadListX;
    RSLNode* roadListY;
    RSLNodeInitialize(&roadListX);
    RSLNodeInitialize(&roadListY);

    char filePath[] = "C:\\Users\\94342\\Desktop\\DataStructure\\Mage\\Mage\\Mage.txt";
    FILE* fp = NULL;
    fp = fopen(filePath, "r");
    if(!fp){
        printf("Read file error!");
    }


    for(int i = 0; i < MAX_SIDE_LENGTH; i++){
        for(int j = 0; j < MAX_SIDE_LENGTH; j++){
            roadNode* origin;
            CreatWall(&origin, i, j);
            theMap[i][j] = origin;
        }
    }

    int roadIndex = 0;
    rewind(fp);
    while(1){
        if(feof(fp))
            break;
        char temp01[10];
        char temp02[10];
        fscanf(fp, "%s%s", temp01, temp02);
        if((*(temp01)) == '#'){
            if(strcmp(temp02, "terminal") == 0){
                fscanf(fp, "%s%s", temp01, temp02);
                terminal = GenerateTerminal(theMap, String2int(temp01), String2int(temp02));
            }
            else if(strcmp(temp02, "start") == 0){
                fscanf(fp, "%s%s", temp01, temp02);
                start = roadStartInitialize(theMap, String2int(temp01), String2int(temp02));
            }
        }
        else{
            RSLNodeInsert(roadListX, String2int(temp01), roadIndex);
            RSLNodeInsert(roadListY, String2int(temp02), roadIndex);
            roadIndex++;
        }
    }

    fclose(fp);

    RSLNode* roadPosX;
    RSLNode* roadPosY;
    roadPosX = roadListX->next;
    roadPosY = roadListY->next;
    while(roadPosX != roadListX && roadPosY != roadListY){
        CreatRoad(theMap, roadPosX->data, roadPosY->data, terminal);
        roadPosX = roadPosX->next;
        roadPosY = roadPosY->next;
    }

    // Find the road
    roadNode* road;
    road = start;
    while(road->positionX != terminal->positionX || road->positionY != terminal->positionY){
        road = roadSelect(theMap, road);
    }

    // get the road point
    road = terminal;
    while(road != NULL){
        printf("(%d, %d)\n", road->positionX, road->positionY);
        road = road->parent;
    }

    VisualMap(theMap, terminal, start);

}
