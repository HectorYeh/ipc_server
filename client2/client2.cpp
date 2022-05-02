#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void median_fun(string num_arr) {

    stringstream ss(num_arr);
    string str;
    vector<int> num_vec;

    while( ss>>str ) {
        num_vec.push_back(stoi(str));
    }
    
    sort(num_vec.begin(), num_vec.end());

    int n = num_vec.size();

//-------------------------------------------------
    //Median calculate
    vector<int> median_vec;
    if( n%2 ) 
        median_vec.push_back(num_vec[n/2]);
    else {
        median_vec.push_back(num_vec[n/2-1]);
        median_vec.push_back(num_vec[n/2]);
    }

//-------------------------------------------------

    //Output
    cout << "Median is ";
    for(int i=0; i<median_vec.size(); i++)
        cout << median_vec[i] << ' ';
    cout << endl;

}

int main() {

    int client_to_server;
    char *myfifo = "/tmp/client_to_server_fifo";

    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";

    char str[BUFSIZ];
    string ready_msg = "Client 2 is ready.";
    strcpy(str, ready_msg.c_str());

    /* write str to the FIFO */
    client_to_server = open(myfifo, O_WRONLY);

    write(client_to_server, ready_msg.c_str(), ready_msg.size());

    close(client_to_server);

    while(strcmp(str, ready_msg.c_str()) == 0) {

        server_to_client = open(myfifo2, O_RDONLY);
        read(server_to_client, str, 1023);

        perror("Read:");

        sleep(1);
    }

    cout << "Got array: " << str << " from server" << endl;

    close(server_to_client);

    median_fun(string(str));

    return 0;
}