#ifndef INPUT_H_
#define INPUT_H_

#define WELL_KNOWN_PIPE "wowzer_bowzer"

//estblishing input code constants
enum {
    //begins and ends input sequences
    END,
    BEGIN,
    //constants for various input codes
    P_UP,
    P_DOWN,
    P_LEFT,
    P_RIGHT,
    PASS,

    //terminate the program
    TERMINATE
};

int init_processer_connection(int * fd, const char * wkp);
int establish_processer_connection(int * fd, const char * wkp);

void send_input(int fd , const int * input_codes);
//not needed as it just recreates read exactly
//void read_input(int fd, int * buff);

#endif
