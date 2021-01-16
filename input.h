#ifndef INPUT_H_
#define INPUT_H_

#define WELL_KNOWN_PIPE "wowzer_bowzer"

//estblishing input code constants
enum {
    //begins and ends input sequences
    END = 0,
    BEGIN = 1,
    //constants for various input codes
    P_UP = 2,
    P_DOWN = 3,
    P_LEFT = 4,
    P_RIGHT = 5
};

int init_processer_connection(int * fd, const char * wkp);
int establish_processer_connection(int * fd, const char * wkp);

void send_input(int fd , const int * input_codes);
//not needed as it just recreates read exactly
//void read_input(int fd, int * buff);

#endif
