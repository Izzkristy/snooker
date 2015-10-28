//全局变量文件

#ifndef DESK_H
#define DESK_H
//最大游戏人数
#define PLAYERNUM 18
//最大线程数，最大登陆人数，最大连接数
#define MAXTHREADNUM 50
//大厅数据更新时间
#define UPDATETIME 500
//玩家信息
struct Player
{
    int id;//用户ID
    QString name;//用户名
    int score;//已获得的分数
};
//当前游戏玩家的信息
extern struct Player player[PLAYERNUM];
//当前在线人数
extern int onlineNum;

#endif // DESK_H
