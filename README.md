# PageReplacement_Algorithms
Page replacement algorithms to analyse page fault and belady's anomaly and thrashing.

## Algorithms
1. Least Recently Used (LRU)
2. Most Recently Used (MRU)

## Some Useful Information
- The reference string is randomly generated using a seed value. This seed value is generated using the current time. So, the reference string will be different every time the program is run.
- The user can provide 3 values as command line arguments. These values are:
    1. Maximum frame size
    2. Maximum page array size (the maximum number of pages in the reference string)
    3. Flag

### Flags
- **sf**: Fixed reference string for each call as the frame size increments.
- **sr**: Random reference string for each call as the frame size increments.

## How to run
1. Clone the repository
2. Run the following commands in the terminal to compile the code:
    ```bash
    g++ mru.cpp pbPlots.cpp supportLib.cpp -lm -o mru
    g++ lru.cpp pbPlots.cpp supportLib.cpp -lm -o lru
    ```
3. Run the following commands in the terminal to generate plots:
    ```bash
    ./mru <maxFrameSize> <maxPageArraySize> -<flag>
    ./lru <maxFrameSize> <maxPageArraySize> -<flag>
    ```
    Replace the placeholders with the desired values. [^1] <br/>

This program will generate plots for the algorithms in "./plots/" folder. <br/>
    
Naming convention for the plots is as follows:
    **"\<Algorithm Name\>-\<flag\>-\<maxFrameSize\>-\<maxPageArraySize\>"**

[^1]: Note: All three command line args must be provided.

