# PageReplacement_Algorithms
Page replacement algorithms to analyse page fault and belady's anomaly and thrashing.

## Algorithms
1. Least Recently Used (LRU)
2. Most Recently Used (MRU)

## How to run
1. Clone the repository
2. Run the following commands in the terminal to compile the code:
    ```bash
    g++ mru.cpp pbPlots.cpp supportLib.cpp -lm -o mru
    g++ lru.cpp pbPlots.cpp supportLib.cpp -lm -o lru
    ```
3. Run the following commands in the terminal to generate plots:
    ```bash
    ./mru <trials> <maxFrameSize> <maxPageArraySize>
    ./lru <trials> <maxFrameSize> <maxPageArraySize>
    ```
    Replace the placeholders with the desired values. (They will fall back to default values if not provided)
    This will generate plots for both the algorithms in ./plots/ folder.
    Naming convention for the plots is as follows:
    "Least Recently Used-\<number of trials\>-\<maxFrameSize\>-\<maxPageArraySize\>"
Note: All three command line args must be provided or none of them would be considered and the program will fall back to default values.

