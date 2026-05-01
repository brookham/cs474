- For a 32-bit address space with 4KB pages and 4-byte PTEs, calculate the size of a single linear page table. If a system has 100 active processes, how much memory is consumed by page tables alone?

the page table would be 4mb so if there are 100 pages it would consume 400mb

- Increasing page size reduces page table size. Why isn't this the preferred solution to the page table bloat problem? What specific memory pathology does it introduce?

because the bigger the pages, the more is wasted within the pages which leads to internal fragmentation

- What is the key insight that allows a multi-level page table to save memory compared to a linear page table? Under what condition is a page of page-table entries not allocated?

the key insight is to rely on segmentation. if a whole page of a page table is invalid it is not allocated

- Both PDEs and PTEs have a valid bit, but the bit means something different in each. Explain the distinction.

if the bit in the PDE is valid it means that at least one of the pages in the table are valid, while in the PTE it means that it is valid if it is being pointed to by a valid PDE

- A two-level page table incurs two memory accesses on a TLB miss, compared to one for a linear page table. Why doesn't this typically destroy performance in practice?

because two loads of memory are required to get the right translation info from the page table

- Given a 30-bit virtual address space with 512-byte pages and 4-byte PTEs, explain why a two-level page table fails to meet the design goal of fitting each piece of the page table within a single page, and what must be done to fix it.

because the page directory will be to big to fit in a single page. in order to make every thing fit you would need to keep splitting things onto different levels and different pages

- The chapter frames multi-level page tables as a time-space trade-off. Concretely describe what is being traded: what space is saved, and what time cost is paid?

you get smaller tables with multi level page tables but have to pay the price when dealing with TLB misses for example 