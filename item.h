//
// Created by ivan on 01.05.2021.
//

#ifndef PROGA4_A_ITEM_H
#define PROGA4_A_ITEM_H
typedef struct Infotype{
    int num1;
    int num2;
    char* string;
} Infotype;

typedef struct Item{
    Infotype *info;
    char* key;
    struct Item *parent;
    struct Item *left;
    struct Item *right;
} Item;
int insert(Item* ptr,char* key, int first,int second,char* third);
#endif //PROGA4_A_ITEM_H
