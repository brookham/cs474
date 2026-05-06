#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Display a file on stdout.
 */
void cat(char *filename)
{
    char buf[4096];
    int count;

    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        perror("cat");
        return;
    }

    do {
        count = read(fd, buf, sizeof buf);
        write(1, buf, count);
    } while (count > 0);

    write(1, "\n", 1);

    close(fd);
}

/**
 * Main.
 */
int main(void)
{
    // Allowed functions: open, lseek, write, close

    // TODO: Open the file `seeker.txt` for writing
    int file = open("seeker.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // TODO: Write 60 `-` characters to the file
    for (int i = 0; i < 60; i++) {
        write(file, "-", 1);
    }
    
    // TODO: Seek to position 0
    lseek(file, 0, SEEK_SET);

    // TODO: Write "interrupting"
    write(file, "interrupting", 12);

    // TODO: cat("seeker.txt");
    cat("seeker.txt");

    // TODO: Seek to position 40
    lseek(file, 40, SEEK_SET);

    // TODO: Write "cow"
    write(file, "cow", 3);

    // TODO: cat("seeker.txt");
    cat("seeker.txt");

    // TODO: Seek to position 20
    lseek(file, 20, SEEK_SET);

    // TODO: Write "MOOOOOOO!"
    write(file, "MOOOOOO0", 8);

    // TODO: cat("seeker.txt");
    cat("seeker.txt");

    // TODO: Close the file
    close(file);
}