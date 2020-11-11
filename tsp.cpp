#include <vector>
#include <iostream>
#include <cmath>

#define V std::vector

struct ReturnPath {
    int length;
    V<int> path;
    // constructor for ReturnPath struct
    ReturnPath(int length_, V<int> path_) {
        length = length_;
        path = path_;
    }
};

struct Point {
    double x, y;
    // constructor for Point struct
    Point(double x_, double y_) {
        x = x_;
        y = y_;
    }
};

double euclideanDistance(Point p1, Point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

int printV(V<V<ReturnPath>> A) {
    std::cout << "\n";
    for (auto r : A) {
        std::cout << "{ ";
        for (auto c : r) {
            std::cout << "{ ";
            for (auto z : c.path)
                std::cout << z << " ";
            if (c.length == INT_MAX)
                std::cout << "}max ";
            else
                std::cout << "}" << c.length << " ";
        }
        std::cout << "}\n";
    }
}

int print(ReturnPath rtn) {
    std::cout << "shortest distance for { ";
    for (auto r : rtn.path) {
            std::cout << r << " ";
    }
    std::cout << "} is " << rtn.length << "\n";
}

ReturnPath tsp(const V<V<int>>& distances, int position, int visited, V<V<ReturnPath>>& state) {
    // if reached the end point then return the distance to the first
    if (visited == ((1 << distances.size()) - 1))
        return ReturnPath(distances[position][0], V<int>(1,distances[position][0]));
    // if it has already been calculated, then use that
    if (state[position][visited].length != INT_MAX)
        return state[position][visited];
    for (int i = 0; i < distances.size(); ++i) {
        if(i == position || (visited & (1 << i)))
            continue;
        // calculate next route
        ReturnPath r = tsp(distances, i, visited | (1 << i), state);
        // if the path is shorter then update
        if (distances[position][i] + r.length < state[position][visited].length) {
            state[position][visited].length = distances[position][i] + r.length;
            if (!state[position][visited].path.empty())
                state[position][visited].path.clear();
            state[position][visited].path.push_back(distances[position][i]);
            for (int j = 0; j < r.path.size(); ++j)
                state[position][visited].path.push_back(r.path[j]);
        }
    }
    return state[position][visited];
}

int main() {
    V<V<int>> distances = { { 0, 10, 15, 20 },
                            { 10, 0, 35, 25 },
                            { 15, 35, 0, 30 },
                            { 20, 25, 30, 0 } };

    V<V<int>> distances2 = { { 0, 20, 42, 35 },
                             { 20, 0, 30, 34 },
                             { 42, 30, 0, 12 },
                             { 35, 34, 12, 0 }
                            };

    V<ReturnPath> type = V<ReturnPath>((1 << distances.size()) - 1, ReturnPath(INT_MAX, V<int>()));
    V<V<ReturnPath>> state(distances.size(), type);

    ReturnPath r = tsp(distances, 0, 1, state);

    print(r);

    // std::cout << "euclidean:" << euclideanDistance(Point(0, 0), Point(12, 16));

    return 0;
}