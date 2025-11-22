#include<bits/stdc++.h>

using namespace std;

int main(){

    string s;
    int temp;
    cin >> s;
    s.erase(remove_if(s.begin(), s.end(), [](char c){
            return !isalnum(static_cast<unsigned char>(c));
    }),
    s.end());
    for(auto i = 0; i <= s.length(); i++){
        for(auto j = 0; j<= s.length(); j++){
            s[temp]= s[i];
            s[i] = s[j];
            s[j] = s[temp];
        }
    }

    cout<< s;
    
    return 0;
}