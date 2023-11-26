#include <bits/stdc++.h>
using namespace std;

int pageFaults(int pages[], int n, int capacity)
{
    // Page record
    unordered_set<int> s;
    // Page index
    unordered_map<int, int> indexes;

    long long pageFaults = 0;
    for (int i = 0; i < n; i++)
    {
        // Empty spaces in memory
        if (s.size() < capacity)
        {
            // Page not present
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                pageFaults++;
            }
            indexes[pages[i]] = i;
        }
        else
        {
            // Page not present
            if (s.find(pages[i]) == s.end())
            {
                int leastRecentlyUsed = INT_MAX;
                int val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] < leastRecentlyUsed)
                    {
                        leastRecentlyUsed = indexes[*it];
                        val = *it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
                pageFaults++;
            }
            indexes[pages[i]] = i;
        }
    }
    return pageFaults;
}

int main()
{
    int trials = 100;
    int maxPageSize = 1000;
    int maxFrameSize = 1000;
    map<int,int> pageFaultsToFrameSize;
    for (int i = 0; i < trials; i++)
    {
        int pageSize = rand() % maxPageSize;
        int pages[pageSize];
        for (int j = 0; j < pageSize; j++)
        {
            pages[j] = rand() % maxPageSize;
        }
        int capacity = rand() % maxFrameSize;
        pageFaultsToFrameSize[capacity] = pageFaults(pages, pageSize, capacity);
    }
    cout << "Frame Size  | Page Faults" << endl;
    for (auto it = pageFaultsToFrameSize.begin(); it != pageFaultsToFrameSize.end(); it++)
    {
        cout << setw(12) << it->first << "|" << setw(12) << it->second << endl;
    }
    return 0;
}