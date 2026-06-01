#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "image.h"

int image_fd;

// opens image and returns file descriptor
int image_open(char *filename, int truncate)
{
    if (truncate == 1)
    {
        image_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    }
    else
    {
        image_fd = open(filename, O_RDWR | O_CREAT, 0600);
    }

    return image_fd;
}

// closes image
int image_close(void)
{
    return close(image_fd);
}