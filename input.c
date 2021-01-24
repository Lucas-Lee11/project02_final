#include <stdio.h>
#include <string.h>

#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "input.h"

/*
 * Create well known pipe and wait for connection. Populate fd with out pipe and then in pipe 
 * Returns: 0 on success else -1
*/

int init_processer_connection(int * fd, const char * wkp) {
    //handshake
    int success = mkfifo(wkp, 0644);
    if(success == -1 && errno != EEXIST) {
        fprintf(stderr, "Error making pipe: %s\n", strerror(errno));

        return -1;
    }

    //not going to error catch this, shouldn't be needed
    fd[1] = open(wkp, O_RDONLY);
    remove(wkp);

    //you better not have so many processes you get to 10 digits
    char in_buff[10];
    read(fd[1], in_buff, sizeof(in_buff)-1);

    fd[0] = open(in_buff, O_WRONLY);

    //"0" is acknoledgement code
    write(fd[0], "0", sizeof("0"));

    return 0;
}

/*
 * Establishes connection to the processor through the wkp (proforms handshake). Populate fd with out pipe and then in pipe
 * Returns: 0 on success else -1
*/

int establish_processer_connection(int * fd, const char * wkp) {
    //handshake
    fd[0] = open(wkp, O_WRONLY);
    if(fd[0] == -1) {
        fprintf(stderr, "Error opening wkp: %s\n", strerror(errno));

        return -1;
    }

    //you better not have that many processes running 10^10 is very big
    char out_buff[10];
    sprintf(out_buff, "%d", getpid());

    int success = mkfifo(out_buff, 0644);
    if(success == -1 && errno != EEXIST) {
        fprintf(stderr, "Error making pipe: %s\n", strerror(errno));

        return -1;
    }

    write(fd[0], out_buff, sizeof(out_buff));

    fd[1] = open(out_buff, O_RDONLY);
    remove(out_buff);

    char in_buff[10];
    read(fd[1], in_buff, sizeof(in_buff));

    if(in_buff[0]-'0' == 0) {
        return 0;
    } else {
        return -1;
    }
}

/*
 * Sends formatted input codes to the given pipe 
 * Returns: void
*/

void send_input(int fd, const int * input_codes) {
    int e = END;
    write(fd, input_codes, sizeof(*input_codes));
    write(fd, &e, sizeof(e));
}
