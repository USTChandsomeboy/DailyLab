#include"Human.h"
#include"Elevator.h"
int IDnum = 0;
floorbutton button[5];
LinkQueue floorup[5];
LinkQueue floordown[5];
int main() {
	int flag1 = 0;
	clock_t start, stop; //clock_t为clock()函数返回的变量类型
	clock_t stop1;
	for (int i = 0; i < 5; i++) {
		InitQueue_L(floorup[i]);
		InitQueue_L(floordown[i]);
	}
	Elevator E[2];
	Initelevator(E);
	info Human[300];
	start = clock();
	int i = 0;
	int t[2];
	t[0] = 0; t[1] = 0;
	Human[i] = Generate();   //出现乘客
	int TotalTime = 0;
	int ReturnTime[2];
	ReturnTime[0] = 0;
	ReturnTime[1] = 0;
	while (TotalTime++ < 5000) {
		if (Human[i].InterTime == 0) {   //间隔时间到，新乘客出现
			i++;
			cout << "时间为" << TotalTime << "时:";
			Human[i] = Generate();
		}
		else Human[i].InterTime--;
		for (int j = 0; j < 5; j++) {// 判断是否有乘客放弃乘电梯
			Giveup(floorup[j], E, j);
			Giveup(floordown[j], E, j);
		}
		Controller(E,TotalTime);
		for (int j = 0; j < 2; j++) {
			if (E[j]->move == Opened) {   //如果电梯是开门，则让乘客进出
				if (t[j] == WalkTime) {
					t[j] = 0;
					HumanOut(E[j], j);
					HumanIn(E[j], j);
				}
				else t[j]++;
			}
			if (TimeUp(E[j])==true) {  //上一个状态完成所需的时间到了，需改变状态
				//cout << "时间为"<<TotalTime << ":";
				ChangeMove(E[j],j,TotalTime);
			}
			else {
				E[j]->StateCount--;
			}
			if (E[j]->move == Waiting) {
				ReturnTime[j]++;
				//if(j==0)cout << '1';
				if (ReturnTime[j] == WaitTime) {   //电梯原地等待时间到达300返回初始状态
					if (j == 0) {    //电梯0回到1楼
						if (E[j]->Floor != 1) {
							cout << "时间为" << TotalTime << "时:";
							printf("电梯%d等待时间过长，返回初始状态\n",j);
							flag1 = 1;
							if (E[j]->Floor > 1) {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("电梯%d开始加速下行\n", j);
								E[j]->State = GoingDown;
								E[j]->Callcar[1] = 1;
							}
							else {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("电梯%d开始加速上行\n", j);
								E[j]->State = GoingUp;
								E[j]->Callcar[1] = 1;
							}
						}
					}
					else {  //电梯1回到3楼
						if (E[j]->Floor != 3) {
							flag1 = 1;
							cout << "时间为" << TotalTime << "时:";
							printf("电梯%d等待时间过长，返回初始状态\n", j);
							if (E[j]->Floor > 3) {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("电梯%d开始加速下行\n", j);
								E[j]->State = GoingDown;
								E[j]->Callcar[3] = 1;
							}
							else {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("电梯%d开始加速上行\n", j);
								E[j]->State = GoingUp;
								E[j]->Callcar[3] = 1;
							}
						}
					}
				}
			}
			else ReturnTime[j] = 0;
		}
		if (TotalTime % 10 == 0)
		{
			//printf("时间为： %d\n", TotalTime);
		}
		//Sleep(90);
	}
	printf("达到预设最大时间，销毁电梯，杀掉人");
	return 0;
}