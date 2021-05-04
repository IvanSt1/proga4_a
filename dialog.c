#include <stdio.h>
#include "dialog.h"
#include "get.h"
#include "item.h"
const char *errmsgs[] = {"OK", "Duplicate key", "Table overflow", "Wrong parent key"};
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
int D_Delete(Item **ptr){
    return 1;
}
int D_Find(Item **ptr){
    return 1;
}
int D_Show(Item **ptr){
    return 1;
}
int D_Find_Nearest(Item **ptr){
    return 1;
}