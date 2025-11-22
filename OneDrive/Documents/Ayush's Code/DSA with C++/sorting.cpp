#include<bits/stdc++.h>
using namespace std;

// selection sort
void selection(int n, int arr[]){
    for(int i = 0; i<=n-2; i++){
        int mini = i;
        for(int j = i; j<=n-1; j++){
            if(arr[j] < arr[mini]){
                mini = j;
            } 
        }
        // swap here
        int temp = arr[mini];
        arr[mini] = arr[i];
        arr[i] = temp;
    }
}


// bubble sort
void bubble(int n , int arr[]){
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<=i-1; j++){
            if(arr[j]> arr[j+1]){
                int temp = arr[j+1];
                arr[j+1]= arr[j];
                arr[j] = temp;
            }
        }
    }
}


// insertion sort
void insertion(int n , int arr[]){
    for(int i = 0; i<=n-1; i++){
        int k = i;
        while(k > 0 && arr[k] <  arr[k-1]){
            int temp = arr[k-1];
            arr[k-1] = arr[k];
            arr[k] = temp;

            k--;
        }
    }
}


// merge sort
void merge(vector<int>& arr, int low,int mid,  int high){
    vector<int> temp;
    int left = low;
    // int mid = (low + high)/2;
    int right = mid+1;

    while(left <=mid && right<=high){
        if(arr[left] <= arr[right]){
            temp.emplace_back(arr[left]);
            left ++;
        }
        else {
            temp.emplace_back(arr[right]);
            right++ ;

        }
    }

    while(left<= mid){
        temp.emplace_back(arr[left]);
        left++ ;

    }
    while(right<= high){
        temp.emplace_back(arr[right]);
        right++ ;
    }

    for(int i = low; i<= high; i++){
        arr[i] = temp[i-low];
    }
}

void merge_sort(vector<int>& arr, int low, int high){
    if (low >= high) return;
    int mid = (low + high) /2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid+1, high);
    merge(arr, low, mid, high);
}


//quick sort
int partiton_index(vector<int>& arr, int low, int high ){
    int pivot = arr[low];
    int i = low;
    int j = high;

    while(i<j){
        while(arr[i] <= pivot && i <= high - 1){
            i++;
        }
        while (arr[j] > pivot && j >= low + 1){
            j--;
        }

        if(i< j){
            swap(arr[i], arr[j]);    
        }
    }
    
    swap(arr[low], arr[j]);
    return j;
        
}

void quick_sort(vector<int>& arr, int low,int high){
    if(low< high){
        int PI = partiton_index(arr, low, high);
        quick_sort(arr, low, PI-1);
        quick_sort(arr, PI + 1, high);
    }
}


int main(){
    
    int n ;
    cin>> n;
    vector<int>arr(n);
    // int low = 0;
    // int high = n-1;


    for(int i = 0; i< n; i++){
        cin>> arr[i];
    }
    quick_sort(arr, 0, n-1);
    for(int i = 0; i < n ; i++){
        cout<< arr[i] << " ";
    }
    
    return 0;
}