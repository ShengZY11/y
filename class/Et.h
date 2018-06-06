//
// Created by xiaosi on 18-5-23.
//

#ifndef LAB2_ET_H
#define LAB2_ET_H

#define MAX_NUM 500
#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

typedef struct EtNode{
    int yminX;
    int yMax;
    float ek;
    EtNode* next;
}EtNode, *EtHead;

class Et {
private:
    EtHead etHead[MAX_NUM];
public:
    Et();
    Et(const Et& et);
    ~Et();
    Et&operator=(const Et& et);
    void insert(EtNode* node, int num); //num表示第num个桶
    void creatEt();
    void output();
    EtHead* getetHead();
};


#endif //LAB2_ET_H
