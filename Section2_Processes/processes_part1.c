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
    if(fork() == 0){
        registerProc(getpid(), getppid(), 1, 1);
        if(fork() == 0) {
            registerProc(getpid(), getppid(), 2, 1);
        }
    }  
    else if(fork() == 0){
        registerProc(getpid(), getppid(), 1, 2);
        if(fork() == 0) {
            registerProc(getpid(), getppid(), 2, 2);
        }
    }  
    else if(fork() == 0){
        registerProc(getpid(), getppid(), 1, 3);
        for(int i = 0; i < LEVEL_13_CHILDREN; i++){
            if(fork() == 0){
                registerProc(getpid(), getppid(), 2, i+LEVEL_13_CHILDREN-1);
                break;
            } 
        }       
    }
    else{
        wait(NULL);
        registerProc(getpid(), getppid(), 0, 0);
    }
}

