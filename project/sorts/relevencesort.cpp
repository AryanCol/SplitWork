#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int n = 7;
    int m = 3;
    int LR = 0.6;
    float workload = 5.5;
    int WLspacialized = (1-(LR))*workload/m;
     

    vector<int> subj = {10, 8, 2, 3};
    vector<pair<pair<int,int>,vector<int>>> final;
    for (int r = 0; r < n; ++r) {
        vector<int> user(4);
        for (int& i : user) {
            i = rand() % 11;
        }
    }
    return 0;
}