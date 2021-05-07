#include <stdio.h>
#include "dialog.h"
#include "get.h"
#include "item.h"
const char *msgs[] = {"1. Quite", "2. Add","3. Delete", "4. Find", "5. Show", "6. Find Nearest Key"};
const int NMgsgs = sizeof(msgs) / sizeof(msgs[0]);
int (*f[])(Item **) ={NULL, D_Add, D_Delete, D_Find,D_Show,D_Find_Nearest};
int main() {
    Item *root=NULL;
    int rc;
    rc = dialog(msgs, NMgsgs);
    while (rc) {
        if (!f[rc](&root)) {
            break;
        }
        rc = dialog(msgs, NMgsgs);
    }
    return 0;
}