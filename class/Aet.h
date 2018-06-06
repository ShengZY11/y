//
// Created by xiaosi on 18-5-24.
//

#ifndef LAB2_AET_H
#define LAB2_AET_H

#include <cmath>
#include "Et.h"

typedef struct AetNode{
    float x;
    int yMax;
    float ek;
    AetNode* next;
}AetNode, *AetHead;

void insert2(AetHead aet, AetNode* aetNode);

class Aet {
private:
    AetHead aet;
    Et et;
    int num;
public:
    Aet(Et et);
    void insert(AetNode* aetNode);
    void update();
    void output();
    bool isEmpty();
    AetHead getAet();
    int getnum(){ return  num;};
};


#endif //LAB2_AET_H
