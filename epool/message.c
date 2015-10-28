#include <stdio.h>
#include <string.h>
#include "message.h"
#include "server.h"

void deal_msg(char *buf)
{
    struct clienMsg *msg = (struct clienMsg *)buf;
    switch (msg->msgType)
    {
        case 'L':
            deal_login(msg);
            break;
        case 'H':
            deal_hall(msg);
            break;
        case 'P':
            deal_play(msg);
            break;
        case 'Q':
            deal_quit(msg);
            break;
        case 'M':
            deal_chat(msg);
            break;
    }
}

static void deal_login(struct clienMsg *msg)
{
    struct loginMsg *login = (struct loginMsg*)msg->data;
    printf("%s\n",login->name);
    printf("%s\n",login->pwd);
    memset(msg,0x00,MAXSIZE);
    struct loginResult *result = (struct loginResult *)msg;
    result->msgType = 'L';
    result->result = 1;
    result->id = htonl(1);
    result->score = htonl(2);
    result->msgLen = htonl(sizeof(struct loginResult) - sizeof(int));
    return;
}
static void deal_hall(struct clienMsg *msg)
{
    return;
}
static void deal_play(struct clienMsg *msg)
{
    return;
}
static void deal_quit(struct clienMsg *msg)
{
    return;
}
static void deal_chat(struct clienMsg *msg)
{
    return;
}