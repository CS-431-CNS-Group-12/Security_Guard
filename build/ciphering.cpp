#include <bits/stdc++.h>
using namespace std;

string key_hashing(string s){
    return s;
}

string str_encription(string s){
    return s;
}

string str_decription(string s){
    return s;
}

vector<string> str_break(string &s){
    vector<string> ans(8,"");
    vector<string> tokens;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        tokens.push_back(word);
    }
    ans[0] = tokens[0];
    if(tokens[0]=="logread"){
        for(int i=1;i<tokens.size();i++){
            string token = tokens[i];
            if(token == "-K"){
                ans[1]=tokens[i+1];
                i++;
            }
            else if(token=="-S"||token=="-R"||token=="-T"){
                ans[5]=token.substr(1,1);
            }
            else if(token=="-G"){
                ans[3]=tokens[i+1];
                i++;
            }
            else if(token=="-E"){
                ans[2]=tokens[i+1];
                i++;
            }
            else{
                ans[4]=token;
            }
        }
    }
    else{
        for(int i=1;i<tokens.size();i++){
            string token=tokens[i];
            if(token=="-T"){
                ans[7]=tokens[i+1];
                i++;
            }
            else if(token=="-K"){
                ans[1]=tokens[i+1];
                i++;
            }
            else if(token=="-E"){
                ans[2]=tokens[i+1];
                i++;
            }
            else if(token=="-G"){
                ans[3]=tokens[i+1];
                i++;
            }
            else if(token=="-A"||token=="L"){
                ans[5]=token.substr(1,1);
            }
            else if(token=="-R"){
                ans[6]=tokens[i+1];
                i++;
            }
            else{
                ans[4]=token;
            }
        }
    }
    return ans;
}
