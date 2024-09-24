/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
 * Irem Yildiz 2125282
 * Pablo Cabale Guerra 2129466
*/
#include "challenges_part1.h"

int isDirectory(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int countTxtFiles(const char* path) {
    int txtFilesCount = 0;
    struct dirent* entry;

    DIR* dir = opendir(path);
    if(dir == NULL) {
        perror("opendir");
        return 0;
    }

    char** txtFiles = NULL;
    int txtCount = 0;

    char** subdirectories = NULL;
    int subdirectoriesCount = 0;

    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        char newPath[MAX_PATH_LENGTH];
        snprintf(newPath, MAX_PATH_LENGTH, "%s/%s", path, entry->d_name);

        if(isDirectory(newPath)) {
            subdirectories = realloc(subdirectories, (subdirectoriesCount + 1) * sizeof(char*));
            subdirectories[subdirectoriesCount] = strdup(newPath);
            subdirectoriesCount++;
        } else {
            txtFiles = realloc(txtFiles, (txtCount + 1) * sizeof(char*));
            txtFiles[txtCount] = strdup(entry->d_name);
            txtCount++;
        }
    }
    
    closedir(dir);

    txtFilesCount += txtCount;

    for(int i = 0; i < txtCount; i++) {
        free(txtFiles[i]);
    }
    free(txtFiles);

    for(int i = 0; i < subdirectoriesCount; i++) {
        pid_t pid = fork();

        if(pid == 0) {
            int subdirectoryTxtFiles = countTxtFiles(subdirectories[i]);
            _exit(subdirectoryTxtFiles);
        } else {
            int status;
            waitpid(pid, &status, 0);
            txtFilesCount += WEXITSTATUS(status);
        }
    }

    for(int i = 0; i < subdirectoriesCount; i++) {
        free(subdirectories[i]);
    }
    free(subdirectories);

    return txtFilesCount;
}

int main(int argc, char*argv[]) {
    int totalTxtFiles = 0;
    const char* rootDir = "./root";

    totalTxtFiles = countTxtFiles(rootDir);

    printf("Nombre de fichiers txt: %d\n", totalTxtFiles);

    return 0;
}



