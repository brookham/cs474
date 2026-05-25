- What could go wrong if SSDs used a direct mapping from logical blocks to pages?

there would be both performance problems on the writes when it has to read in the block, erase it, and the program it, and also reliability problems when you constantly have to write, erase, and override the block it starts to ware out and can break down

- What is it about log structuring that causes garbage collection to be required?

you need a garbage collector because the overwritten logical blocks result in garbage so you need to collect them to make space for future writes

- What is _write amplification_?

the total write traffic issued to the flash chips by the FTL / total write traffic issued by client to SSD
