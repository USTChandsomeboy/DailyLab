#include"Human.h"
#include"Elevator.h"
int IDnum = 0;
floorbutton button[5];
LinkQueue floorup[5];
LinkQueue floordown[5];
int main() {
	int flag1 = 0;
	clock_t start, stop; //clock_tΪclock()�������صı�������
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
	Human[i] = Generate();   //���ֳ˿�
	int TotalTime = 0;
	int ReturnTime[2];
	ReturnTime[0] = 0;
	ReturnTime[1] = 0;
	while (TotalTime++ < 5000) {
		if (Human[i].InterTime == 0) {   //���ʱ�䵽���³˿ͳ���
			i++;
			cout << "ʱ��Ϊ" << TotalTime << "ʱ:";
			Human[i] = Generate();
		}
		else Human[i].InterTime--;
		for (int j = 0; j < 5; j++) {// �ж��Ƿ��г˿ͷ����˵���
			Giveup(floorup[j], E, j);
			Giveup(floordown[j], E, j);
		}
		Controller(E,TotalTime);
		for (int j = 0; j < 2; j++) {
			if (E[j]->move == Opened) {   //��������ǿ��ţ����ó˿ͽ���
				if (t[j] == WalkTime) {
					t[j] = 0;
					HumanOut(E[j], j);
					HumanIn(E[j], j);
				}
				else t[j]++;
			}
			if (TimeUp(E[j])==true) {  //��һ��״̬��������ʱ�䵽�ˣ���ı�״̬
				//cout << "ʱ��Ϊ"<<TotalTime << ":";
				ChangeMove(E[j],j,TotalTime);
			}
			else {
				E[j]->StateCount--;
			}
			if (E[j]->move == Waiting) {
				ReturnTime[j]++;
				//if(j==0)cout << '1';
				if (ReturnTime[j] == WaitTime) {   //����ԭ�صȴ�ʱ�䵽��300���س�ʼ״̬
					if (j == 0) {    //����0�ص�1¥
						if (E[j]->Floor != 1) {
							cout << "ʱ��Ϊ" << TotalTime << "ʱ:";
							printf("����%d�ȴ�ʱ����������س�ʼ״̬\n",j);
							flag1 = 1;
							if (E[j]->Floor > 1) {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("����%d��ʼ��������\n", j);
								E[j]->State = GoingDown;
								E[j]->Callcar[1] = 1;
							}
							else {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("����%d��ʼ��������\n", j);
								E[j]->State = GoingUp;
								E[j]->Callcar[1] = 1;
							}
						}
					}
					else {  //����1�ص�3¥
						if (E[j]->Floor != 3) {
							flag1 = 1;
							cout << "ʱ��Ϊ" << TotalTime << "ʱ:";
							printf("����%d�ȴ�ʱ����������س�ʼ״̬\n", j);
							if (E[j]->Floor > 3) {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("����%d��ʼ��������\n", j);
								E[j]->State = GoingDown;
								E[j]->Callcar[3] = 1;
							}
							else {
								E[j]->move = Accelerate;
								E[j]->StateCount = AccTime;
								printf("����%d��ʼ��������\n", j);
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
			//printf("ʱ��Ϊ�� %d\n", TotalTime);
		}
		//Sleep(90);
	}
	printf("�ﵽԤ�����ʱ�䣬���ٵ��ݣ�ɱ����");
	return 0;
}