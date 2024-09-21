/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * SystemCalls - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
 * Irem Yildiz 2125282
 * Pablo Cabale Guerra 2129466
*/


#include <stdio.h>
#include <fcntl.h>

int main () {
    char buffer;
    int file;
    __ssize_t bytesRead, bytesWritten;

    file = open("systemcalls_output2.txt", O_WRONLY | O_TRUNC, 0644);
    if(file == -1) {
        perror("Appel système open a échoué");
        return 1;
    }
    
    write(1,"Saisissez votre texte suivi de CTRL-D :\n", 40);

    while (bytesRead = read(0, &buffer, 1) > 0) {
        bytesWritten = write(file, &buffer, bytesRead);
        if(bytesWritten == -1){
            perror("Appel système write a échoué");
            close(file);
            return 1;
        }
    }

    if (bytesRead == -1) {
        perror("Appel système read a échoué");
        close(file);
        return 1;
    }

    close(file);
    return 0;
}

