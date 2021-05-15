#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 9

int collision(){
    int pote[DIM], i, j, counter, table[DIM];
    pote[0] = table[0];
    for (i = 1; i != DIM-1; ++i){
        for(j = 0; j != i; ++j)
            if (pote[j] == table[i]) ++counter;
        pote[i] = table[i];
    }
    return counter;