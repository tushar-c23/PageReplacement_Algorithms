#include <bits/stdc++.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"
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
                int mostRecentlyUsed = INT_MAX;
                int val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] > mostRecentlyUsed)
                    {
                        mostRecentlyUsed = indexes[*it];
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

void plotGraph(vector<double> x, vector<double> y, int trials, int maxFrameSize, int maxPageSize)
{
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    
    wstring titleText = L"Most Recently Used-"+to_wstring(trials)+L"-"+to_wstring(maxFrameSize)+L"-"+to_wstring(maxPageSize);
    string titleTextString = "Most Recently Used-"+to_string(trials)+"-"+to_string(maxFrameSize)+"-"+to_string(maxPageSize);
    const wchar_t *titleTextConverted = titleText.c_str();

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = &x;
    series->ys = &y;
    series->linearInterpolation = true;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1080;
    settings->height = 720;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(titleTextConverted);
    settings->xLabel = toVector(L"Frame Size");
    settings->yLabel = toVector(L"Page Faults");
    settings->scatterPlotSeries->push_back(series);

    DrawScatterPlotFromSettings(imageRef, settings);

    vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plots/"+titleTextString+".png");
    DeleteImage(imageRef->image);

    return;
}

int main(int argc, char *argv[])
{
    int trials = 30;
    int maxPageSize = 100;
    int maxFrameSize = 100;
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
    
    //Plotting
    vector<double> x;
    vector<double> y;

    for (auto it = pageFaultsToFrameSize.begin(); it != pageFaultsToFrameSize.end(); it++)
    {
        x.push_back(double(it->first));
        y.push_back(double(it->second));
    }

    plotGraph(x,y,trials,maxFrameSize,maxPageSize);
    return 0;
}