#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> generateList(int size, int maxval){
    vector<int> list(size);
    for (int i = 0; i < size; i++) {
        list[i] = rand() % (maxval + 1);
    }

    sort(list.begin(), list.end());
    return list;
}

bool binarySearch(vector<int> list, int target){
    int lo = 0;
    int hi = list.size() - 1;
    while(lo <= hi){
        //cout << lo << "\t" << hi << endl;
        int mid = (lo + hi) / 2;
        if(list[mid] == target){
            return true;
        }else if(list[mid] > target){
            hi = mid-1;
        }else{
            lo = mid+1;
        }
    }
    return false;
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

    //vector<int> num = generateList(size, size*10);
    vector<int> num = generateListEven(size);
    
    bool ans = binarySearch(num, target);

    for(int i = 0; i < size; i++)
        cout << num[i] << " ";
    cout << endl;

    if(ans) cout << target << " está en el arreglo" << endl;
    else cout << target << " no está en el arreglo" << endl; 
    return 0;
}