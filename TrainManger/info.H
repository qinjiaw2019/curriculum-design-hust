#ifndef _INFO_H
#define _INFO_H

//定义车次基本信息结构体
typedef struct TrainInfo
{
	char trainId[8];			//车次编号
	char trainName[20];			//车次名称
	char trainCode[1];			//车次类型编码
	char typeName[20];			//车次类型名称
	char rodeId[8];				//所属路局编号
	char rodeName[20];			//所属路局名称
	char startStaion[10];		//始发站
	char startTime[20];			//始发时间
	char endStation[10];		//终到站
	char endTime[20];			//终到时间
	float hardLwr;				//硬卧下铺全程票价
	float hardMid;				//硬卧中铺全程票价
	float hardUpper;			//硬卧上铺全程票价
	float softLwr;				//软卧下铺全程票价
	float softUpper;			//软卧上铺全程票价
	float hardSit;				//硬座全程票价
	char fullTime[10];			//全程运行时间
    int fullMile;				//全程运行里程
	struct TrainInfo *trainNext;//指向下一节点的指针
	struct StopStation *stopNext;//指向经停车站基本信息链的指针

}TrainInfo,*PTrainInfo;	

//定义经停车站基本信息结构体
typedef struct StopStationInf
{
	
	char stationidI[8];			//车站编号
	char trainType[8];			//车次编号
	char stopId[8];				//车站编号
	char stopName[20];			//车站名称
	char stopRodeId[8];			//所属路局编号	
	char atStation[10];			//到站时间
	char driveTime[10];			//开车时间
	char runTime[10];			//运行时间
	int runMile;				//运行里程
	float hardLwr;				//硬卧下铺全程票价
	float hardMid;				//硬卧中铺全程票价
	float hardUpper;			//硬卧上铺全程票价
	float softLwr;				//软卧下铺全程票价
	float softUpper;			//软卧上铺全程票价
	float hardSit;				//硬座全程票价
	int leftTicket;				//余票车次数量
	struct StopStationInf *stopTrainNext;//指向下一节点的指针
}StopStationInf,*PStopStationInf;

//定义经停车站基本信息结构体
typedef struct 	StopStation
{
	char stationId[8];			//车站编号
	char stopid[8];				//经停车次编号
	char soptTrainName[20];		//经停车次名称
	char rodeId[8];				//路局编号
	char trainType[6];			//车次类型
	char atTime[10];			//进站时间
	char leaveTime[10];			//开车时间
	float hardLwr;				//硬卧下铺全程票价
	float hardMid;				//硬卧中铺全程票价
	float hardUpper;			//硬卧上铺全程票价
	float softLwr;				//软卧下铺全程票价
	float softUpper;			//软卧上铺全程票价
	float hardSit;				//硬座全程票价
	int leftTicket;				//余票车次数量
	struct StopStation *stopNext;//指向下一节点的指针
	struct StopStationInf *stopTrainNext;//指向停车次基本信息指针
}StopStation,*PStopStation;


void Menu();//菜单
int drawMenu(char *str[],int left,int top,int line_height,bool line_flag);//绘制一个菜单

int showMenu(int option);//显示菜单
int menuAction();//菜单Action

int setLeft(int left);//控制左间距
int setTop(int top);//控制上间距
int getLength(int li);//获得链表的长度

int Scanf(int left,int top);//一次输入
int FScanf(int n);

void Error();//报错并返回

//车次
void add_train();//新增车次
void change_train();//修改车次
void delete_train();//删除车次
void print_train(bool div);//打印车次信息    div true折叠  false 展开
PTrainInfo findTrain(int n,char *str,int rhs);//查找  n：更具节点位置查    或更具传入的字符str（编号）查（当n=0时表示按str查） 返回这个节点 得到的是前一个节点  

//停车站
void add_stop();//新增停车站
void change_stop();//修改停车站
void print_stop();//打印停车站信息
void delete_stop();//删除停车站
PStopStation findStop(int n,char *str);//查找  n：更具节点位置查    或更具传入的字符str（经停车次编号）查（当n=0时表示按str查） 返回这个节点 得到的是前一个节点  


//经停车站信息
void add_stop_inf();//新增经停车站信息
void change_stop_inf();//修改经停车站信息
void delete_stop_inf();//删除经停车站信息
PStopStationInf findStopInf(int n,char *str);//查找


//查询
void simple_list(int type);//简单列表
void sigle(int i);//单条件查询
void print_query(int i,int t);//查询打印  t查询控制
void print(int m);//查询打印m 类型

void tongji();//数据统计

void load();//加载一条链表  
void print();//遍历一条全局链表 
void Write(int n,int pos,char *str);//写入文件  n：链表标示  pos第n个节点，str字符串
void lists(int n,int many,bool ul);//列表  many<0表示只循环一次  many>0表示全部循环   bool = true 显示项目序号  bool= false 显示列表序号

//全局变量
PTrainInfo train_info,p11,front,tail=NULL;//车次基本信息链表  tail辅助指针   p11查询结构链表
PStopStationInf sotp_station_info,p33,tail3=NULL;//经停车次基本信息链表
PStopStation stop_station,p22,tail2=NULL;//停车站基本信息链表   //有头节点

int post=1; //节点定位附加变量

//查询用的变量
int mil=1;
char strs[20];
int rhs=1;

#define WIN_SIZE "mode con cols=250 lines=500"  //控制台尺寸 150*250
#define TRAINSIZE sizeof(TrainInfo)  //计算车次结构体大小
#define STOPSIZE sizeof(TrainInfo)  //计算停车站结构体大小
#define STOPINFSIZE sizeof(StopStationInf) //计算经停车站结构体大小

#endif