#ifndef GLOBAL_H
#define GLOBAL_H

#include "connectServer.h"
#define PLAYERNUM 18

struct Player
{
    int id;
    QString name;
    int score;
};

extern struct Player player[PLAYERNUM];
extern int G_id;
extern QString G_name;
extern int G_score;
extern QString G_password;
extern int G_onlineNum;
extern int G_playNo;
extern connectServer serverConnect;

#endif // GLOBAL_H
