# OS_Assignment4

## Page Replacement Algorithms
This programming assignment implements three different page replacement algorithms: LRU, Optimal, and First-In, First-Out (FIFO). These algorithms are mainly used in OS to manage memory and reduce page faults.

## Algorithms

### Least Recently Used (LRU)
This algorithm replaces the least recently used pages when a page fault occurs and when there is no more space in memory. If a page is referenced, it is moved to the top of the stack. When a page fault occurs, the page at the bottom of the stack is replaced.

### Optimal
This algorithm replaces page that will not be used for the longest period of time in the future. Basically, this algorithm requires future knowledge of the reference string.

### First-In, First-Out (FIFO)
This algorithm treats the page frames allocated to a process as a circular buffer and pages are removed using the round-robin style. It replaces the oldest page.

## Execution Instruction
As this is a .cpp file, please use C++ to run this file.
