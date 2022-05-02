#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define SHMSZ     1024



void mode_fun(string num_arr) {

    stringstream ss(num_arr);
    string str;
    vector<int> num_vec;

    while( ss>>str ) {
        num_vec.push_back(stoi(str));
    }
    
    sort(num_vec.begin(), num_vec.end());

    int n = num_vec.size();

//-------------------------------------------------
    //Mode calculate
    vector<bool> visited(n, false);
    vector<int> mode_vals;
    int max_freq = 0;

    for(int i=0; i<n; i++) {
        if(visited[i] == true)
            continue;

        int cnt = 1;
        for(int j=i+1; j<n; j++) {
            if(num_vec[i] == num_vec[j]) {
                visited[j] = true;
                cnt++;
            }
        }
        if(max_freq < cnt) {
            max_freq = cnt;
            mode_vals.clear();
            mode_vals.push_back(num_vec[i]);
        }
        else if (max_freq == cnt)
            mode_vals.push_back(num_vec[i]);
    }

//-------------------------------------------------

    //Output
    cout << "Mode is ";
    for(int i=0; i<mode_vals.size(); i++)
        cout << mode_vals[i] << ' ';
    cout << endl;

}

int main() {

    int shmid;
    char* shm, *s;

    // Shared Memory init
    key_t key = ftok("shmfile",65);

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *) - 1) {
        perror("shmat");
        exit(1);
    }

    string ready_msg = "Client 3 is ready.";
    strcpy(shm, ready_msg.c_str());

    while(strcmp(shm, ready_msg.c_str()) == 0) {
        sleep(1);
    }

    cout << "Got array: " << shm << " from server" << endl;

    mode_fun(string(shm));

    //detach from shared memory 
    shmdt(shm);

    return 0;
}