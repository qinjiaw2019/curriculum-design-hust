#include "graph.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>


/******************************************************
 *
 *  功能描述:创建图(邻接表)
 *  函数名称:CreateGraph
 *  参   数:      @param  adj 一个空的头节点指针
 *  返回值 :       @return void
 *  实现原理:如果头指针adj为空则创建图，如果adj不为空则指向
 *          新的图，原来的内容丢失。
 *          1.根据文件读取人基本物信息，将信息保存至机结构体
 *          2.根据已有的唯一标识id读取人物介绍信息和关系保存
 *            至相应的结构体
 *
 ******************************************************/
void CreateGraph(AdjList *adj)
{
    //计数器
    int i = 0;
    int flag = 1;

    //保存id值
    int id;

    //初始化顶点数
    adj->VexNum = 0;
    //初始化边数
    adj->ArcNum = 0;

    Relative *pdj = NULL,*pr,*dpr;

    //初始化坐标最大值
    adj->vertex[0].y = 0;
    adj->vertex[0].x = 0;
    adj->vertex[0].weight = 0;

    QFile f(":/data/data/person.txt");

    //如果文件不存在报错
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        msg("File open error!");


    QTextStream txtInput(&f);

    //标识名称
    QString lineStr;
    QString flagStr;

    //初始化表头结点
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();

        //去掉两端的空白字符用当个空格代替
        lineStr = lineStr.simplified();
        //去掉两端空白字符
        lineStr = lineStr.trimmed();

        flagStr = lineStr.mid(0,lineStr.indexOf('='));
        //mid从a位置到末尾
        lineStr = lineStr.mid(lineStr.indexOf('=')+1);

        if(!lineStr.isEmpty() && lineStr.size()>0  )
        {
            //判断顶点数组空间是否已满
            if(i+1>MAX_VERTEX_NUM-1)
                msg("Array OverFlow!");

            // 得到id
            if(flagStr.endsWith("id") && flagStr.startsWith("id"))
            {
                 i++;
                 //把总记录保存在一个顶点
                 adj->vertex[0].id = i;
                 id = lineStr.toInt();

                 adj->vertex[i].id = lineStr.toInt();
                 adj->vertex[i].firstedge=NULL;
                 adj->vertex[i].rlt = NULL;

                 //创建一个关系节点用于统计关系数 并初始化为0  这是最后一个节点
                 pdj = new Relative;

                 //如果分配失败
                 if(pdj==NULL)
                    msg("Creating Graph error!");

                 pdj->next = NULL;
                 pdj->id = 0;


                 adj->vertex[i].rlt = pdj;

                 //创建邻节表头节点
                 EdgeNode *q = NULL;

                 q = new EdgeNode;
                 if(q==NULL) return;
                 q->next = NULL;
                 q->data = "0";

                 adj->vertex[i].firstedge = q;

            }

            //得到name
            if(flagStr.endsWith("name") && flagStr.startsWith("name"))
                adj->vertex[i].data = lineStr;

            //得到坐标x
            if(flagStr.endsWith("x") && flagStr.startsWith("x"))
            {
                adj->vertex[i].x = lineStr.toInt();
                if(adj->vertex[0].x < (adj->vertex[i].x))
                       //获得x坐标的最大值
                       adj->vertex[0].x  = adj->vertex[i].x;


            }

            //得到坐标y
            if(flagStr.endsWith("y") && flagStr.startsWith("y"))
            {
                adj->vertex[i].y = lineStr.toInt();
                if(adj->vertex[0].y < (adj->vertex[i].y))
                        //获得y坐标的最大值
                       adj->vertex[0].y  = adj->vertex[i].y;

            }

            //得到坐标pic
            if(flagStr.endsWith("pic") && flagStr.startsWith("pic"))
            {
                adj->vertex[i].pic = lineStr;
            }

            //权值
            if(flagStr.endsWith("weight") && flagStr.startsWith("weight"))
            {
                adj->vertex[i].weight = lineStr.toDouble();
                adj->vertex[0].weight = i;
            }

            //保存关系
            if(flagStr.endsWith("toNextId") && flagStr.startsWith("toNextId") && !lineStr.isEmpty())
            {
                QStringList list = lineStr.split(",");//关系链表
                EdgeNode *q = NULL,*p;//头结点
                int count=0;//计数器

                p = adj->vertex[i].firstedge;

                for(int j = 0;j<list.size();j++)//生成表结点链表
                {
                    QString str = list.at(j);
                    if(!str.isEmpty())
                    {
                         //创建邻接表
                         q  = new EdgeNode;
                         if(q==NULL) return ;
                         q->next = NULL;
                         q->data = str;
                         p->next = q;
                         p = q;

                         count++;
                    }
                }

                adj->vertex[i].firstedge->data =QString::number(count);

                //统计边数
                 adj->ArcNum +=count;
            }
        }
    }
    //第一个顶点数计数点  没有邻接点
    adj->vertex[0].firstedge=NULL;
    adj->VexNum = adj->vertex[0].id;

    f.close();

    //添加边
    QFile fr(":/data/data/relative.txt");
    if(!fr.open(QIODevice::ReadOnly | QIODevice::Text))
        msg("File Open fail!");

    QTextStream txtInputr(&fr);
    //保存获得的父Id值
    int parentId = -1;

    while(!txtInputr.atEnd())
    {
        i= 0;
        lineStr = txtInputr.readLine();
        //去掉两端的空白字符用当个空格代替
        lineStr = lineStr.simplified();
        //去掉两端空白字符
        lineStr = lineStr.trimmed();

        flagStr = lineStr.mid(0,lineStr.indexOf('='));
        //mid从a位置到末尾
        lineStr = lineStr.mid(lineStr.indexOf('=')+1);

        if(!lineStr.isEmpty() && lineStr.size()>0  )
        {

            if(flagStr.endsWith("id") && flagStr.startsWith("id"))
            {
                //如果读取的id存在则
                if(findById(adj,lineStr.toInt()) >=0)
                {
                    parentId = lineStr.toInt() ;
                }
                continue;
            }

            //  得到id
            if(flagStr.endsWith("toNextId") && flagStr.startsWith("toNextId"))
            {
                //如果读取的id存在则
                if(findById(adj,lineStr.toInt())>=0&& parentId>=0)
                {

                    pdj = adj->vertex[parentId + 1].rlt;
                    pr = new Relative;
                    if(pr==NULL)
                        return;

                    pr->next = pdj->next;
                    pr->id = lineStr.toInt() +1;
                    pdj->next = pr;
                }
                continue;
            }

            //得到关系
            if(flagStr.endsWith("relative") && flagStr.startsWith("relative"))
            {
                pr->realtive = lineStr;
            }
            parentId = -1;
        }

    }

    fr.close();
}


/******************************************************
 *
 *  功能描述:根据id查找
 *  函数名称:findById
 *  参   数:      @param  adj 图头结点指针
 *                @param  id ID
 *  返回值 :       @return -1:查找失败，其他返回位置
 *  实现原理:如果adj为空则直接返回，否则返回id对应的位置
 *
 ******************************************************/
int findById(AdjList *adj,int id)
{
    if(adj==NULL) return -1;
    for(int i = 1;i<getSize(adj);i++)
        if(adj->vertex[i].id == id)
            return id;
    return -1;
}

/******************************************************
 *
 *  功能描述:获得顶点数
 *  函数名称:getSize
 *  参   数:      @param  adj 图头结点指针
 *  返回值 :       @return -1:查找失败，其他返总记录数
 *  实现原理:如果adj为空则直接返回，否则返总记录数
 *
 ******************************************************/
int getSize(AdjList *adj)
{
    if(adj!=NULL && adj->vertex[0].id > 0){
        return adj->vertex[0].id;
    }
    return -1;
}

/******************************************************
 *
 *  功能描述:获得顶点i的表结点数
 *  函数名称:getEdgeSize
 *  参   数:      @param  adj 图头结点指针
 *  参   数:      @param  i   ID
 *  返回值 :       @return -1:查找失败，其他ID的所在位置
 *  实现原理:如果adj为空则直接返回，否则返ID的所在位置
 *
 ******************************************************/
int getEdgeSize(AdjList *adj,int i)
{
    if(adj!=NULL)
    {
        if(i<getSize(adj) && i > 0)
        {
            if(adj->vertex[i].firstedge!=NULL)
                return (adj->vertex[i].firstedge->data).toInt();
        }
    }
    return -1;
}

/******************************************************
 *
 *  判断id是否存在
 *  函数名称:isHasId
 *  参   数:      @param  adj 图头结点指针
 *  参   数:      @param  id  ID
 *  返回值 :       @return true:ID存在 false:ID不存在
 *  实现原理:如果adj为空则直接返回，否则返ID的所在位置
 *
 ******************************************************/
bool isHasId(AdjList *adj,int id)
{
    if(findById(adj,id)>0)
        return true;
    return false;
}

/******************************************************
 *
 *  判断id是否存在
 *  函数名称:isHasId
 *  参   数:      @param  adj 图头结点指针
 *  返回值 :       @return true:图信息完整 false:图信息不完整
 *  实现原理:如果adj为空则直接返回，如果id等信息不匹配或混乱则表
 *          图信息不完整
 *
 ******************************************************/
bool checkAdj(AdjList *adj)
{
    //顶点个数，后面要遍历每一个点
    int n=adj->VexNum;
    EdgeNode *q=NULL;
    int i;
    int j=0;

    for( i=1;i<=n;i++)
    {
        q=adj->vertex[i].firstedge;
        if(q!=NULL)
        {
           while(q->next!=NULL)
            {
                q = q->next;
                j++;
                if(findById(adj,(q->data).toInt())<0)
                     return false;
            }
        }
    }
    return true;
}

/******************************************************
 *
 *  根据id查到其所有子节点
 *  函数名称:getChild
 *  参   数:      @param  adj 图头结点指针
 *  参   数:      @param  id  ID
 *  返回值 :       @return 边指针
 *  实现原理:如果adj为空则直接返回，如果没有子节点则返回NULL
 *
 ******************************************************/
EdgeNode * getChild(AdjList *adj,int id)
{
    if(adj!=NULL && id<=adj->VexNum)
    {
        return adj->vertex[id].firstedge;
    }

    return NULL;
}

/******************************************************
 *
 *  根据名称获得其所有子代
 *  函数名称:getByNmame
 *  参   数:      @param  adj 图头结点指针
 *  参   数:      @param  name  名称
 *  返回值 :       @return 人物信息集合
 *  实现原理:如果adj为空则直接返回，如果没有则返回空集合
 *
 ******************************************************/
QStringList getByNmame(AdjList *adj,QString name)
{
    QStringList list;
    EdgeNode *en;
    list.clear();
    for(int i = 1;i<adj->VexNum;i++)
    {
        if(adj->vertex[i].data == name)
        {
            en = adj->vertex[i].firstedge;
            while(en->next!=NULL)
            {
                en = en->next;
                for(int j=1;j<=adj->VexNum;j++)
                    if(adj->vertex[j].id==en->data.toInt())
                    {
                        list.append(adj->vertex[j].data);
                        break;
                    }
            }
            return list;
        }
    }

    //如果没有记录则返回空的集合
    list.append("");
    return list;
}

/******************************************************
 *
 *  销毁图
 *  函数名称:destroyGraph
 *  参   数:      @param  adj 图头结点指针
 *  返回值 :       @return 无
 *  实现原理:如果adj为空则直接返回，否则销毁边结构和关系结构
 *          并将顶点数组重置
 *
 ******************************************************/
void destroyGraph(AdjList *adj)
{
    if(NULL==adj)
        msg("Tips:","Creating Error!");

    Relative *rlt,*pre_rlt;
    EdgeNode *en,*pre_en;
    for(int i = 1;i<=adj->VexNum;i++)
    {
        //销毁关系
        rlt = adj->vertex[i].rlt;
        while(rlt->next!=NULL)
        {
            pre_rlt = rlt;
            rlt = rlt->next;
            delete pre_rlt;
        }
        adj->vertex[i].rlt = NULL;

        //销毁邻接表
        en = adj->vertex[i].firstedge;
        while(en->next!=NULL)
        {
            pre_en = en;
            en = en->next;
            delete pre_en;
        }
        adj->vertex[i].firstedge = NULL;

        //将全部顶点信息设置为初始状态
        adj->vertex[i].data ="";
        adj->vertex[i].id=0;
        adj->vertex[i].pic = "";
        adj->vertex[i].weight = 0;
        adj->vertex[i].x = 0;
        adj->vertex[i].y = 0;

    }
}


/******************************************************
 *
 *  消息提示框
 *  函数名称:msg
 *  参   数:      @param  title 消息头
 *  参   数:      @param  string 消息体
 *  参   数:      @param  isReturn 是否返回
 *  返回值 :       @return 无
 *  实现原理:
 *
 ******************************************************/
void msg(QString title,QString string,bool isReturn)
{
    //QStringLiteral("提示：")
    QMessageBox::information(NULL,title, string);
    if(isReturn)
        return;
}

/******************************************************
 *
 *  消息提示框 重载@Overrid
 *  函数名称:msg
 *  参   数:      @param  title 消息头
 *  参   数:      @param  string 消息体
 *  参   数:      @param  isReturn 默认为true
 *  返回值 :       @return 无
 *  实现原理:
 *
 ******************************************************/
void msg(QString title,QString string)
{
    msg(title,string,true);
}

/******************************************************
 *
 *  消息提示框 重载@Overrid
 *  函数名称:msg
 *  参   数:      @param  title 消息头  默认为Tips:
 *  参   数:      @param  string 消息体
 *  参   数:      @param  isReturn 默认为true
 *  返回值 :       @return 无
 *  实现原理:
 *
 ******************************************************/
void msg(QString string)
{
    msg("Tips:",string,true);
}
