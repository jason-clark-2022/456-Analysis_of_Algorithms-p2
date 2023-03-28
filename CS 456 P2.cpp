// Jason Clark CS 456 P2

#include <iostream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;
void runTenIterations(int size, int maxWeight, int totalWeight);
vector<int> generateWeights(int size, int maxWeight);
int greedyApproximation(vector<int> weights, int totalWeight);
int subsetSum(vector<int> weights, int totalWeight);
int max(int i1, int i2);
void printlist(vector<int> v);

int main()
{
    int size = 100;
    int maxWeight = 600;
    int totalWeight = 1000;

    runTenIterations(size, maxWeight, totalWeight);
    
    return 0;
}

void printlist(vector<int> v)
{
    for(int i = 0; i< v.size(); i++)
    {
        cout << v[i] << " ";
        if(i>0 && i%20 == 0)
            cout << endl;
    }
}


void runTenIterations(int size, int maxWeight, int totalWeight)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;
    
    vector<int> weights;
    int greedyWeight;
    int subsetSumWeight;
    
    for(int i = 1; i < 11; i++)
    {
        cout << endl <<  "---Test " << i << "---" << endl;
        cout << "Target Weight:\t" << totalWeight << endl;
        weights = generateWeights(size, maxWeight);

        auto start = high_resolution_clock::now();
        greedyWeight = greedyApproximation(weights, totalWeight);
        auto stop = high_resolution_clock::now();
        auto greedyTime = duration_cast<microseconds>(stop - start);

        start = high_resolution_clock::now();
        subsetSumWeight = subsetSum(weights, totalWeight);
        stop = high_resolution_clock::now();
        auto subsetTime = duration_cast<microseconds>(stop - start);

        cout << "Greedy Weight:\t" << greedyWeight << endl << "Greedy Time:\t";
        cout << greedyTime.count() << endl;
        cout << "Subset Weight:\t" << subsetSumWeight << endl << "Subset Time:\t";
        cout << subsetTime.count() << endl << endl;
    }
}

vector<int> generateWeights(int size, int maxWeight)
{
    //srand(time(0)); // use for seeded randoms 
    vector<int> weights(size);
    for (int i = 0; i < size; i++)
    {
        weights[i] = (rand()% maxWeight) + 1;
    } 
    return weights;
}

int greedyApproximation(vector<int> weights, int totalWeight)
{
    int basketWeight;
    for(int i = 0; i < weights.size(); i++)
    {
        for(int j = i+1; j < weights.size(); j++)
        {
            if(weights[i] < weights[j])
            {
                int temp = weights[i];
                weights[i] = weights[j];
                weights[j] = temp;
            }
        }
    }
    
    for(int i = 0; i < weights.size(); i++)
    {
        int nextBasketWeight = basketWeight + weights[i];
        if(nextBasketWeight <= totalWeight)
        {
            basketWeight = nextBasketWeight;
        }
        else
        {
            i = weights.size();
        }
    }
    return basketWeight;
}

int subsetSum(vector<int> weights, int totalWeight)
{    
    vector<vector <int>> m(weights.size()+1, vector<int>(totalWeight+1));
    
    for(int i = 1; i <= weights.size(); i++)
    {
        
        for(int w = 0; w <= totalWeight; w++)
        {   
            if(w < weights[i-1])
                m[i][w] = m[i-1][w];
            else
            {
                m[i][w] = max(m[i-1][w], weights[i-1] + m[i-1] [w - weights[i-1]]);    
            }
                
        }
    }
    return m[weights.size()][totalWeight];
}

int max(int i1, int i2)
{
    if(i1 < i2)
        return i2;
    else
        return i1;
}