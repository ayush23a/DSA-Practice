// this file will not be eecutd as it will only contain the various STL operations and not the main function to call them

#include<bits/stdc++.h>
using namespace std;
//pair
void ExplainPair(){
    pair<int, int> p = {1, 2};
    cout<< p.first << "" << p.second; // p.first = 1, p.second = 2

    pair<int, char> pt = {1, 'ayush'}; // multi-data in pair

    pair<int , pair<int , int>> p1 = {2, {1, 3}}; // nested pairs {pair inside pair}
    cout<< p1.second.first; // to print 1
    cout<< p1.second.second; // to print 3

}


void EXplainVector(){
    vector<int>v ;
    v.push_back(1); // appends 1 inside vector
    v.emplace_back(2); // appends 2 inside vector

    // pair inside vector 
    vector<pair<int , int >> v1;
    v1.push_back({1, 2}); // if push_back is used 
    v1.emplace_back(2,3); // if emplace_back is used 

    vector<int> demo(5, 100); // printts 100 -> 5 times
    vector<int> demo(5); // printts 0 -> 5 times

    // cloning a vector 
    vector<int> c(5, 10); // main vector
    vector<int> v2(c); // cloned c into v2

    // vector operation for element insertion
    vector<char> v = {'a', 'f', 'd'};
  
  	// Inserting 'z' at the back
  	v.push_back('z');
  
  	// Inserting 'c' at index 1
  	v.insert(v.begin() + 1, 'c');
}

void ExplainIterators(){
    vector<int> v;
    vector<int>::iterator i = v.begin(); // access the starting of vector 
    i++;
    cout<< *(i) << ""; //prints the element at 'i' position 


    //other iterators are:
    vector<int>::iterator i = v.end(); // end iterator
    vector<int>::iterator i = v.rend(); // reverse end
    vector<int>::iterator i = v.rbegin(); // reverse begin

    cout<< v.back() << " "; // refers to the last element of vector container

    
    // to print different vector 
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout<< *(it)<< " "; // prints all the elemnet inside the vector using address/ pointer reference
    }

    // alternative method 
    for(auto i = v.begin(); i != v.end(); i++){
        cout<< *(i) <<" "; // here auto is used to automatically assign the datatype as per the value present 
    }

    // method3
    for (auto i : v){
        cout<< i <<" "; 
    }

    // erase function

    // let the vector be {10, 20, 30, 40}
    v.erase(v.begin() +1 ); // delete the element 20 and new vector will become {10 , 30, 40}
    
    // to remove 20, 30 from vector 
    v.erase(v.begin()+ 1, v.begin()+ 3); // to erase a range of elements in vector 
    // v.begin() + 1 -> index of starting elemnt 
    // v.begin() + 3 -> index of element just after the targeting element (exclusive index)
    

    // insert function
    vector<int>v(2, 100); // {100, 100}
    v.insert(v.begin(), 300); // {300, 100, 100}
    v.insert(v.begin() +1, 2, 10 ); // {300, 100, 10, 10, 100} 

    //size of vector
    cout<< v.size(); 

    // swap 2 vectors
    v1.swap(v2); // v1 and v2 swaps each other

    // remove an element 
    // {10, 20, 30}
    v.pop_back();  // {10, 20}

    // clear the entire vector
    v.clear();
}


void ExplainList(){
    list<int> ls;

    ls.push_back(4); //{4}
    ls.emplace_back(10); //{4, 10}

    ls.push_front(5); // {5, 4, 10}
    ls.emplace_front(); // {4, 10}

    // rest func same as vectors
}

void explainDequeue(){
    deque<int>dq;
    
    //insertion
    dq.push_back(2); // {2}
    dq.emplace_back(4); // {2, 4}
    dq.push_front(3); //{3,2,4}
    dq.emplace_front(5); // {5,3,2,4}

    //deletion
    dq.pop_back(); // {5,3,2}
    dq.pop_front(); // {3,2}

    // rest same as vectors 
}







// int main(){
    


//     return 0;

// }