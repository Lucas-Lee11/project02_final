#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    if(!pid) {
        execl("./input_reader_renderer", "input_reader_renderer", (char *) NULL);
    }

    sleep(1);

    execl("./simulation", "simulation", (char *) NULL);

    return 0;
}
