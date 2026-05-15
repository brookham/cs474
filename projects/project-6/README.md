## Building
Command Line:
- `make` to build. Object files for `block`, `image`, and `testfs` will be built along with a library called `libvvsfs.a`
- `make clean` to clean all build products execpt the executables.
- `make pristine` to clean all the biuld products entirely


## Files

- `block.c`: code to read and write to specified block
- `block.h`: header file that stores block functions 
- `image.c`: code to create/open and close image files
- `image.h`: header file for storing image functions
- `testfs.c`: test suite for block and image functions
- `ctest.h`: header file for test suite

## Functions
- `image_open()`: create/open image and return `image_fd`
    - `open()`: opens file and returns file descriptor
    
- `image_close()`: closes `image_fd`
- `bread()`: reads block data to buffer and returns buffer pointer
    - `lseek()`: repositions file offset for `image_fd`
    - `read()`: reads data from `image_fd` into buffer

- `bwrite()`: writes to a specfic location in block
    - `lseek()`: repositions file offset for `image_fd`
    - `write()`: writes data from buffer to file descriptor