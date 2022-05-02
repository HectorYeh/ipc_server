#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void error(const char *msg) {

    perror(msg);
    exit(0);
}

// void statistic_fun(string num_arr) {

//     stringstream ss(num_arr);
//     string str;
//     vector<int> num_vec;

//     while( ss>>str ) {
//         // cout << str << endl;
//         num_vec.push_back(stoi(str));
//     }
//     sort(num_vec.begin(), num_vec.end());

//     int n = num_vec.size();
// //-------------------------------------------------
//     //Mean calculate
//     double mean = accumulate(num_vec.begin(), num_vec.end(), 0.0) / num_vec.size();
// //-------------------------------------------------
//     //Median calculate
//     vector<int> median_vec;
//     if( n%2 ) 
//         median_vec.push_back(num_vec[n/2]);
//     else {
//         median_vec.push_back(num_vec[n/2-1]);
//         median_vec.push_back(num_vec[n/2]);
//     }
// //-------------------------------------------------
//     //Mode calculate
//     vector<bool> visited(n, false);
//     vector<int> mode_vals;
//     int max_freq = 0;

//     for(int i=0; i<n; i++) {
//         if(visited[i] == true)
//             continue;

//         int cnt = 1;
//         for(int j=i+1; j<n; j++) {
//             if(num_vec[i] == num_vec[j]) {
//                 visited[j] = true;
//                 cnt++;
//             }
//         }
//         if(max_freq < cnt) {
//             max_freq = cnt;
//             mode_vals.clear();
//             mode_vals.push_back(num_vec[i]);
//         }
//         else if (max_freq == cnt)
//             mode_vals.push_back(num_vec[i]);
//     }

// //-------------------------------------------------

//     //Output
//     cout << "Mean is " << mean << endl;

//     cout << "Median is ";
//     for(int i=0; i<median_vec.size(); i++)
//         cout << median_vec[i] << ' ';
//     cout << endl;

//     cout << "Mode is ";
//     for(int i=0; i<mode_vals.size(); i++)
//         cout << mode_vals[i] << ' ';
//     cout << endl;

// }

void mean_fun(string num_arr) {

    stringstream ss(num_arr);
    string str;
    vector<int> num_vec;

    while( ss>>str ) {
        // cout << str << endl;
        num_vec.push_back(stoi(str));
    }
    sort(num_vec.begin(), num_vec.end());

    int n = num_vec.size();
//-------------------------------------------------
    //Mean calculate
    double mean = accumulate(num_vec.begin(), num_vec.end(), 0.0) / num_vec.size();

//-------------------------------------------------

    //Output
    cout << "Mean is " << mean << endl;

}

int main(int argc, char *argv[]) {

    int sockfd, portno = 9999;
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == 0) {

        char buf[1024];
        string str = "Client 1 is ready.";

        write(sockfd, str.c_str(), str.size());
        int count = read(sockfd, buf, 1023);
        cout << "Got array: " << buf << " from server" << endl;

        mean_fun(string(buf));

        shutdown(sockfd, SHUT_RDWR);
    }
    else
        error("ERROR connecting");
}