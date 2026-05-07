- What are some benefits of abstraction layers when it comes to hardware support in the OS?

abstractions allow you to preform I/O's without having to worry about interreacting with the what is stored on disk and instead can just interface with the OS programing language

- If you switched from PIO to DMA-with-interrupts, how would that potentially improve performance?

that would help performance because PIO has to micromanage the transfer of data which is very time consuming and cant be interrupted for another task typically while DMA with interrupts can delegate work and be interrupted

- Why might you prefer memory-mapped I/O to port-based I/O?

memory-mapped I/O is typically preferred because it is faster and and allows more interaction with the peripheral