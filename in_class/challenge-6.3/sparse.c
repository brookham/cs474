#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("foo.txt", O_CREAT|O_TRUNC|O_WRONLY, 0660);

    lseek(fd, 400000000, SEEK_SET);

    write(fd, "", 1);

    close(fd);
}

// -rwxrwxrwx 1 bhami bhami 382M May  6 11:14 foo.txt
// 382M    .
// the difference is becasue there is only one block being stored