#include <bits/stdc++.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"
using namespace std;

void printPageFaultMap(map<int, int> pageFaultsToFrameSize)
{
    cout << "Frame Size  | Page Faults" << endl;
    for (auto it = pageFaultsToFrameSize.begin(); it != pageFaultsToFrameSize.end(); it++)
    {
        cout << setw(12) << it->first << "|" << setw(12) << it->second << endl;
    }
}

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

void plotGraph(vector<double> x, vector<double> y, char* flag, int maxFrameSize, int maxPageSize)
{
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();

    wstring flagText;
    string flagTextString;

    if(string(flag) == "-sf")
    {
        flagText = L"Fixed";
        flagTextString = "Fixed";
    }
    else if(string(flag) == "-sr")
    {
        flagText = L"Random";
        flagTextString = "Random";
    }
    else
    {
        flagText = L"";
    }

    wstring titleText = L"Least Recently Used-" + flagText + L"-" + to_wstring(maxFrameSize) + L"-" + to_wstring(maxPageSize);
    string titleTextString = "Least Recently Used-" + flagTextString + "-" + to_string(maxFrameSize) + "-" + to_string(maxPageSize);
    const wchar_t *titleTextConverted = titleText.c_str();

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->linearInterpolation = true;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1920;
    settings->height = 1080;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(titleTextConverted);
    settings->xLabel = toVector(L"Page Faults");
    settings->yLabel = toVector(L"Frame Size");
    settings->scatterPlotSeries->push_back(series);

    DrawScatterPlotFromSettings(imageRef, settings);

    vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plots/" + titleTextString + ".png");
    DeleteImage(imageRef->image);

    return;
}

void plotFromMap(map<int, int> pageFaultsToFrameSize, char* flag, int maxFrameSize, int maxPageSize)
{
    // Plotting
    vector<double> x;
    vector<double> y;

    for (auto it = pageFaultsToFrameSize.begin(); it != pageFaultsToFrameSize.end(); it++)
    {
        x.push_back(double(it->first));
        y.push_back(double(it->second));
    }

    plotGraph(x, y, flag, maxFrameSize, maxPageSize);
}

void referenceStringFixed(int maxFrameSize, int maxPageSize, char* flag)
{
    map<int, int> pageFaultsToFrameSize;
    int pages[maxPageSize];
    srand(time(0));
    for (int i = 0; i < maxPageSize; i++)
    {
        pages[i] = rand() % maxPageSize;
    }
    for (int frameSize = 1; frameSize < maxFrameSize; frameSize++)
    {
        pageFaultsToFrameSize[frameSize] = pageFaults(pages, maxPageSize, frameSize);
    }

    printPageFaultMap(pageFaultsToFrameSize);
    plotFromMap(pageFaultsToFrameSize, flag, maxFrameSize, maxPageSize);
}

// reference string is randomised at frame size
void referenceStringRandom(int maxFrameSize, int maxPageSize, char* flag)
{
    map<int, int> pageFaultsToFrameSize;
    srand(time(0));
    int pageSize = maxPageSize;
    int pages[pageSize];
    for (int frameSize = 1; frameSize < maxFrameSize; frameSize++)
    {
        for (int i = 0; i < maxPageSize; i++)
        {
            pages[i] = rand() % maxPageSize;
        }
        pageFaultsToFrameSize[frameSize] = pageFaults(pages, maxPageSize, frameSize);
    }

    printPageFaultMap(pageFaultsToFrameSize);
    plotFromMap(pageFaultsToFrameSize, flag, maxFrameSize, maxPageSize);
}

int main(int argc, char *argv[])
{
    int maxFrameSize = 100;
    // Represents the maximum number of pages not maxPageSize
    int maxPageSize = 10;

    if(argc < 3)
    {
        cerr << "Usage: ./mru <maxFrameSize> <maxPageSize> -<flag>" << endl;
        return 0;
    }

    if (argc == 4)
    {
        if (string(argv[3]) == "-sr")
        {
            referenceStringRandom(maxFrameSize, maxPageSize, argv[3]);
            return 0;
        }
        else if (string(argv[3]) == "-sf")
        { // reference string fixed
            referenceStringFixed(maxFrameSize, maxPageSize, argv[3]);
            return 0;
        }
        else
        {
            cerr << "Invalid flag" << endl;
            return 0;
        }
    }

    return 0;
}