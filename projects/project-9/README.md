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
- `inode.c`: code for inode allocation, lookup, and read/write helpers
- `inode.h`: header file for inode structures and function declarations
- `pack.c`: code to read and write packed integer values in big-endian order
- `pack.h`: header file for packed read/write helper declarations
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

- `find_low_clear_bit()`: finds lowest free bit within byte

- `set_free()`: sets free bit in block to desired value

- `find_free()`: finds lowest free bit in block
    - `find_low_clear_bit()`  

- `read_u32()`: reads a 32-bit value from a packed byte buffer
- `read_u16()`: reads a 16-bit value from a packed byte buffer
- `read_u8()`: reads an 8-bit value from a packed byte buffer

- `write_u32()`: writes a 32-bit value to a packed byte buffer
- `write_u16()`: writes a 16-bit value to a packed byte buffer
- `write_u8()`: writes an 8-bit value to a packed byte buffer

- `ialloc()`: allocates a previously-free inode in the inode map
    - `bread()`
    - `find_free()`
    - `set_free()`
    - `bwrite()`

- `incore_find_free()`: finds a free in-core inode slot

- `incore_find()`: finds an in-core inode by inode number

- `incore_free_all()`: clears the in-core inode table

- `read_inode()`: reads an inode from disk into memory
    - `bread()`
    - `read_u32()`
    - `read_u16()`
    - `read_u8()`

- `write_inode()`: writes an inode from memory to disk
    - `bread()`
    - `write_u32()`
    - `write_u16()`
    - `write_u8()`
    - `bwrite()`

- `iget()`: gets an in-core inode for a given inode number
    - `incore_find()`
    - `incore_find_free()`
    - `read_inode()`

- `iput()`: releases an in-core inode
    - `write_inode()`

- `alloc()`: allocates a previously-free inode in the free block map
    - `bread()`
    - `find_free()`
    - `set_free()`
    - `bwrite()`

- `mkfs()`: initializes file system
    - `memset()`: sets value of specified bits
    - `bwrite()`
    - `alloc()`