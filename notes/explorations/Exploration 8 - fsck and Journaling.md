- Describe a scenario in which the metadata of a disk would be inconsistent. What data would be in disagreement?

things can get inconsistent when you modify metadata without first writing the inode because then the actual metadata of the block and the inode data would b in disagreement

- Describe one type of correction to broken metadata `fsck` would be able to handle and how it would accomplish it.

it could have incorrect file size in which case `fsck` would have to verify that the data is incorrect and what the correct information is, then detect where the problem is, and then correct it

- In metadata-only journaling, why does the data block get written _before_ the journal entry is processed?

to prevent data corruption