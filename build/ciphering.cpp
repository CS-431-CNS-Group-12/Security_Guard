#include <bits/stdc++.h>
using namespace std;

#define public_key  3
#define private_key 12355
#define mod         18841

string key_hashing(string s){
    return sha256(s);
}

long long int encrypt(double message)
{
    int e = public_key;
    long long int encrpyted_text = 1;
    while (e--) {
        encrpyted_text *= message;
        encrpyted_text %= mod;
    }
    return encrpyted_text;
}

long long int decrypt(int encrpyted_text)
{
    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrpyted_text;
        decrypted %= mod;
    }
    return decrypted;
}
string str_encription(string message)
{
    string ans = "";
    for (auto& letter : message){
        long long int temp = encrypt((int)letter);
        ans += to_string(temp);
        ans += '-';
    }

    return ans;
}
string str_decription(string encoded)
{
    string s;
    string temp = "";
    for (auto& num : encoded){

        if(num == '-'){
            long long int val = stoi(temp);
            s += decrypt(val);
            temp = " ";
        }else{
            temp += num;
        }
    }
        
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
                ans[4]=tokens[i+1];
                i++;
            }
            else{
                ans[2]=token;
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
                ans[4]=tokens[i+1];
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
                ans[2]=token;
            }
        }
    }
    return ans;
}
