#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "ciphering.cpp"
//#include <winsock2.h>
using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024
#define Secret_key 1234

// map<string, string> hash_map;

void createCSV(string &filename) {

    // Create and open a CSV file
    ofstream file(filename);
    // Check if the file was created successfully
    if (!file) {
        cerr << "Could not create file!" << endl;
        return;
    }
    // Close the file
    file.close();
}

void store_csv(vector<string> &info, string &filename){
    ofstream file(filename, std::ios::app);
    for(auto i : info){
        file << i << ",";
    }
    file << endl;
}

string q_process(vector<string> &info){
    return "working";
}

void Server(){

    map<string,string> hash_map;
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(address);

    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        return ;
    }

    // Server address setup
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return ;
    }

    // Listen for incoming connections
    if (listen(server_fd, SOMAXCONN) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return ;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        // Accept a connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len)) < 0)
        {
            perror("Accept failed");
            continue;
        }

        // Handle the connection in a separate process
        if (fork() == 0)
        {
            close(server_fd); // Child process doesn't need the listener

            // Receive and send data
            while (1)
            {
                int n = read(new_socket, buffer, BUFFER_SIZE - 1);
                if (n <= 0)
                {
                    break;
                }
                buffer[n] = '\0';
                printf("Received: %s\n", buffer);
                string response;

                if(strlen(buffer)==100){
                    if(hash_map.find(buffer)==hash_map.end()){
                        response ="NA";
                    }else{
                        response =str_encription(hash_map[buffer]);
                    }
                }else{
                    string decrypt_str =str_decription(string(buffer));
                    vector<string> info =str_break(decrypt_str);
                    string info_type, info_key, file_path;
                    info_type =info[0];
                    info_type =info[1];
                    file_path =info[2];
                    if(info_type =="logappend"){
                        if(hash_map.find(info_key)==hash_map.end()){
                            createCSV(file_path);
                            hash_map[info_key] =file_path;
                        }
                        store_csv(info,file_path);
                        response ="Successfully executed";
                    }
                    if(info_type =="logread"){
                        if(hash_map.find(info_key)==hash_map.end()){
                            response ="Invalid Key";
                        }else{
                            response =q_process(info);
                        }
                    }
                }
                response =str_encription(response);
                send(new_socket, response.c_str(), response.size(), 0);
                // Send "Pong!" back to the client
                
            }

            // Close the connection
            close(new_socket);
            return ;
        }
        else
        {
            close(new_socket); // Parent process doesn't need this socket
        }
    }

    close(server_fd);
}

int main()
{
    Server();
    return 0;
}