#include "tsp.h"
#include <fstream>

float TSP::degToRad(float x) {
    return x * M_PI / 180;
};
float TSP::radToDeg(float x) {
    return x * 180 / M_PI;
};

float TSP::euclideanDistance(Point p1, Point p2) {
    float lat = sin(degToRad(p1.lat - p2.lat)/2);
    float lon = sin(degToRad(p1.lon - p2.lon)/2);
    // calculating using 'Haversine' formula
    return 2.0 * earthRadius * asin(sqrt(lat*lat + 
        cos(degToRad(p1.lat)) * cos(degToRad(p2.lat)) * lon*lon));
}

V<V<float>> TSP::calculateEuclidean(V<Point> data) {
    int size = data.size();
    V<V<float>> rtn(size, V<float>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = i+1; j < size; ++j) {
            rtn[i][j] = euclideanDistance(data[i], data[j]);
            rtn[j][i] = rtn[i][j];
        }
    }
    return rtn;
}

int TSP::printV(V<V<ReturnPath>> A) {
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

int TSP::print(ReturnPath rtn) {
    std::cout << "shortest distance for { ";
    for (auto r : rtn.path) {
            std::cout << r << " ";
    }
    std::cout << "} is " << rtn.length << "\n";
}

ReturnPath TSP::tsp(const V<V<float>>& distances, int position, int visited, V<V<ReturnPath>>& state) {
    // if reached the end point then return the distance to the first
    if (visited == ((1 << distances.size()) - 1))
        return ReturnPath(distances[position][0], V<int>(1, position)); // distances[position][0]));
    // if it has already been calculated, then use that
    if (state[position][visited].length != __FLT_MAX__)
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
            state[position][visited].path.push_back(position); //distances[position][i]);
            for (int j = 0; j < r.path.size(); ++j)
                state[position][visited].path.push_back(r.path[j]);
        }
    }
    return state[position][visited];
}

int printV1(V<V<float>> A) {
    std::cout << "\n";
    for (auto r : A) {
        std::cout << "{ ";
        for (auto c : r) {
            std::cout << c << " ";
        }
        std::cout << "}\n";
    }
}

int main() {
    TSP tsp;

    V<Point> points = { Point(-35.282001, 149.128998, "Canberra"),
                        Point(-33.865143, 151.209900, "Sydney"),
                        Point(-37.840935, 144.946457, "Melbourne"),
                        Point(-27.470125, 153.021072, "Brisbane"),
                        Point(-31.953512, 115.857048, "Perth"),
                        Point(-34.921230, 138.599503, "Adelaide"),
                        Point(-42.880554, 147.324997, "Hobart"),
                        Point(-12.462827, 130.841782, "Darwin"),
                       };

    V<V<float>> distances = tsp.calculateEuclidean(points);
    printV1(distances);

    V<V<float>> distances2 = { { 0, 20, 42, 35 },
                               { 20, 0, 30, 34 },
                               { 42, 30, 0, 12 },
                               { 35, 34, 12, 0 }
                             };

    V<ReturnPath> type = V<ReturnPath>((1 << distances.size()) - 1, ReturnPath(__FLT_MAX__, V<int>()));
    V<V<ReturnPath>> state(distances.size(), type);

    ReturnPath r = tsp.tsp(distances, 0, 1, state);
    r.path.push_back(r.path[0]);
    tsp.print(r);

    // Create an output filestream object
    std::ofstream output("output.csv");    
    // Send data to the stream
    output << "Latitude,Longitude,Name\n";
    for (int i = 0; i < r.path.size(); ++i) {
        output << points[r.path[i]].lat << "," << points[r.path[i]].lon 
            << "," << points[r.path[i]].name << "\n";
    }
    // Close the file
    output.close();

    return 0;
}