#include <vector>
#include <iostream>
#include <cmath>

#define M_PI 3.14159265358979323846
#define V std::vector
#define earthRadius 6371

struct ReturnPath {
    float length;
    V<int> path;
    // constructor for ReturnPath struct
    ReturnPath(float length_, V<int> path_) {
        length = length_;
        path   = path_;
    }
};

struct Point {
    float lat, lon;
    std::string name;
    // constructor for Point struct
    Point(float lat_, float lon_, std::string name_) {
        lat  = lat_;
        lon  = lon_;
        name = name_;
    }
};

class TSP {
    private:
        V<ReturnPath> type;
        V<V<ReturnPath>> state;
        float degToRad(float x);
        float radToDeg(float x);
        float euclideanDistance(Point p1, Point p2);
        V<V<float>> calculateEuclidean(V<Point> data);
        ReturnPath tsp(const V<V<float>>& distances, int position, int visited, V<V<ReturnPath>>& state);
    public:
        TSP() {}
        int print(ReturnPath rtn);
        ReturnPath solveTSP(V<Point> points);
};