#ifndef _INFO_H
#define _INFO_H

//���峵�λ�����Ϣ�ṹ��
typedef struct TrainInfo
{
	char trainId[8];			//���α��
	char trainName[20];			//��������
	char trainCode[1];			//�������ͱ���
	char typeName[20];			//������������
	char rodeId[8];				//����·�ֱ��
	char rodeName[20];			//����·������
	char startStaion[10];		//ʼ��վ
	char startTime[20];			//ʼ��ʱ��
	char endStation[10];		//�յ�վ
	char endTime[20];			//�յ�ʱ��
	float hardLwr;				//Ӳ������ȫ��Ʊ��
	float hardMid;				//Ӳ������ȫ��Ʊ��
	float hardUpper;			//Ӳ������ȫ��Ʊ��
	float softLwr;				//��������ȫ��Ʊ��
	float softUpper;			//��������ȫ��Ʊ��
	float hardSit;				//Ӳ��ȫ��Ʊ��
	char fullTime[10];			//ȫ������ʱ��
    int fullMile;				//ȫ���������
	struct TrainInfo *trainNext;//ָ����һ�ڵ��ָ��
	struct StopStation *stopNext;//ָ��ͣ��վ������Ϣ����ָ��

}TrainInfo,*PTrainInfo;	

//���徭ͣ��վ������Ϣ�ṹ��
typedef struct StopStationInf
{
	
	char stationidI[8];			//��վ���
	char trainType[8];			//���α��
	char stopId[8];				//��վ���
	char stopName[20];			//��վ����
	char stopRodeId[8];			//����·�ֱ��	
	char atStation[10];			//��վʱ��
	char driveTime[10];			//����ʱ��
	char runTime[10];			//����ʱ��
	int runMile;				//�������
	float hardLwr;				//Ӳ������ȫ��Ʊ��
	float hardMid;				//Ӳ������ȫ��Ʊ��
	float hardUpper;			//Ӳ������ȫ��Ʊ��
	float softLwr;				//��������ȫ��Ʊ��
	float softUpper;			//��������ȫ��Ʊ��
	float hardSit;				//Ӳ��ȫ��Ʊ��
	int leftTicket;				//��Ʊ��������
	struct StopStationInf *stopTrainNext;//ָ����һ�ڵ��ָ��
}StopStationInf,*PStopStationInf;

//���徭ͣ��վ������Ϣ�ṹ��
typedef struct 	StopStation
{
	char stationId[8];			//��վ���
	char stopid[8];				//��ͣ���α��
	char soptTrainName[20];		//��ͣ��������
	char rodeId[8];				//·�ֱ��
	char trainType[6];			//��������
	char atTime[10];			//��վʱ��
	char leaveTime[10];			//����ʱ��
	float hardLwr;				//Ӳ������ȫ��Ʊ��
	float hardMid;				//Ӳ������ȫ��Ʊ��
	float hardUpper;			//Ӳ������ȫ��Ʊ��
	float softLwr;				//��������ȫ��Ʊ��
	float softUpper;			//��������ȫ��Ʊ��
	float hardSit;				//Ӳ��ȫ��Ʊ��
	int leftTicket;				//��Ʊ��������
	struct StopStation *stopNext;//ָ����һ�ڵ��ָ��
	struct StopStationInf *stopTrainNext;//ָ��ͣ���λ�����Ϣָ��
}StopStation,*PStopStation;


void Menu();//�˵�
int drawMenu(char *str[],int left,int top,int line_height,bool line_flag);//����һ���˵�

int showMenu(int option);//��ʾ�˵�
int menuAction();//�˵�Action

int setLeft(int left);//��������
int setTop(int top);//�����ϼ��
int getLength(int li);//��������ĳ���

int Scanf(int left,int top);//һ������
int FScanf(int n);

void Error();//����������

//����
void add_train();//��������
void change_train();//�޸ĳ���
void delete_train();//ɾ������
void print_train(bool div);//��ӡ������Ϣ    div true�۵�  false չ��
PTrainInfo findTrain(int n,char *str,int rhs);//����  n�����߽ڵ�λ�ò�    ����ߴ�����ַ�str����ţ��飨��n=0ʱ��ʾ��str�飩 ��������ڵ� �õ�����ǰһ���ڵ�  

//ͣ��վ
void add_stop();//����ͣ��վ
void change_stop();//�޸�ͣ��վ
void print_stop();//��ӡͣ��վ��Ϣ
void delete_stop();//ɾ��ͣ��վ
PStopStation findStop(int n,char *str);//����  n�����߽ڵ�λ�ò�    ����ߴ�����ַ�str����ͣ���α�ţ��飨��n=0ʱ��ʾ��str�飩 ��������ڵ� �õ�����ǰһ���ڵ�  


//��ͣ��վ��Ϣ
void add_stop_inf();//������ͣ��վ��Ϣ
void change_stop_inf();//�޸ľ�ͣ��վ��Ϣ
void delete_stop_inf();//ɾ����ͣ��վ��Ϣ
PStopStationInf findStopInf(int n,char *str);//����


//��ѯ
void simple_list(int type);//���б�
void sigle(int i);//��������ѯ
void print_query(int i,int t);//��ѯ��ӡ  t��ѯ����
void print(int m);//��ѯ��ӡm ����

void tongji();//����ͳ��

void load();//����һ������  
void print();//����һ��ȫ������ 
void Write(int n,int pos,char *str);//д���ļ�  n��������ʾ  pos��n���ڵ㣬str�ַ���
void lists(int n,int many,bool ul);//�б�  many<0��ʾֻѭ��һ��  many>0��ʾȫ��ѭ��   bool = true ��ʾ��Ŀ���  bool= false ��ʾ�б����

//ȫ�ֱ���
PTrainInfo train_info,p11,front,tail=NULL;//���λ�����Ϣ����  tail����ָ��   p11��ѯ�ṹ����
PStopStationInf sotp_station_info,p33,tail3=NULL;//��ͣ���λ�����Ϣ����
PStopStation stop_station,p22,tail2=NULL;//ͣ��վ������Ϣ����   //��ͷ�ڵ�

int post=1; //�ڵ㶨λ���ӱ���

//��ѯ�õı���
int mil=1;
char strs[20];
int rhs=1;

#define WIN_SIZE "mode con cols=250 lines=500"  //����̨�ߴ� 150*250
#define TRAINSIZE sizeof(TrainInfo)  //���㳵�νṹ���С
#define STOPSIZE sizeof(TrainInfo)  //����ͣ��վ�ṹ���С
#define STOPINFSIZE sizeof(StopStationInf) //���㾭ͣ��վ�ṹ���С

#endif