#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LEN_MSG 64
#define PATH_FILE   "/proc/my_proc_file"

int main()
{
    int  fd;
    char recv_msg[MAX_LEN_MSG];
    char send_msg[] = "Hello, kernel!";

    fd = open(PATH_FILE, O_RDWR); 
    if (fd < 0){
        perror("open");
        return -1;
    }

    // Считываем сообщение из пространства ядра
    if (read(fd, recv_msg, MAX_LEN_MSG) == -1){
        printf("error read from %s\n", PATH_FILE);
        return -1;
    }
    printf("Read from kernel: %s\n", recv_msg);

    // Спускаем сообщение в пространство ядра
    if (write(fd, send_msg, strlen(send_msg) + 1) == -1){
        printf("error write to %s\n", PATH_FILE);
        return -1;
    }
    close(fd);
    return 0;
}