#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <winsock2.h>
#include <sys/time.h>
using namespace std;
#define PORT 8080
#define Secret_key 1234
#include "ciphering.cpp"
#include "input_validation.cpp"
// Get current time in milliseconds

long long current_time_in_ms()
{
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec * 1000LL) + (time_now.tv_usec / 1000);
}

bool build_connection(int &sockfd){

    struct sockaddr_in server_addr;

    // Create TCP socket
    if (sockfd < 0) {
        perror("Socket creation failed");
        return false;
    }

    // Server address setup
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return false;
    }
    return true;
}

string get_input(){

    string s;
    cin >> s;
    return s;
}

void print_output(string s){
    cout << s;
}

bool user_autentication(string info_key, string info_path, int &sockfd){

    char info[1000];
    string hash =key_hashing(info_key);

    send(sockfd, hash.c_str(), hash.size(), 0);
    printf("Message sent to server\n");

    int n = read(sockfd, info, strlen(info)- 1);
    string decript_str =str_decription(string(info));

    if (n < 0) {
        perror("autentication failed");
        close(sockfd);
        return false;
    }
    if(decript_str ==info_path || decript_str =="NA"){
        return true;
    }
    cout << "Invalid Key" << endl;
    return false;
}

void send_info(string &s, int &sockfd){

    string encript_str =str_encription(s);
    send(sockfd, encript_str.c_str(), encript_str.size(), 0);
    cout << "Message sent to server" << endl;
}

void Client(){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(build_connection(sockfd) ==false){
        return;
    }
    string info = get_input();
    if(input_validation(info) ==false){
        cout << "Please check the input Format" << endl;
        return;
    }
    
    string info_type,info_key,info_path;

    vector<string> info_break =str_break(info);
    info_type =info_break[0];
    info_key =info_break[1];
    info_path =info_break[2];

    long long start_time = current_time_in_ms();

    if(user_autentication(info_key, info_path, sockfd)==false){
        return;
    }
    send_info(info, sockfd);
    
    char recieved_info[1000];
    int n = read(sockfd, recieved_info, strlen(recieved_info)- 1);
    if (n < 0 || recieved_info =="failed") {
        perror("failed");
        close(sockfd);
        return;
    }
    if(info_type =="Logappend"){
        cout << "Successfully Executed" << endl;
    }
    if(info_type =="Logread"){
        string decript_str =str_decription(string(recieved_info));
        print_output(decript_str);
    }
    long long end_time = current_time_in_ms();

    // Calculate RTT
    long long rtt = end_time - start_time;
    cout << ("RTT: %lld ms\n", rtt) << endl;

    close(sockfd);

}

int main() {

    Client();
    return 0;
}