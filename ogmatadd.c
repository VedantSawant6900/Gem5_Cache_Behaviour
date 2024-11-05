#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#ifdef FRMWRK
#include "gem5/m5ops.h"
#endif    

void doadd(int *mata,int* matb,int* matc, int size) {
    printf("Do add\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            matc[i*size+j] = mata[i*size+j] + matb[i*size+j];
        }
    }
}

int main(int argc, char *argv[]) {

    char *p;

    int size = atoi(argv[1]);
    
    int *mata;
    int *matb;
    int *matc;
    mata = (int*)(malloc(sizeof(int)*size*size));
    matb = (int*)(malloc(sizeof(int)*size*size));
    matc = (int*)(malloc(sizeof(int)*size*size));

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            mata[i*size+j] = i*size+j;
            matb[i*size+j] = i*size+j;
        }
    }

#ifdef FRMWRK
    m5_reset_stats(0,0);
#endif

    doadd(mata, matb, matc, size);

#ifdef FRMWRK
    m5_dump_stats(0,0);
#endif    

    printf("\n Done computation \n");
    bool frmwrk_validation = true;
    int incorrect=0; int correct=0;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if ((mata[i*size+j]+matb[i*size+j]) != matc[i*size+j]) {
               printf("Mismatch (%d,%d) - %d,%d,", i, j, mata[i*size+j], matb[i*size+j]);
               printf("%d vs %d\n", mata[i*size+j]+matb[i*size+j], matc[i*size+j]);
               frmwrk_validation = false;
               incorrect++;
            } else {
               correct++;
            }
        }
    }

    if (frmwrk_validation)
      printf("FRMWRK VALIDATION SUCCESSFUL\n");
    else
      printf("FRMWRK VALIDATION FAILED %d-%d\n", correct, incorrect);

    free(mata);
    free(matb);
    free(matc);

}

