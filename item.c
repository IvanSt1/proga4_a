#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "dialog.h"
#include "get.h"
#include "item.h"

int insert(Item *root, char *key, int first, int second, char *third) {
    if (root == NULL) {
        root = (Item *) malloc(sizeof(Item));
        if (root == NULL) {
            return 2;
        } else {
            root->key = key;
            root->info=(Infotype*) malloc(sizeof (Infotype));
            root->info->num1 = first;
            root->info->num2 = second;
            root->info->string = third;
            root->left = NULL;
            root->right = NULL;
        }
    }
    else {
        Item *ptr = root;
        Item *par = NULL;
        Item *x = (Item *) malloc(sizeof(Item));
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
}