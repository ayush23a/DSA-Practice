#include <bits/stdc++.h>
using namespace std;

bool isSorted(vector<int>& num){
    for(int i = 0; i<= num.size(); i++ )
    {
        if (num[i] <= num[i+1]) return true;
        else return false;
    }
}

int main(){
    
    int n ;
    cin>> n;
    vector<int>arr(n);

    for(int i = 0; i< n; i++){
        cin>> arr[i];
    }

    isSorted(arr);

    return 0;
}
