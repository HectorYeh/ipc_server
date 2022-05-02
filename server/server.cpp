#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define SHMSZ     1024

void error(const char *msg) {

    perror(msg);
    exit(1);
}

bool number_chk(string num_arr) {

    for(int i=0; i<num_arr.size(); i++) {
        if(num_arr[i] == ' ') continue;
        else if( isdigit(num_arr[i]) == 0 ) return false;
    }

    return true;

}

int main() {

    // Socket init
    int sockfd, newsockfd, portno = 9999;
    // create a TCP/IP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
       error("ERROR opening socket");

    struct sockaddr_in serv_addr;
    // clear address structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    /* setup the host_addr structure for use in bind call */
    // server byte order
    serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // port number to bind to
    serv_addr.sin_port = htons(portno);

    // This bind() call will bind  the socket to the current IP address on port
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    char socket_buf[SHMSZ];

    listen(sockfd,2);

//----------------------------------------------------

    // Named pipe init
    int client_to_server;
    char *myfifo = "/tmp/client_to_server_fifo";

    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";

    char pipe_buf[SHMSZ];

    // /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);

    // /* open, read, and display the message from the FIFO */
    // client_to_server = open(myfifo, O_RDONLY);
    // server_to_client = open(myfifo2, O_WRONLY);

//----------------------------------------------------

    // Shared memory init
    int shmid;
    char* shm;

    key_t key = ftok("shmfile",65);

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char*) - 1) {
        perror("shmat");
        exit(1);
    }

//----------------------------------------------------

    bool client1_chk = false;
    bool client2_chk = false;
    bool client3_chk = false;

    string num_arr;
    string shm_str, pipe_str;

    while(!client1_chk || !client2_chk || !client3_chk) {

        //wait socket client
        if(client2_chk && client3_chk) {
            if(newsockfd = accept(sockfd, 0, 0)) {
                if( read(newsockfd, socket_buf, 1023) > 0 ) {
                    cout << socket_buf << endl;
                    client1_chk = true;
                }
            }
        }

        //wait pipe client
        if(!client2_chk) {
            client_to_server = open(myfifo, O_RDONLY);
            if( read(client_to_server, pipe_buf, 1023) > 0) {
                cout << pipe_buf << endl;
                client2_chk = true;
            }
            close(client_to_server);
        }

        //wait shared memory client
        if(!client3_chk) {
            shm_str = string(shm);
            if(shm_str.find("ready") != string::npos) {
                cout << shm_str << endl;
                client3_chk = true;
            }
        }

        sleep(1);
    }

    //Server ready
    cout << "Server is ready." << endl;
    cout << "Please input digit array: ";
    getline(cin, num_arr);

    // num_arr = "1 5 5 10 15 2 3 1 5";

    if( number_chk(num_arr) ) {

        //write to socket
        write(newsockfd, num_arr.c_str(), num_arr.size());

        //write to pipe
        server_to_client = open(myfifo2, O_WRONLY);
        write(server_to_client, num_arr.c_str(), num_arr.size());
        close(server_to_client);

        //write to shared memory
        strcpy(shm, num_arr.c_str());
    }

    else cout << '{' << num_arr << "} include invalid values." << endl;

    unlink(myfifo);
    unlink(myfifo2);

    return 0;
}