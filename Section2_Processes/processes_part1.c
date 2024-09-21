/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"

const int LEVEL_13_CHILDREN = 4;

void question1()
{
    if(fork() == 0)
        fork();
    else if(fork() == 0)
        fork();
    else if(fork() == 0){
        for(int i = 0; i < LEVEL_13_CHILDREN; i++)
            if(fork() == 0)
                break;
    }
}

