#include "../include/master.h"
using namespace std;

/*
Global variables indices, w, d, device, STDout and STDerr initialized in file include/globals.h
*/

int main()
{
    FAST_IO
    Time t(__func__);

    // int m = indices(device), n = indices(device), C = indices(device);
    int m = 1000, n = 1000, C = 1000;
    vector<vector<float>> D(m, vector<float>(n)), W(C, vector<float>(n));
    // vector<vector<float>> W{{0.0025, 0.3, 0.45, 0.75}, {0.95, 0.35, 0.25, 0.15}}, D{{0, 0, 1, 1}, {1, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 1}}; // Test Data And Weights.
    SOM<float> O(D, W);

#pragma omp parallel for num_threads(8)
    for (int i = 0; i < D.size(); i++)
        ranges::generate(D[i], [&]
                         { return d(device); });
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < W.size(); i++)
        ranges::generate(W[i], [&]
                         { return w(device); });

    STDout.emplace_back(format("Datapoints=\n{: .3f}\n\nWeights before transform=\n{: .3f}\n\n", D, W));
    O.fit_transform(1000);
    STDout.emplace_back(format("Weights after transform=\n{: .3f}\n", W));
}