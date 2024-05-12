#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int main(){
    vector<int> subj = {10, 8, 2, 3};
    vector<pair<pair<int,int>,vector<int>>> final;
    for (int r = 0; r < 7; ++r) {
        vector<int> user(4);
        for (int& i : user) {
            i = rand() % 11;
        }
    }
    return 0;
}