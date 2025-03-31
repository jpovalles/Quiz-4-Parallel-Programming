#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <omp.h>
using namespace std;


bool parallelBinarySearch(vector<int>& arr, int target, int numThreads) {
    bool found = false;
    int n = arr.size();
    
    // Create a vector to store the ranges for each processor
    vector<pair<int, int>> ranges(numThreads);
    
    int segmentSize = n / numThreads;
    for (int i = 0; i < numThreads; i++) {
        int start = i * segmentSize;
        int end = (i == numThreads - 1) ? n - 1 : ((i + 1) * segmentSize) - 1;
        ranges[i] = {start, end};
    }
    
    while (!ranges.empty() && !found) {
        vector<pair<int, int>> nextRanges;
        
        #pragma omp parallel num_threads(numThreads)
        {
            int tid = omp_get_thread_num();
            
            // solo se procesa si el hilo tiene un rango asignado
            if (tid < ranges.size()) {
                int start = ranges[tid].first;
                int end = ranges[tid].second;

                //cout << "from " << start << " to " << end << endl;
                
                if (start <= end) {
                    if (arr[start] == target || arr[end] == target) {
                        #pragma omp critical
                        {
                            found = true;
                        }
                    }
                    
                    else if (arr[start] < target && target < arr[end]) {
                        int mid = start + (end - start) / 2;
                        #pragma omp critical
                        {
                            nextRanges.push_back({start + 1, mid});
                            nextRanges.push_back({mid + 1, end - 1});
                        }
                    }
                }
            }
        }
        
        ranges = nextRanges;
        numThreads = min(numThreads, (int)ranges.size());
    }
    
    return found;
}


vector<int> generateList(int size, int maxval){
    vector<int> list(size);
    for (int i = 0; i < size; i++) {
        list[i] = rand() % (maxval + 1);
    }

    sort(list.begin(), list.end());
    return list;
}

vector<int> generateListEven(int size){
    vector<int> list(size);
    for (int i = 0; i < size; i++) {
        list[i] = i*2;
    }

    return list;
}


int main(int argc, char *argv[]){
    srand(time(nullptr));
    int size = atoi(argv[1]);
    int target = atoi(argv[2]);

//    vector<int> num = generateList(size, size*10);
    vector<int> num = generateListEven(size);
    
    bool ans = parallelBinarySearch(num, target, 4);

    for(int i = 0; i < size; i++)
        cout << num[i] << " ";
    cout << endl;

    if(ans) cout << target << " está en el arreglo" << endl;
    else cout << target << " no está en el arreglo" << endl; 
    return 0;
}