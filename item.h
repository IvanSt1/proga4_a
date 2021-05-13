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
int insert(Item** ptr,char* key, int first,int second,char* third);
int show(Item** root);
void work(Item * ptr);
Item * find(Item *ptr,char* key);
int delete(Item **root, char*key,int flag);
Item * min(Item *root);
void delete_all(Item *ptr);
Item *find_nearest(Item *ptr, char *key);
void show_tree(Item* ptr, int i);
Item *max(Item *ptr);
Item *find_previous(Item* ptr);
Item *find_following(Item* ptr);
int summa(char *s);
int work_with_file(Item** root,char *name);
#endif //PROGA4_A_ITEM_H
