//
// Created by ivan on 01.05.2021.
//

#ifndef PROGA4_A_DIALOG_H
#define PROGA4_A_DIALOG_H

#include "item.h"

int dialog(const char *msgs[], int n);
int D_Add(Item *ptr);
int D_Delete(Item *ptr);
int D_Find(Item *ptr);
int D_Show(Item *ptr);
int D_Find_Nearest(Item *ptr);


#endif //PROGA4_A_DIALOG_H
