#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// Define a structure for a line segment
struct LineSegment {
    int xStart, yStart, xEnd, yEnd;
};

// Calculate the number of cells affected by a line segment
int calculateCells(LineSegment line, pair<int, int> intersectionPoint, bool splitAtIntersection) {
    if (line.xStart == line.xEnd) { // Vertical line
        if (splitAtIntersection) {
            return min(abs(intersectionPoint.second - line.yStart), abs(intersectionPoint.second - line.yEnd)) + 1;
        } else {
            return abs(line.yStart - line.yEnd) + 1;
        }
    } else { // Horizontal line
        if (splitAtIntersection) {
            return min(abs(intersectionPoint.first - line.xStart), abs(intersectionPoint.first - line.xEnd)) + 1;
        } else {
            return abs(line.xStart - line.xEnd) + 1;
        }
    }
}

// Check if two line segments intersect
bool checkIntersection(LineSegment line1, LineSegment line2, pair<int, int>& intersectionPoint) {
    if (line1.xStart == line1.xEnd && line2.yStart == line2.yEnd) { // Vertical line intersects horizontal line
        if (line2.xStart <= line1.xStart && line1.xStart <= line2.xEnd &&
            line1.yStart <= line2.yStart && line2.yStart <= line1.yEnd) {
            intersectionPoint = {line1.xStart, line2.yStart};
            return true;
        }
    }
    if (line1.yStart == line1.yEnd && line2.xStart == line2.xEnd) { // Horizontal line intersects vertical line
        if (line1.xStart <= line2.xStart && line2.xStart <= line1.xEnd &&
            line2.yStart <= line1.yStart && line1.yStart <= line2.yEnd) {
            intersectionPoint = {line2.xStart, line1.yStart};
            return true;
        }
    }
    return false;
}

int main() {
    int lineCount, requiredIntersections;
    cin >> lineCount;
    vector<LineSegment> segments(lineCount);

    // Input line segments
    for (int i = 0; i < lineCount; ++i) {
        cin >> segments[i].xStart >> segments[i].yStart >> segments[i].xEnd >> segments[i].yEnd;
        // Ensure the line starts at the smaller coordinate
        if (segments[i].xStart > segments[i].xEnd || 
           (segments[i].xStart == segments[i].xEnd && segments[i].yStart > segments[i].yEnd)) {
            swap(segments[i].xStart, segments[i].xEnd);
            swap(segments[i].yStart, segments[i].yEnd);
        }
    }
    cin >> requiredIntersections;

    // Map to store intersection points and the lines that intersect there
    map<pair<int, int>, vector<LineSegment>> intersectionMap;
    for (int i = 0; i < lineCount; ++i) {
        for (int j = i + 1; j < lineCount; ++j) {
            pair<int, int> intersectionPoint;
            if (checkIntersection(segments[i], segments[j], intersectionPoint)) {
                intersectionMap[intersectionPoint].push_back(segments[i]);
                intersectionMap[intersectionPoint].push_back(segments[j]);
            }
        }
    }

    int totalIntensity = 0;
    for (auto& entry : intersectionMap) {
        if (entry.second.size() / 2 == requiredIntersections) {
            vector<int> cellCounts;
            for (auto& segment : entry.second) {
                cellCounts.push_back(calculateCells(segment, entry.first, true));
            }
            totalIntensity += *min_element(cellCounts.begin(), cellCounts.end());
        }
    }

    cout << totalIntensity << endl;
    return 0;
}
