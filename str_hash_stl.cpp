#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin>> s;

    // pre-compute , hashmap making
    map<char, int>mpp;
    for(int i= 0; i<s.length(); i++){
        mpp[s[i]]++;
    }
    int q;
    cin>> q;
    while(q--){
        char c;
        cin>> c;
        // fetch from hashmap
        cout<< mpp[c] << " ";
    }
    return 0;
}