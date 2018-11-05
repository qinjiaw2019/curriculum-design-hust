#ifndef GRAPH_H
#define GRAPH_H
#include <QString>


/**宏定义常量*/
#define MAX_VERTEX_NUM 160  //定义图的最大顶点数
#define MAX_NAME_SIZE 20    //name长度

typedef QString VertexData;

/**关系信息结构体*/
typedef struct Relative
{
    int id;                 //映射哪个顶点
    VertexData realtive;    //与顶点的关系
    Relative *next;
}Relative;

/**邻接表信息结构体*/
typedef struct EdgeNode     //表结点
{
    int adjvex;             //邻接点域
    VertexData data;
    EdgeNode *next;         //边结点所对应的下一个边结点
} EdgeNode;

/**顶点信息结构体*/
typedef struct VertexNode
{
    int id;                 //id字段
    int x;                  //坐标x
    int y;                  //坐标y
    VertexData data;        //第一个顶点保存顶点个数
    VertexData pic;         //图片
    double weight;          //权值
    Relative *rlt;          //与顶点的关系
    EdgeNode *firstedge;    //头结点所对应的第一个边结点
}VertexNode;
typedef struct AdjList
{
    int VexNum,ArcNum;      //定义图的顶点数和边数
    VertexNode vertex[MAX_VERTEX_NUM];//定义头结点数组。
}AdjList;


/**方法定义*/

/*
* 创建图(邻接表)
* @param  adj  图头指针
* @return 无
*/
void CreateGraph(AdjList *adj);

/*
* 销毁图
* @param  adj  图头指针
* @return 无
*/
void destroyGraph(AdjList *adj);

/*
* 根据id查找
* @param  adj   图头指针
* @param  id    ID
* @return -1:查找失败，其他返回位置
*/
int findById(AdjList *adj,int id);

/*
* 获得顶点数
* @param  adj    图头指针
* @return -1:查找失败，其他返回位置
*/
int getSize(AdjList *adj);

/*
* 获得顶点i的表结点数
* @param  adj     图头指针
* @param  i       ID
* @return -1:查找失败，其他返回位置
*/
int getEdgeSize(AdjList *adj,int i);

/*
* 判断id是否存在
* @param  adj     图头指针
* @param  id  ID
* @return true:存在  false:不存在
*/
bool isHasId(AdjList *adj,int id);

/*
* 检查图信息是否完整，关键信息是否匹配
* @param  adj      图头指针
* @return true:信息匹配  false:信息不匹配
*/
bool checkAdj(AdjList *adj);

/*
* 根据名称获得其所有子代
* @param  adj     图头指针
* @param  name    名称
* @return         人物信息集合
*/
QStringList getByNmame(AdjList *adj,QString name);

/*
* 消息提示框
* @param  title    消息头
* @param  string   消息体
* @param  isReturn 消息提示后是否从该位置返回
* @return          无
*/
void msg(QString title,QString string,bool isReturn);

/*
* @Override        弹出消息框,重载了
*                  msg(QString title,QString string,bool isReturn)
*                  将isReturn默认为true
*
* @param  title    消息头
* @param  string   消息体
* @return          无
*/
void msg(QString title,QString string);

/*
* @Override        弹出消息框,重载了
*                  msg(QString title,QString string,bool isReturn)
*                  将isReturn默认为true,title默认为Tips:
*
* @param  title    消息头
* @param  string   消息体
* @return          无
*/
void msg(QString string);

/*
* 根据id查到其所有子节点
* @param  adj      图头指针
* @param  id       ID
* @return          边节点指针
*/
EdgeNode * getChild(AdjList *adj,int id);
#endif // GRAPH_H
