#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MYPORT "4950"  

#define MAXBUFLEN 100

FILE *status;
FILE *status2;
FILE *status3;
FILE *status4;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    while(1) {
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE; // use my IP

        if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            return 1;
        }

        // loop through all the results and bind to the first we can
        for(p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                    p->ai_protocol)) == -1) {
                perror("listener: socket");
                continue;
            }

            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("listener: bind");
                continue;
            }

            break;
        }

        if (p == NULL) {
            fprintf(stderr, "listener: failed to bind socket\n");
            return 2;
        }

        freeaddrinfo(servinfo);

        printf("listener: waiting to recvfrom...\n");

        addr_len = sizeof their_addr;
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
        }




        printf("listener: got packet from %s\n",
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s));
        printf("listener: packet is %d bytes long\n", numbytes);
        buf[numbytes] = '\0';
        printf("listener: packet contains \"%s\"\n", buf);


        char *count = malloc(sizeof(char));
        char *left = malloc(sizeof(char));
        char *right = malloc(sizeof(char));

        count = strtok(buf, " ");


        if (strcmp(count, "1") == 0) {
            left = strtok(NULL, " ");
        } else if (strcmp(count, "2") == 0) {
            left = strtok(NULL, " ");
            right = strtok(NULL, " ");
        }


        status = fopen("count.txt", "w");
        if (status == NULL) {
            fprintf(stderr, "Could not open status.txt\n");
        }
        memset(status, 0, sizeof status);
        fwrite(count, 1, 1, status);


        status2 = fopen("left.txt", "w");
        if (status2 == NULL) {
            fprintf(stderr, "Could not open status2.txt\n");
        }
        memset(status2, 0, sizeof status2);
        fwrite(left, 1, 1, status2);




        if (strcmp(count, "2") == 0) {
            status3 = fopen("right.txt", "w");
            if (status3 == NULL) {
                fprintf(stderr, "Could not open status3.txt\n");
            }
            memset(status3, 0, sizeof status3);
            fwrite(right, 1, 1, status3);
        }

        char ava[1];


        if (strcmp(count, "1") == 0) {
            if (strcmp(left, "1") == 0) {
                ava[0] = '1';
            } else {
                ava[0] = '0';
            }
        } else {
            if (strcmp(left, "1") == 0 && strcmp(right, "0") == 0) {
                ava[0] = '1';
            } else if (strcmp(left, "0") == 0 && strcmp(right, "1") == 0 ) {
                ava[0] = '1';
            } else if (strcmp(left, "1") == 0 && strcmp(right, "1") == 0) {
                ava[0] = '2';
            } else {
                ava[0] = '0';
            }
        }


        status4 = fopen("ava.txt", "w");
        if (status4 == NULL) {
            fprintf(stderr, "Could not open status4.txt\n");
        }
        memset(status4, 0, sizeof status4);
        fwrite(ava, 1, 1, status4);
        


        fclose(status);
        fclose(status2);

        if (strcmp(count, "2") == 0) {
            fclose(status3);
        }
        fclose(status4);


        close(sockfd);
    }

    

    return 0;
}