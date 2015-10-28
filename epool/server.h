#ifndef SERVER_H
#define SERVER_H

#define IPADDRESS   "127.0.0.1"
#define PORT        7962
#define MAXSIZE     1024
#define LISTENQ     5
#define FDSIZE      1000
#define EPOLLEVENTS 100
#define USERNAMELEN 20
#define PLAYERNUM   18

struct player
{
    int id;
    char name[USERNAMELEN];
    int score;
    int socket;
};

extern int connect_num;
extern struct player player[PLAYERNUM];

#endif
