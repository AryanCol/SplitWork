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

    vector<int> subj = {10, 8, 2, 3};
    vector<pair<pair<int,int>,vector<int>>> final;
    for (int r = 0; r < 7; ++r) {
        vector<int> user(4);
        for (int& i : user) {
            i = rand() % 11;
        }

        vector<int> diff(4);
        transform(subj.begin(), subj.end(), user.begin(), diff.begin(), minus<int>());
        int diffSum = 0;
        for(auto itr:diff){diffSum += (itr);} 

        int dotProduct = inner_product(subj.begin(), subj.end(), user.begin(), 0);
        final.push_back({{dotProduct,diffSum},user});
        cout << diffSum << endl;
        cout << "Score: (" << dotProduct << ") User: ";
        for (int i : user) {
            cout << i << " ";
        }
        cout << endl;
    }
    sort(final.begin(),final.end(),[](auto& a, auto& b) { 
        return a.first.first > b.first.first; 
    });
    sort(final.begin(),final.begin()+4,[](auto& a, auto& b) { 
        return abs(a.first.second) < abs(b.first.second); 
    });
    for(auto itr: final){
        cout<<itr.first.first<<" ";
        cout<<itr.first.second<<" ";
        for (int i : itr.second) {
            cout<< i << " ";
        }
        cout<<endl;
    }
    return 0;
}