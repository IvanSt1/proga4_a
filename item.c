#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
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
    show_tree(ptr, 0);
    return 1;
}

void work(Item *ptr) {
    if (ptr != NULL) {
        if (ptr->parent != NULL) {
            printf("key: %s | first number: %d | second number: %d | information string: %s | parent key: %s \n",
                   ptr->key,
                   ptr->info->num1, ptr->info->num2, ptr->info->string, ptr->parent->key);
        } else {
            printf("key: %s | first number: %d | second number: %d | information string: %s \n",
                   ptr->key,
                   ptr->info->num1, ptr->info->num2, ptr->info->string);
        }
        work(ptr->left);
        work(ptr->right);
    }
}

void show_tree(Item *ptr, int i) {
    if (ptr == NULL) {
        return;
    } else {
        show_tree(ptr->left, i + 1);
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        printf("%s\n", ptr->key);
        show_tree(ptr->right, i + 1);
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

int summa(char *s) {
    int sum = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        sum += (int) s[i];
    }
    return sum;

}

Item *find_following(Item *ptr) {
    Item *res;
    Item *par;
    if (ptr->right != NULL) {
        res = min(ptr->right);
    } else {
        par = ptr->parent;
        while ((par != NULL) && (par->right == ptr)) {
            ptr = par;
            par = ptr->parent;
        }
        res = par;
    }
    return res;
}

Item *find_previous(Item *ptr) {
    Item *res;
    Item *par;
    if (ptr->left != NULL) {
        res = max(ptr->left);
    } else {
        par = ptr->parent;
        while ((par != NULL) && (par->left == ptr)) {
            ptr = par;
            par = ptr->parent;
        }
        res = par;
    }
    return res;
}

Item *find_nearest(Item *root, char *key) {
    Item *res = NULL;
    Item *ptr;
    Item *par;
    Item *following;
    Item *previous;
    int k;
    if (root == NULL) {
        res = NULL;
    } else {
        ptr = root;
        while (ptr != NULL) {
            par = ptr;
            k = strcmp(key, ptr->key);
            if (k == 0) {
                break;
            } else {
                if (k < 0) {
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            }
        }
        if (ptr != NULL) {
            following = find_following(ptr);
            previous = find_previous(ptr);
            if (following == NULL) {
                if (previous == NULL) {
                    res = NULL;
                } else {
                    res = following;
                }
            } else {
                if (previous == NULL) {
                    res = following;
                } else {
                    int sum_key = summa(key);
                    int sum_fol=summa(following->key);
                    int sum_pre= summa(previous->key);
                    if(abs(sum_key-sum_fol)<abs(sum_key-sum_pre)){
                        res=following;
                    }
                    else{
                        res=previous;
                    }
                }
            }
        } else {
            following = find_following(par);
            previous = find_previous(par);
            if (following == NULL) {
                if (previous == NULL) {
                    res = NULL;
                } else {
                    res = following;
                }
            } else {
                if (previous == NULL) {
                    res = following;
                } else {
                    int sum_key = summa(key);
                    int sum_fol=summa(following->key);
                    int sum_pre= summa(previous->key);
                    if(abs(sum_key-sum_fol)<abs(sum_key-sum_pre)){
                        res=following;
                    }
                    else{
                        res=previous;
                    }
                }
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

Item *max(Item *ptr) {
    Item *x = ptr;
    while (x != NULL && x->right != NULL) {
        x = x->right;
    }
    return x;
}

int delete(Item **root, char *key, int flag) {

    if (*root == NULL) {
        return 4;
    }
    Item *x = find(*root, key);
    if (x == NULL) {
        return 3;
    } else {
        if (x == *root) { // удаляемый элемент корень
            if ((*root)->left == NULL) {
                if ((*root)->right == NULL) {
                    *root = NULL;
                    free(x->info->string);
                    free(x->info);
                    free(x->key);
                } else {
                    (*root)->info = (*root)->right->info;
                    if ((*root)->right->left != NULL) {
                        (*root)->right->left->parent = (*root);
                    }
                    if ((*root)->right->right != NULL) {
                        (*root)->right->right->parent = (*root);
                    }
                    char *s = x->right->key;
                    delete(root, s, 1);
                    (*root)->key = s;

                }
            } else {
                if ((*root)->right == NULL) {
                    (*root)->info = x->left->info;
                    if ((*root)->left->left != NULL) {
                        (*root)->left->left->parent = (*root);
                    }
                    if ((*root)->left->right != NULL) {
                        (*root)->left->right->parent = (*root);
                    }
                    char *s = x->left->key;
                    delete(root, s, 1);
                    (*root)->key = s;
                } else {
                    if ((*root)->right->left != NULL) {
                        (*root)->right->left->parent = (*root);
                    }
                    if ((*root)->right->right != NULL) {
                        (*root)->right->right->parent = (*root);
                    }
                    if ((*root)->left->left != NULL) {
                        (*root)->left->left->parent = (*root);
                    }
                    if ((*root)->left->right != NULL) {
                        (*root)->left->right->parent = (*root);
                    }
                    Item *y = min(x->right);
                    (*root)->info = y->info;
                    char *s = y->key;
                    delete(root, s, 1);
                    (*root)->key = s;
                }
            }

        } else {
            if (x->left == NULL) { // нет левого поддерева
                if (x->parent->left == x) {
                    x->parent->left = x->right;
                    if (x->right != NULL) {
                        x->right->parent = x->parent;
                    }
                } else {
                    x->parent->right = x->right;
                    if (x->right != NULL) {
                        x->right->parent = x->parent;
                    }
                }
                if (flag == 0) {
                    free(x->info->string);
                    free(x->info);
                    free(x->key);
                }
            } else {
                if (x->right == NULL) { // нет правого поддерерва
                    if (x->parent->left == x) {
                        x->parent->left = x->left;
                        if (x->left != NULL) {
                            x->left->parent = x->parent;
                        }
                    } else {
                        x->parent->right = x->left;
                        if (x->left != NULL) {
                            x->left->parent = x->parent;
                        }

                    }
                    if (flag == 0) {
                        free(x->info->string);
                        free(x->info);
                        free(x->key);
                    }

                } else {  // есть левое и правое
                    Item *y = min(x->right);
                    x->info = y->info;
                    char *s = y->key;
                    delete(root, s, 1);
                    x->key = s;
                }
            }
        }
    }
    return 0;
}

void delete_all(Item *ptr) {
    if (ptr != NULL) {
        delete_all(ptr->left);
        delete_all(ptr->right);
        free(ptr->info->string);
        free(ptr->info);
        free(ptr->key);
        free(ptr);
    }
}
int work_with_file(Item** root,char *name){
    int res;

    return res;
}