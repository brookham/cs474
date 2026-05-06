- What's in the inode?

a data structure holding the metadata for a single file

- We describe a free block bitmap in this exploration. What other ways might we represent free blocks in the system?

you could use a free list that points to the first free block and the next and so on

- Why would not having a buffer cache make things run more slowly?

because without it there are many more I/O's to the disk which is expensive and take more time