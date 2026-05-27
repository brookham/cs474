## fsck-File System Check
- what can go wrong?
	- what happens when we create a file?
		- allocate a new block
		- allocate an inode
		- populate the inode
		- a new directory entry is made
			- the directory is a file
			- update directory inode
			- potentially new block allocation

## Journaling Filesystem
- all modern systems use these by default

### How it works
- write out *what* we are going to do to the journal.
- copy the data out of the journal onto the disk
- remove the data from the journal

## Example
- Write to the journal:
	- transaction start
	- inode changes
	- free block changes
	- data block
	- transaction end

- One we have the *txe* (transaction end), we replay the commands from the journal onto the disk
  
- remove the journal entry
  
- speed improvement:
	- data block written straight to disk
	- transaction start
	- inode changes
	- free block changes
	- transaction end