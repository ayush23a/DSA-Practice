#include<bits/stdc++.h>
using namespace std;

int main(){
    
    int x;
    cin>> x;
    int temp = x;
    int rev = 0;
    while (temp > 0){
    
        
        int ld = temp%10;
        rev = (rev * 10) + ld;

        temp = temp/10;
    
    }
    
    if (rev == x) {
        cout << "palindrome";
    }
    else cout<< "not palindrome";

    return 0;
}