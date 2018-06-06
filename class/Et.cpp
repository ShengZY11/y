//
// Created by xiaosi on 18-5-23.
//

#include <iostream>
#include "Et.h"

Et::Et() {
    for(int i = 0; i<MAX_NUM; i++)
        etHead[i] = nullptr;
}


Et::Et(const Et &et) {
    for(int i = 0; i< MAX_NUM; i++){
        this->etHead[i] = nullptr;
    }
    for(int i = 0; i<MAX_NUM; i++){
        if(et.etHead[i] == nullptr)
            continue;
        this->etHead[i] = new EtNode;
        this->etHead[i]->next = nullptr;
        EtNode *p, *r = new EtNode;
        p = et.etHead[i]->next; //p为被复制链表的工作指针
        r = this->etHead[i]; //r为复制链表工作指针
        while (p != nullptr){
            EtNode *q = new EtNode;
            q->yMax = p->yMax;
            q->yminX = p->yminX;
            q->ek = p->ek;
            q->next = nullptr;
            r->next = q;
            r = r->next;
            p = p->next;
        }
    }
}
Et::~Et() {
    for(int i = 0; i<MAX_NUM; i++){
        if(etHead[i] == nullptr)
            continue;
        EtNode *p = etHead[i];
        EtNode *r = nullptr;
        while(p->next != nullptr){
            r = p->next;
            delete p;
            p = r;
        }
    }

}
Et& Et::operator=(const Et &et) {
    for(int i = 0; i< MAX_NUM; i++){
        this->etHead[i] = nullptr;
    }
    for(int i = 0; i<MAX_NUM; i++){
        if(et.etHead[i] == nullptr)
            continue;
        this->etHead[i] = new EtNode;
        this->etHead[i]->next = nullptr;
        EtNode *p, *r = new EtNode;
        p = et.etHead[i]->next; //p为被复制链表的工作指针
        r = this->etHead[i]; //r为复制链表工作指针
        while (p != nullptr){
            EtNode *q = new EtNode;
            q->yMax = p->yMax;
            q->yminX = p->yminX;
            q->ek = p->ek;
            q->next = nullptr;
            r->next = q;
            r = r->next;
            p = p->next;
        }
    }
    return *this;
}
void Et::insert(EtNode* node, int num) {
    EtNode* head = etHead[num];
    if(head->next == nullptr){  //如果桶为空直接插入
        node->next = nullptr;
        head->next = node;
        return;
    }
    EtNode* p = head;
    while(p->next != nullptr && node->yminX > p->next->yminX) //确保x有序
        p = p->next;
    while(p->next != nullptr && p->next->yminX == node->yminX && node->ek > p->next->ek)//确保k有序
        p = p->next;
    node->next = p->next;
    p->next = node;
}
void Et::creatEt() {
    int x, y;
    int firstx, firsty, secondx, secondy; //存储第一个点和第二个点的信息
    int fx, fy, ex = 0, ey = 0, eex, eey; //存储操作点和它之前两个点的信息
    EtNode* lastEdge = nullptr; //存储上一个边的信息
    EtNode* firstEdge = nullptr; //存储第一个边的信息
    bool firstFlag = 1;
    std::cin>>x>>y;
    //先把第一个点处理好
    if(x != 9999 && y != 9999){
        firstx = x;  //这里记录第一个点最后链接用
        firsty = y;
        fx = x;
        fy = y;
        std::cin>>x>>y;
        secondx = x;
        secondy = y;
    }else{
        return;
    }

    //循环链接制作边表
    while(x != 9999 && y != 9999){
        //更新fx fy ex ey eex eey
        eex = ex;
        eey = ey;
        ex = fx;
        ey = fy;
        fx = x;
        fy = y;
        int miny;
        int yminX;
        int yMax;
        float ek;
        if(fy < ey){
            miny = fy;
            yminX = fx;
            yMax = ey;
        }else{
            miny = ey;
            yminX = ex;
            yMax = fy;
        }
        if(ey - fy != 0){
            ek = (float(ex) - fx)/(ey - fy);
            if(etHead[miny] == nullptr){
                etHead[miny] = new EtNode;
                etHead[miny]->next = nullptr;
            }
            auto* node = new EtNode;
            node->yminX = yminX;
            node->yMax = yMax;
            node->ek = ek;
            if(firstFlag){
                firstEdge = node;
                firstFlag = 0;
            }
            // 如果 两边一上一下
            if(lastEdge != nullptr && (eey - ey)*(fy - ey) <= 0 ){
                if(eey - ey < 0)    //原始边在下
                    lastEdge->yMax--;
                else    //新增边在下
                    node->yMax--;
            }
            insert(node, miny);
            lastEdge = node;
        }

        std::cin>>x>>y;
    }

    //最后一个点和第一个点链接
    eex = ex;
    eey = ey;
    ex = fx;
    ey = fy;
    fx = firstx;
    fy = firsty;
    int miny;
    int yminX;
    int yMax;
    float ek;
    if(fy < ey){
        miny = fy;
        yminX = fx;
        yMax = ey;
    }else{
        miny = ey;
        yminX = ex;
        yMax = fy;
    }
    if(etHead == nullptr){
        etHead[miny] = new EtNode;
        etHead[miny]->next = nullptr;
    }
    auto* node = new EtNode;
    if(ey - fy != 0){
        ek = (float(ex) - fx)/(ey - fy);
        node->yminX = yminX;
        node->yMax = yMax;
        node->ek = ek;
        if(lastEdge != nullptr && (eey - ey)*(fy - ey) <= 0 ){
            if(eey - ey < 0)    //原始边在下
                lastEdge->yMax--;
            else    //
                node->yMax--;
        }
        insert(node, miny);
        lastEdge = node;

    }

    node = firstEdge;

    //检查最后一个边和第一个边是否为一上一下

    eey = ey;
    ey = fy;
    fy = secondy;
    if(lastEdge != nullptr && (eey - ey)*(fy - ey) <= 0 ){
        if(eey - ey < 0)    //原始边在下
            lastEdge->yMax--;
        else    //
            node->yMax--;
    }
}
void Et::output() {
    for(int i = 0; i<MAX_NUM; i++){
        if(etHead[i] == nullptr)
            continue;
        EtNode *p = etHead[i]->next;
        std::cout<<"y["<<i<<"]->";
        while(p != nullptr){
            std::cout<<p->yminX<<" "<<p->yMax<<" "<<p->ek<<"->";
            p = p->next;
        }
        std::cout<<std::endl;
    }
}

EtHead* Et::getetHead() {
    return etHead;
}