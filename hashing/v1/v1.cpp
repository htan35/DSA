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

int hash[100001] = {0}; //max size is 10^5

for(int i=0;i<s;i++){
    hash[arr[i]] +=1;
}

int query;
cout<<"enter query"<<endl;
cin >> query;
    
cout << hash[query];


return 0;
}