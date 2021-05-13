#include <stdio.h>
#include <string.h>
#include "dialog.h"
#include "get.h"
#include "item.h"

const char *msgs[] = {"1. Quite", "2. Add", "3. Delete", "4. Find", "5. Show", "6. Find Nearest Key",
                      "7. Show exceeding the key"};
const int NMgsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*f[])(Item **) ={NULL, D_Add, D_Delete, D_Find, D_Show, D_Find_Nearest, D_Show_Exceeding_Key};

int main() {
    Item *root = NULL;
    int rc;
    rc = dialog(msgs, NMgsgs);
    printf("Do you want to work with file? (y/n)");
    char *answer = Get_Str();
    if (answer==NULL){
        printf("something goes wrong restart");
        return 0;
    }
    int k1 = strcmp("y", answer);
    int k2 = strcmp("n", answer);
    while ((k1 != 0) && (k2 != 0)) {
        printf("Try one more time");
        answer=Get_Str();
        if (answer==NULL){
            printf("something goes wrong restart");
            return 0;
        }
        k2 = strcmp("n", answer);
        k1 = strcmp("y", answer);
    }
    if (k1 == 0) {
        Add_from_file(&root);
    }
    while (rc) {
        if (!f[rc](&root)) {
            break;
        }
        rc = dialog(msgs, NMgsgs);
    }
    D_Delete_ALL(&root);
    return 0;
}