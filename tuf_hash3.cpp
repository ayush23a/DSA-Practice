#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    map<int, int> hash;

    for (int i = 0; i < n; i++) {
        hash[arr[i]]++;
    }

    if (hash.empty()) {
        cout << "No elements were entered." << endl;
        return 0;
    }

    int max_freq = 0;
    int most_frequent_element = 0;

    int min_freq = n + 1;
    int least_frequent_element = 0;

    for (auto const& pair : hash) {
        int current_number = pair.first;
        int current_freq = pair.second;

        if (current_freq > max_freq) {
            max_freq = current_freq;
            most_frequent_element = current_number;
        }
        
        if (current_freq < min_freq) {
            min_freq = current_freq;
            least_frequent_element = current_number;
        }
    }

    
    cout << "Most frequent element: " << most_frequent_element
         << " (appeared " << max_freq << " times)" << endl;

    cout << "Least frequent element: " << least_frequent_element
         << " (appeared " << min_freq << " times)" << endl;

    return 0;
}