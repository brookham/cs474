#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

int stat(const char *pathname, struct stat *statbuf);
char fullpath[4096];

/*
 * Takes a dirname as a string ("." for current directory) and shows the
 * contents of that directory.
 */
void ls(const char *dirname)
{
    DIR *dir = opendir(dirname);

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        struct stat i_info;
        sprintf(fullpath, "%s/%s", dirname, ent->d_name);

        if (stat(fullpath, &i_info) == -1){
            continue;
        }

        printf("%s, %lu, %o, %d, %d, %ld, %ld, %ld\n", ent->d_name, ent->d_ino, i_info.st_mode, i_info.st_uid, i_info.st_gid, i_info.st_size);
    }

    closedir(dir);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: myls dirname\n");
        exit(1);
    }

    char *dirname = argv[1];
    
    ls(dirname);
}