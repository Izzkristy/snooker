
struct clienMsg
{
    char msgType;
    int id;
    char data[4];
};

struct loginMsg
{
    char name[20];
    char pwd[20];
};

struct loginResult
{
    int msgLen;
    char msgType;
    char result;
    int id;
    int score;
};

//处理消息
void deal_msg(char *buf);

static void deal_login(struct clienMsg *msg);
static void deal_hall(struct clienMsg *msg);
static void deal_play(struct clienMsg *msg);
static void deal_quit(struct clienMsg *msg);
static void deal_chat(struct clienMsg *msg);

