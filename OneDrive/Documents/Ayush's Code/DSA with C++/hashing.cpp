#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin>> s;

    int hash[26] = {0}; // for only small letters. for all the other string input type use hash[256] = {0};
    
    for(int i = 0; i<s.length(); i++){
        hash[s[i] - 'a'] += 1;
    }


    int q;
    cin>> q;
    while(q--){
        char c;
        cin>> c;

        cout<< hash[c - 'a']<< " ";
    }

    return 0;
}
