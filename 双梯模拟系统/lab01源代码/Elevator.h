#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<Windows.h>
#include<random>
#include"Elevator.h"
#include"Human.h"
#include<math.h>
#define STACK_INIT_SIZE 11
#define DoorTime 20
#define WalkTime 25
#define TestTime 40
#define WaitTime 300
#define UpSlow 14
#define UpTime 51
#define DownSlow 23
#define DownTime 61
#define AccTime 15
/*#define DoorTime 0
#define WalkTime 0
#define TestTime 0
#define WaitTime 20
#define UpSlow 0
#define UpTime 0
#define DownSlow 0
#define DownTime 0
#define AccTime 0*/  //用于debug
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<Windows.h>
#include<random>
#include"Elevator.h"
using namespace std;
typedef struct {
	int Infloor;//进入楼层
	int Outfloor;//目标楼层
	float InterTime;//下一个乘客出现时间
	float GiveupTime;//放弃时间
	int ID;//编号
}info;
typedef struct LNode {
	int Infloor;
	int Outfloor;
	float InterTime;
	float GiveupTime;
	int ID;
	struct LNode* next;
}LNode, * Linklist;
typedef Linklist Queueptr;
typedef struct {
	Queueptr front;
	Queueptr rear;
}LinkQueue;

typedef struct {
	info* elem;
	int stacksize;
	int top;
}Sqstack;//电梯中的乘客栈
enum	ElevatorMove { Opening, Opened, Closing, Closed, Moving, SlowDown, Waiting, Accelerate};
enum	ElevatorState { GoingUp, GoingDown, Idle };
typedef struct ElevatorNode {
	int Floor;//代表电梯当前楼层
	int Callcar[5];//需要停留的楼层
	int Humman_num;//电梯内的人数
	ElevatorState State;//电梯状态
	ElevatorMove move;//电梯动作
	int StateCount;//结束当前动作时间
	Sqstack HS[5];//乘客栈
}*Elevator;
typedef struct {
	int up;
	int down;
}floorbutton;
void InitStack_sq(Sqstack& S);
bool Push_sq(Sqstack& S, info e);
bool Pop_sq(Sqstack& S, info& e);
int Length_sq(Sqstack& S);
bool EmptyStack(Sqstack& S);
void Initelevator(Elevator E[]);
bool TimeUp(Elevator e);
int Floorrequire(Elevator& E);
bool Stop(Elevator E);
bool CheckIn_Out(Elevator& E);
bool Controller(Elevator E[],int time);
void ChangeMove(Elevator& E,int k,int time);
int HighRequire(Elevator E);
int LowRequire(Elevator E);
bool InitQueue_L(LinkQueue& Q);
int QueueLength_L(LinkQueue Q);
bool EnQueue_L(LinkQueue& Q, info e);
bool DeQueue_L(LinkQueue& Q, info& e);
bool EmptyQueue_L(LinkQueue Q);
void DeleteQueue_L(LinkQueue& Q, Queueptr m);
int Rand(int l, int r);
info Generate();
bool HumanIn(Elevator& E, int k);
bool HumanOut(Elevator& E, int k);
bool HumanIn_Out(Elevator& E, int k);
bool Giveup(LinkQueue& Q, Elevator E[], int floor);