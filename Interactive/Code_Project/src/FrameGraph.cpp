#include "FrameGraph.hpp"


/**
 * Public
*/
FrameGraphData::FrameGraphData() {
    initialize();
}

FrameGraphData::FrameGraphData(int numDataPoints)
{
    this->numDataPoints = numDataPoints;
    initialize();
}

int FrameGraphData::getGraphDataSize()
{
    return graphData.size();
    //return numDataPoints; // should equal graphData.size() unless something went wrong
}

void FrameGraphData::AddData(float data)
{   
    // Add new data to graph, removing oldest point
    if(graphData.size() > numDataPoints) {
        graphData.pop_front();
    }
    graphData.push_back(data);
}

std::vector<float> FrameGraphData::GetDataArray()
{
    // Convert into a float
    std::vector<float> dataPoints;

    for(float &d : graphData) {
        dataPoints.push_back(d);
    }

    return dataPoints;
}


float FrameGraphData::getGraphDataN(int n)
{
    return graphData[n];
}


/**
 * Private
*/
void FrameGraphData::initialize()
{
    // Stick some 0s in
    for(int i=0; i < numDataPoints; i++) {
        graphData.push_back(0);
    }
}