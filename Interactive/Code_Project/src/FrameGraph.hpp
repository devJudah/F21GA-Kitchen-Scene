/**
 * Store frametime / fps data to graph
*/

#pragma once

#include <deque>
#include <vector>


class FrameGraphData
{
    public:

        FrameGraphData();

        FrameGraphData(int numDataPoints);

        int getGraphDataSize();

        void AddData(float data);

        std::vector<float> GetDataArray();

        float getGraphDataN(int n);
    
    private:

        int numDataPoints = 1000; // How many logged items to keep

        std::deque<float> graphData;

        void initialize();
};