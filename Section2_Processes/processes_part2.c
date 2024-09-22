/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 4

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
    long sumTotal = 0;
    intptr_t number = (intptr_t)p;

    for(int i=(number * m/nb) + 1; i <= (number + 1) * m/nb; i++) {
        sumTotal += i;
    }

    somme[number] = sumTotal;
    return NULL;
}


void question2( )
{
    long sumTotal = 0;
    long calculationFormula = ((long)m*((long)m+1))/2;
    pthread_t* tid = malloc (nb * sizeof(pthread_t));

    for(int i=0; i <nb; i++) { 
      pthread_create(&tid[i], NULL, contribution, (void*)(intptr_t)i);
    }

    for (int i = 0; i < nb; i++) {
      pthread_join(tid[i], NULL);
    }    

    for (int i = 0; i < nb; i++) { 
        sumTotal += somme[i];
    }

    printf("La somme des %d premiers nombres naturels est %ld et %ld\n", m, sumTotal, calculationFormula);
}

