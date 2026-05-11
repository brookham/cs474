
## Project 7
- we have to keep track of free blocks on the disk
- each byte of the free map will have 8 Booleans in it
	- we can tell if any of 8 blocks are free per byte of the free map
- we also have to do this for the free inode map
- you have to map from a block number to a byte number in the free map
- you have to map from a block number to a bit number inside that byte
## Bitwise Operations
