//
// Created by xiaosi on 18-5-24.
//

#include "Aet.h"
#include <iostream>

Aet::Aet(Et et) {
    AetNode* p = new AetNode;
    p->next = nullptr;
    aet = p;
    this->et = et;
    num = 0;
}
void Aet::insert(AetNode* aetNode) {
    insert2(aet, aetNode);
}
void Aet::update() {
    num++;
    //删除超过上限的边
    {
        AetNode *p = aet;
        while(p->next != nullptr){
            if(p->next->yMax < num){
                AetNode *q = p->next;
                p->next = q->next;
                delete q;
            }
            else{
                p = p->next;
            }
        }
    }
    //更新链表的值
    {
        AetNode *p = aet->next;
        while (p != nullptr){
            p->x = p->x + p->ek;
            p = p->next;
        }
    }

    //把et表中的信息读入
    if(et.getetHead()[num] != nullptr){
        EtNode* etp = new EtNode;
        etp = et.getetHead()[num]->next;
        while (etp != nullptr){
            AetNode* aetp = new AetNode;
            aetp->x = etp->yminX;
            aetp->yMax = etp->yMax;
            aetp->ek = etp->ek;
            aetp->next = nullptr;
            insert(aetp);
            etp = etp->next;
        }
    }

    //排序:采用插入排序
    {
        //初始化一个新的链表
        AetHead newAet = new AetNode;
        newAet->next = nullptr;

        //把旧链表中的节点插入新链表中
        AetNode *p = aet->next;
        while (p != nullptr){
            AetNode *r = p->next;
            p->next = nullptr;
            insert2(newAet, p);
            p = r;
        }
        delete aet;
        aet = newAet;
    }
}

void Aet::output() {
    std::cout<<"y="<<num;
    AetNode *p = aet->next;
    while (p != nullptr){
        std::cout<<"->"<<p->x<<" "<<p->yMax<<" "<<p->ek<<" ";
        p = p->next;
    }
    std::cout<<"->NULL"<<std::endl;
}

bool Aet::isEmpty() {
    if(aet->next == nullptr)
        return true;
    return false;
}

void insert2 (AetHead aet, AetNode* aetNode) {
    if(aet->next == nullptr){  //如果为空直接插入
        aetNode->next = nullptr;
        aet->next = aetNode;
    return;
    }
    AetNode *p = aet;
    while(p->next != nullptr && aetNode->x > p->next->x) //确保x有序
        p = p->next;
    while(p->next != nullptr && p->next->x == aetNode->x && aetNode->ek > p->next->ek)//确保k有序
        p = p->next;
    aetNode->next = p->next;
    p->next = aetNode;
}
AetHead Aet::getAet() {
    return aet;
}