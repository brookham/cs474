## Direct Memory Access (DMA)
- With Disks:
	- request a block read
	- go about my business
	- when the disk reads the data, the disk hardware stores it directly in RAM
	- when an interrupt is raised, process it
		- us the data that was stored 


## IO Methods

### Port IO
- the CPU has a number of "ports", 16 for example.
- you can input bytes from ports, or output bytes to ports
- the ports control hardware
- Assembly instructions:
	- `INB`
	- `OUTB`
### Memory-Mapped I/O
- Certain memory addresses represent hardware
- store certain values at certain addresses, controls the hardware

