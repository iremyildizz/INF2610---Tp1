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
    int totalChildren = 0;

    registerProc(getpid(), getppid(), 0, 0);

    if(fork() == 0){
        registerProc(getpid(), getppid(), 1, 1);
        if(fork() == 0) {
            registerProc(getpid(), getppid(), 2, 1);
            _exit(0);
        }

        int childTotalChildren = 0;
        wait(&childTotalChildren);
        _exit(1 + WEXITSTATUS(childTotalChildren));
    }  
    else if(fork() == 0){
        registerProc(getpid(), getppid(), 1, 2);
        if(fork() == 0) {
            registerProc(getpid(), getppid(), 2, 2);
            _exit(0);
        }

        int childTotalChildren = 0;
        wait(&childTotalChildren);
        _exit(1 + WEXITSTATUS(childTotalChildren));
    }  
    else if(fork() == 0){
        int level13Children = 0;
        registerProc(getpid(), getppid(), 1, 3);

        for(int i = 0; i < LEVEL_13_CHILDREN; i++){
            if(fork() == 0){
                registerProc(getpid(), getppid(), 2, i+3);
                _exit(0);
            } 

            int childTotalChildren = 0;
            wait(&childTotalChildren);
            level13Children += 1 + WEXITSTATUS(childTotalChildren);
        }

        return _exit(level13Children);
    }
    else{
        int childTotalChildren = 0;
        for (int i = 0; i < 3; i++) {
            wait(&childTotalChildren);
            printf("Nombre d'enfants créés par l'enfant %d: %d\n", i + 1, 1 + WEXITSTATUS(childTotalChildren));
            totalChildren += 1 + WEXITSTATUS(childTotalChildren);
        }

        printf("Nombre d'enfants créés par la racine: %d\n", totalChildren);

        printProcRegistrations();
    }
}

