#include <stdio.h>
#include <malloc.h>
#include "dialog.h"
#include "get.h"
#include "item.h"
const char *errmsgs[] = {"OK", "Duplicate key", "Memory problem","There is no such key", "Table is empty"};
int dialog(const char *msgs[], int n) {
    char *errmsg = "";
    int rc;
    int i, p;
    do {
        puts(errmsg);
        errmsg = "You are wrong";
        for (i = 0; i < n; ++i)
            puts(msgs[i]);
        puts("Make your choise: -->");
        p = Get_Int(&rc);
        if (p == 0)
            rc = 0;
    } while (rc < 0 || rc > n);
    rc--;
    return rc;
}
int D_Add(Item **root){
    int first,second,rc;
    char *key;
    char *third;
    printf("Enter key:\n");
    key = Get_Str();
    if (key == NULL) {
        return 0;
    }
    printf("Enter info:\n");
    printf("Enter first integer: -->");
    Get_Int(&first);
    printf("Enter second integer: -->");
    Get_Int(&second);
    printf("Enter string: -->");
    third = Get_Str();
    if (third == NULL) {
        return 0;
    }
        rc = insert(root, key, first, second, third);
        printf("%s\n", errmsgs[rc]);
        return 1;

}
int D_Delete(Item **root){
    char* key;
    printf("Enter key:\n");
    key = Get_Str();
    if (key == NULL) {
        return 0;
    }
    int rc=delete(root,key,0);
    printf("%s",errmsgs[rc]);
    free(key);
    return 1;
}
int D_Find(Item **root){
    char *key;
    printf("Enter key:\n");
    key = Get_Str();
    if (key == NULL) {
        return 0;
    }
    Item *x =find(*root,key);
    if (x==NULL){
        printf("There is no such key: %s\n",key);
    }
    else{
        printf("key: %s | first number: %d | second number: %d | information string: %s\n",x->key,x->info->num1,x->info->num2,x->info->string);
    }
    free(key);
    return 1;
}
int D_Show(Item **root){
    int rc= show(root);
    if (rc==0){
        printf("Table is empty");
    }
    return 1;
}
int D_Find_Nearest(Item **root){
    char *key;
    printf("Enter key:\n");
    key = Get_Str();
    if (key == NULL) {
        return 0;
    }
    Item *x =find_nearest(*root,key);
    if (x==NULL){
        printf("There is no such key: %s\n",key);
    }
    else{
        printf("key: %s | first number: %d | second number: %d | information string: %s\n",x->key,x->info->num1,x->info->num2,x->info->string);
    }
    free(key);
    return 1;
}
void D_Delete_ALL(Item **ptr){
    if(ptr!=NULL){
        delete_all(*ptr);
    }
}
int D_Show_Exceeding_Key(Item**ptr){
    char *key;
    printf("Enter key:\n");
    key = Get_Str();
    if (key == NULL) {
        return 0;
    }
    Item* x=find(*ptr,key);
    if (x==NULL){
        printf("There is no such key: %s\n",key);
    }
    else{
        work(x->right);
    }
    free(key);
    return 1;
}
void Add_from_file(Item** root){
    printf("Enter file Name\n");
    char* name=Get_Str();
    if (name==NULL){
        return ;
    }
   FILE *file = fopen(name, "r");
    while (file==NULL){
        printf("There is no such file, try one more time\n");
        printf("Enter file Name\n");
        name=Get_Str();
        if (name==NULL){
            return ;
        }
        file = fopen(name, "r");
    }
   int res= work_with_file(root,file);
    if (res!=0){
        printf("Format of information is wrong in file\n");
        D_Delete_ALL(root);
    }
    else{
        printf("Successful reading from file\n");
    }
}
