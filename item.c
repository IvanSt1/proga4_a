#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "item.h"

int insert(Item **root, char *key, int first, int second, char *third) {
    if (*root == NULL) {
        *root = (Item *) malloc(sizeof(Item));
        if (*root == NULL) {
            return 2;
        }
        (*root)->key = key;
        (*root)->info = (Infotype *) malloc(sizeof(Infotype));
        (*root)->info->num1 = first;
        (*root)->info->num2 = second;
        (*root)->info->string = third;
        (*root)->left = NULL;
        (*root)->right = NULL;

    } else {
        Item *ptr = *root;
        Item *par = NULL;
        Item *x = (Item *) malloc(sizeof(Item));
        if (x == NULL) {
            return 2;
        }
        while (ptr != NULL) {
            par = ptr;
            int k = strcmp(key, ptr->key);
            if (k == 0) {
                return 1;
            } else {
                if (k < 0) {
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            }
        }
        x->key = key;
        x->info = (Infotype *) malloc(sizeof(Infotype));
        if (x->info == NULL) {
            return 2;
        }
        x->info->num1 = first;
        x->info->num2 = second;
        x->info->string = third;
        x->left = NULL;
        x->right = NULL;
        x->parent = par;
        if (strcmp(key, par->key) < 0) {
            par->left = x;
        } else {
            par->right = x;
        }
    }

    return 0;
}

int show(Item **root) {
    if ((*root) == NULL) {
        return 0;
    }
    Item *ptr = *root;
    work(ptr);
    return 1;
}

void work(Item *ptr) {
    if (ptr != NULL) {
        if (ptr->parent!=NULL) {
            printf("key: %s | first number: %d | second number: %d | information string: %s | parent key: %s \n",
                   ptr->key,
                   ptr->info->num1, ptr->info->num2, ptr->info->string, ptr->parent->key);
        }
        else{
            printf("key: %s | first number: %d | second number: %d | information string: %s \n",
                   ptr->key,
                   ptr->info->num1, ptr->info->num2, ptr->info->string);
        }
        work(ptr->left);
        work(ptr->right);
    }
}

Item *find(Item *ptr, char *key) {
    Item *res = NULL;
    while (ptr != NULL && res == NULL) {
        int k = strcmp(key, ptr->key);
        if (k == 0) {
            res = ptr;
        } else {
            if (k < 0) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }
    }
    return res;
}

Item *min(Item *ptr) {
    Item *x = ptr;
    while (x != NULL && x->left != NULL) {
        x = x->left;
    }
    return x;
}

int delete(Item **root, char *key ,int flag) {

    if (*root == NULL) {
        return 4;
    }
    Item* x= find(*root,key);
    if (x==NULL){
        return 3;
    }
    else{
        if (x==*root){ // удаляемый элемент корень
            if((*root)->left==NULL){
                if ((*root)->right==NULL){
                    *root=NULL;
                }
                else{
                    (*root)->info=(*root)->right->info;
                    if ((*root)->right->left!=NULL){
                        (*root)->right->left->parent=(*root);
                    }
                    if ((*root)->right->right!=NULL){
                        (*root)->right->right->parent=(*root);
                    }
                    char* s =x->right->key;
                    delete(root,s,1);
                    (*root)->key=s;

                }
            }
            else {
                if ((*root)->right==NULL){
                    (*root)->info=x->left->info;
                    if ((*root)->left->left!=NULL){
                        (*root)->left->left->parent=(*root);
                    }
                    if ((*root)->left->right!=NULL){
                        (*root)->left->right->parent=(*root);
                    }
                    char* s =x->left->key;
                    delete(root,s,1);
                    (*root)->key=s;
                }
                else{
                    if ((*root)->right->left!=NULL){
                        (*root)->right->left->parent=(*root);
                    }
                    if ((*root)->right->right!=NULL){
                        (*root)->right->right->parent=(*root);
                    }
                    if ((*root)->left->left!=NULL){
                        (*root)->left->left->parent=(*root);
                    }
                    if ((*root)->left->right!=NULL){
                        (*root)->left->right->parent=(*root);
                    }
                    Item * y=min(x->right);
                    (*root)->info=y->info;
                    char* s=y->key;
                    delete(root,s,1);
                    (*root)->key=s;
                }
            }

        }
        else{
            if (x->left==NULL){ // нет левого поддерева
                if (x->parent->left==x) {
                    x->parent->left=x->right;
                    if (x->right!=NULL) {
                        x->right->parent = x->parent;
                    }
                }
                else{
                    x->parent->right=x->right;
                    if (x->right!=NULL) {
                        x->right->parent = x->parent;
                    }
                }
                if (flag==0){
                    free(x->info->string);
                    free(x->info);
                    free(x->key);
                }
            }
            else
            {
                if (x->right==NULL){ // нет правого поддерерва
                    if (x->parent->left==x) {
                        x->parent->left=x->left;
                        if(x->left!=NULL) {
                            x->left->parent = x->parent;
                        }
                    }
                    else{
                        x->parent->right=x->left;
                        if(x->left!=NULL) {
                            x->left->parent = x->parent;
                        }

                    }
                    if (flag==0){
                        free(x->info->string);
                        free(x->info);
                        free(x->key);
                    }

                }
                else{  // есть левое и правое
                    Item * y=min(x->right);
                    x->info=y->info;
                    char* s=y->key;
                    delete(root,s,1);
                    x->key=s;
                }
            }
        }
    }
    return 0;
}
void delete_all(Item *ptr){
    if (ptr != NULL) {
        delete_all(ptr->left);
        delete_all(ptr->right);
        free(ptr->info->string);
        free(ptr->info);
        free(ptr->key);
        free(ptr);
    }
}