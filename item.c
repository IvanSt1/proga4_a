#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "dialog.h"
#include "get.h"
#include "item.h"

int insert(Item **root, char *key, int first, int second, char *third) {
    if (*root == NULL) {
        *root = (Item *) malloc(sizeof(Item));
        if (*root == NULL) {
            return 2;
        }
            (*root)->key = key;
            (*root)->info=(Infotype*) malloc(sizeof (Infotype));
            (*root)->info->num1 = first;
            (*root)->info->num2 = second;
            (*root)->info->string = third;
            (*root)->left = NULL;
            (*root)->right = NULL;

    }
    else {
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
        x->key=key;
        x->info=(Infotype*) malloc(sizeof (Infotype));
        if (x->info == NULL) {
            return 2;
        }
        x->info->num1 = first;
        x->info->num2 = second;
        x->info->string = third;
        x->left = NULL;
        x->right = NULL;
        x->parent=par;
        if (strcmp(key,par->key)<0){
            par->left=x;
        } else{
            par->right=x;
        }
    }

    return 0;
}int show(Item** root){
    if((*root)==NULL){
        return 0;
    }
    Item* ptr=*root;
    work(&ptr);
    return 1;
}
void work(Item ** ptr){
    if (*ptr!=NULL){
        printf("key: %s | first number: %d | second number: %d | information string: %s\n",(*ptr)->key,(*ptr)->info->num1,(*ptr)->info->num2,(*ptr)->info->string);
        work(&(*ptr)->left);
        work(&(*ptr)->right);
    }
}
Item * find(Item *ptr,char* key){
    Item* res;
    if (ptr==NULL){
        return NULL;
    }
    else{
        int k= strcmp(key,ptr->key);
       if(k==0){
           res=ptr;
       }
       else{
           if(k<0){
               res=find(ptr->left, key);
           }
           else{
               res=find(ptr->right, key);
           }
       }
    }

    return res;
}
Item * min(Item *ptr){
    Item * x=ptr;
    while(x!=NULL && x->left!=NULL){
        x=x->left;
    }
    return x;
}
Item* delete(Item *root, char *key){

    if (root == NULL){
        printf("Table is empty");
        return root;
    }
    int k=strcmp(key, root->key);
    if (k < 0){
        root->left = delete(root->left, key);
    }

    else if (k > 0){
        root->right = delete(root->right, key);
    } else {
        if (root->left==NULL){
            Item *temp = root->right;
            free(root->info->string);
            free(root->info);
            free(root);
            return temp;
        }
        else if (root->right==NULL){
            Item *temp = root->left;
            free(root->info->string);
            free(root->info);
            free(root);
            return temp;
        }

        Item *temp = min(root->right);
        root->key = temp->key;
        root->info = temp->info;

        root->right = delete(root->right, temp->key);
    }
    return root;
}