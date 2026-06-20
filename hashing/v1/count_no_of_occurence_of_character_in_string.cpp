#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cout <<"enter string"<< endl;
    cin >> s;


    int hash[26] = {0}; //26 for alphabets and 256 for all characters
    for(int i=0;i<s.size();i++){
        hash[s[i]-'a'] +=1; //'character' - 'a' gives the index of the character in the hash array
    }
    char c;
    cout <<"enter character to count"<<endl;
    cin >> c;

    int count = hash[c-'a'];

    cout << "number of occurences of " << c << " is " << count;
    return 0;
}