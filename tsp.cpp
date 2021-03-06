#include "tsp.h"

float TSP::degToRad(float x) {
    return x * M_PI / 180;
};
float TSP::radToDeg(float x) {
    return x * 180 / M_PI;
};

float TSP::haversineDistance(Point p1, Point p2) {
    float lat = sin(degToRad(p1.lat - p2.lat)/2);
    float lon = sin(degToRad(p1.lon - p2.lon)/2);
    // calculating using 'Haversine' formula
    return 2.0 * earthRadius * asin(sqrt(lat*lat + 
        cos(degToRad(p1.lat)) * cos(degToRad(p2.lat)) * lon*lon));
}

V<V<float>> TSP::calculateHaversine(V<Point> data) {
    int size = data.size();
    V<V<float>> rtn(size, V<float>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = i+1; j < size; ++j) {
            rtn[i][j] = haversineDistance(data[i], data[j]);
            rtn[j][i] = rtn[i][j];
        }
    }
    return rtn;
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

void TSP::print(ReturnPath rtn) {
    std::cout << "The shortest distance for point indexes { ";
    for (auto r : rtn.path) {
            std::cout << r << " ";
    }
    std::cout << "} is " << rtn.length << " km!\n";
}

ReturnPath TSP::solveTSP(V<Point> points) {
    V<V<float>> distances = calculateHaversine(points);
    type = V<ReturnPath>((1 << points.size()) - 1, ReturnPath(__FLT_MAX__, V<int>()));
    state = V<V<ReturnPath>>(points.size(), type);
    ReturnPath rtn = tsp(distances, 0, 1, state);
    rtn.path.push_back(rtn.path[0]);
    return rtn;
}