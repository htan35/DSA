#include<bits/stdc++.h>
using namespace std;        
int main(){
    int s;
    cout <<"enter size"<<endl;
    cin >> s;
    int arr[s];

    for(int i=0;i<s;i++){
        cin >> arr[i];
    }
    cout << endl;

    //precompute
    map<int, int> mpp;
    for(int i=0;i<s;i++){
        mpp[arr[i]] +=1;
    }

    //itereate in map
    for(auto it : mpp){
        cout << it.first << "-> " << it.second << endl;
    }

    
    int query;
    cout<<"enter query"<<endl;
    cin >> query;
    //fetching
    cout << mpp[query];
    return 0;
}