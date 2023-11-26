# PageReplacement_Algorithms
Page replacement algorithms to analyse page fault and belady's anomaly and thrashing.

## Algorithms
1. Least Recently Used (LRU)
2. Most Recently Used (MRU)

## How to run
1. Clone the repository
2. Run the following commands in the terminal
    ```bash
    g++ mru.cpp pbPlots.cpp supportLib.cpp -lm -o mru
    ./mru
    g++ lru.cpp pbPlots.cpp supportLib.cpp -lm -o lru
    ./lru
    ```
    This will generate plots for both the algorithms in ./plots/ folder.
    Naming convention for the plots is as follows:
    "Least Recently Used-\<number of trials\>-\<maxFrameSize\>-\<maxPageArraySize\>"
3. The values of number of trials, maxFrameSize and maxPageArraySize can be changed in the respective files.

