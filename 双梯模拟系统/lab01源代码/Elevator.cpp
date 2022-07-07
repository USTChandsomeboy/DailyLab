#include"Elevator.h"
extern floorbutton button[5];
extern LinkQueue floorup[5]; extern LinkQueue floordown[5];
void InitStack_sq(Sqstack& S) {
	int msize = STACK_INIT_SIZE;
	S.elem = (info*)malloc(sizeof(info) * 10);
	S.stacksize = msize;
	S.top = -1;
}
bool Push_sq(Sqstack& S, info e) {
	S.elem[++S.top].GiveupTime = e.GiveupTime;
	S.elem[S.top].Infloor = e.Infloor;
	S.elem[S.top].InterTime = e.InterTime;
	S.elem[S.top].Outfloor = e.Outfloor;
	S.elem[S.top].ID = e.ID;
	return true;
}
bool Pop_sq(Sqstack& S, info& e) {
	e.GiveupTime = S.elem[S.top].GiveupTime;
	e.Infloor = S.elem[S.top].Infloor;
	e.ID = S.elem[S.top].ID;
	e.InterTime= S.elem[S.top].InterTime;
	e.Outfloor = S.elem[S.top].Outfloor;
	S.top--;
	return true;
}
int Length_sq(Sqstack& S) {
	return S.top + 1;
}
bool EmptyStack(Sqstack& S) {
	if (S.top == -1)return true;
	else return false;
}


/*void CallElevator(info Human, LinkQueue floorup[], LinkQueue floordown[], Elevator Elevator[], floorbutton floorbutton[]) {
	if (Human.Infloor - Human.Outfloor > 0) {
		EnQueue_L(floordown[Human.Infloor], Human);  //���˷�����Ӧ¥����¥����
		floorbutton[Human.Infloor].down = 1;    //��¥��������°�ť��1
	}
	else {
		EnQueue_L(floorup[Human.Infloor], Human);
		floorbutton[Human.Infloor].up = 1;
	}
	if (!strcmp(Elevator[0].State, "Idle") && !strcmp(Elevator[1].State, "Idle")) {
		if (fabs(Elevator[0].Floor - Human.Infloor) <= fabs(Elevator[1].Floor - Human.Infloor)) {
			Elevator[0].Callcar[Human.Infloor] = 1;
			if ((Elevator[0].Floor - Human.Infloor) > 0); //strcpy(Elevator[0].State, "Goingdown");
			else if ((Elevator[0].Floor - Human.Infloor) == 0);
			else;//strcpy(Elevator[0].State, "Goingup");
		}
		else {
			Elevator[1].Callcar[Human.Infloor] = 1;
			if ((Elevator[1].Floor - Human.Infloor) > 0);// strcpy(Elevator[1].State, "Goingdown");
			else if ((Elevator[1].Floor - Human.Infloor) == 0);
			else;// strcpy(Elevator[1].State, "Goingup");
		}
	}
	if (!strcmp(Elevator[0].State, "Idle") && !strcmp(Elevator[1].State, "Goingup")&&floorbutton[Human.Infloor].up) {
		if (Elevator[1].Floor < Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else if (Elevator[0].Floor > Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
			// strcpy(Elevator[0].State, "Goingdown");
		}
		else if (Elevator[0].Floor == Human.Infloor) Elevator[0].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[0].State, "Goingup");
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Idle") && !strcmp(Elevator[1].State, "Goingup") && floorbutton[Human.Infloor].down) {
		if (Elevator[0].Floor > Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[0].State, "Goingdown");
		}
		else if (Elevator[0].Floor == Human.Infloor) Elevator[0].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[0].State, "Goingup");
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Idle") && !strcmp(Elevator[1].State, "Goingdown")&& floorbutton[Human.Infloor].down ) {
		if (Elevator[1].Floor > Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else if (Elevator[0].Floor > Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[0].State, "Goingdown");
		}
		else if (Elevator[0].Floor == Human.Infloor)Elevator[0].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[0].State, "Goingup");
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Idle") && !strcmp(Elevator[1].State, "Goingdown") && floorbutton[Human.Infloor].up ) {
		if (Elevator[0].Floor > Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[0].State, "Goingdown");
		}
		else if (Elevator[0].Floor == Human.Infloor)Elevator[0].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[0].State, "Goingup");
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Idle") && floorbutton[Human.Infloor].up ) {
		if (Elevator[0].Floor < Human.Infloor) Elevator[0].Callcar[Human.Infloor] = 1;
		else if (Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[1].State, "Goingdown");
		}
		else if (Elevator[1].Floor == Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[1].State, "Goingup");
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Idle") && floorbutton[Human.Infloor].down) {
		if (Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[1].State, "Goingdown");
		}
		else if (Elevator[1].Floor == Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[1].State, "Goingup");
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Idle") && floorbutton[Human.Infloor].down) {
		if (Elevator[0].Floor > Human.Infloor) Elevator[0].Callcar[Human.Infloor] = 1;
		else if (Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[1].State, "Goingdown");
		}
		else if (Elevator[1].Floor == Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[1].State, "Goingup");
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Idle") && floorbutton[Human.Infloor].up) {
		if (Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
			//strcpy(Elevator[1].State, "Goingdown");
		}
		else if (Elevator[1].Floor == Human.Infloor) Elevator[1].Callcar[Human.Infloor] = 1;
		else {
			//strcpy(Elevator[1].State, "Goingup");
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Goingup")&&floorbutton[Human.Infloor].up) {
		if (Elevator[0].Floor >= Human.Infloor && Elevator[1].Floor >=Human.Infloor) {
			int max1 = 0, max2 = 0;
			for (int i = 0; i < 5; i++) {   //�ҵ���Ҫǰ��¥����͵ĵ��ݷ��ظò�
				if (Elevator[0].Callcar[i] == 1)max1 = i;
				if (Elevator[1].Callcar[i] == 1)max2 = i;
			}
			if (max1 <= max2) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
		else if (Elevator[0].Floor < Human.Infloor && Elevator[1].Floor >= Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
		else if (Elevator[0].Floor >= Human.Infloor && Elevator[1].Floor < Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
		else if(Elevator[0].Floor < Human.Infloor && Elevator[1].Floor < Human.Infloor) {
			if(Elevator[0].Floor>=Elevator[1].Floor) Elevator[0].Callcar[Human.Infloor] = 1;
			else Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Goingup") && floorbutton[Human.Infloor].down) {
		int max1 = 0, max2 = 0;
		for (int i = 0; i < 5; i++) {   //�ҵ���Ҫǰ��¥����͵ĵ��ݷ��ظò�
			if (Elevator[0].Callcar[i] == 1)max1 = i;
			if (Elevator[1].Callcar[i] == 1)max2 = i;
		}
		if (max1 <= max2) {
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
		else {
			Elevator[1].Callcar[Human.Infloor] = 1;
		}	
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Goingdown") && floorbutton[Human.Infloor].up) {
		int max1 = 0, max2 = 0;
		if (Elevator[0].Floor < Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (Elevator[0].Callcar[i] == 1)max1 = i;
				if (Elevator[1].Callcar[4-i] == 1)max2 = 4-i;
			}
			if (fabs(max1-Human.Infloor) <= fabs(max2 - Human.Infloor)) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
	}
	if (!strcmp(Elevator[0].State, "Goingup") && !strcmp(Elevator[1].State, "Goingdown") && floorbutton[Human.Infloor].down) {
		int max1 = 0, max2 = 0;
		if (Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (Elevator[0].Callcar[i] == 1)max1 = i;
				if (Elevator[1].Callcar[4 - i] == 1)max2 = 4 - i;
			}
			if (fabs(max1 - Human.Infloor) <= fabs(max2 - Human.Infloor)) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Goingup") && floorbutton[Human.Infloor].up) {
		int max1 = 0, max2 = 0;
		if (Elevator[1].Floor < Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (Elevator[0].Callcar[4-i] == 1)max1 = 4-i;
				if (Elevator[1].Callcar[i] == 1)max2 = i;
			}
			if (fabs(max1 - Human.Infloor) <= fabs(max2 - Human.Infloor)) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Goingup") && floorbutton[Human.Infloor].down) {
		int max1 = 0, max2 = 0;
		if (Elevator[0].Floor > Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
		else {
			for (int i = 0; i < 5; i++) {
				if (Elevator[0].Callcar[4 - i] == 1)max1 =4 - i;
				if (Elevator[1].Callcar[i] == 1)max2 = i;
			}
			if (fabs(max1 - Human.Infloor) <= fabs(max2 - Human.Infloor)) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Goingdown") && floorbutton[Human.Infloor].down) {
		if (Elevator[0].Floor <= Human.Infloor && Elevator[1].Floor <= Human.Infloor) {
			int max1 = 0, max2 = 0;
			for (int i = 0; i < 5; i++) {   //�ҵ���Ҫǰ��¥����ߵĵ��ݷ��ظò�
				if (Elevator[0].Callcar[4-i] == 1)max1 = 4-i;
				if (Elevator[1].Callcar[4-i] == 1)max2 =4-i;
			}
			if (max1 >= max2) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
		}
		else if (Elevator[0].Floor <= Human.Infloor && Elevator[1].Floor > Human.Infloor) {
			Elevator[1].Callcar[Human.Infloor] = 1;
		}
		else if (Elevator[0].Floor > Human.Infloor && Elevator[1].Floor <= Human.Infloor) {
			Elevator[0].Callcar[Human.Infloor] = 1;
		}
		else if (Elevator[0].Floor > Human.Infloor && Elevator[1].Floor > Human.Infloor) {
			if (Elevator[0].Floor <= Elevator[1].Floor) Elevator[0].Callcar[Human.Infloor] = 1;
			else Elevator[1].Callcar[Human.Infloor] = 1;
		}
	}
	if (!strcmp(Elevator[0].State, "Goingdown") && !strcmp(Elevator[1].State, "Goingdown") && floorbutton[Human.Infloor].up) {
			int max1 = 0, max2 = 0;
			for (int i = 0; i < 5; i++) {   //�ҵ���Ҫǰ��¥����ߵĵ��ݷ��ظò�
				if (Elevator[0].Callcar[4 - i] == 1)max1 = 4 - i;
				if (Elevator[1].Callcar[4 - i] == 1)max2 = 4 - i;
			}
			if (max1 >= max2) {
				Elevator[0].Callcar[Human.Infloor] = 1;
			}
			else {
				Elevator[1].Callcar[Human.Infloor] = 1;
			}
	}
}*/

void Initelevator(Elevator E[]) {
	int j;
	for (int i = 0; i < 5; i++) {
		button[i].down = 0;
		button[i].up = 0;
	}
	
	for (j = 0; j <2; j++) {
		E[j] = (Elevator)malloc(sizeof(ElevatorNode));
		for (int i = 0; i < 5; i++) {
			E[j]->Callcar[i] = 0;
			InitStack_sq(E[j]->HS[i]);
		}
		E[j]->State = Idle;
		E[j]->StateCount = 0;
		E[j]->move = Waiting;
		E[j]->Floor = 1;
		E[j]->Humman_num = 0;
	}
	E[1]->Floor = 3;
}
bool TimeUp(Elevator e) //�жϵ�������ʱ���Ƿ񵽴�
{
	if (e->State == Idle && e->Floor == 1)
		return false;
	else if (e->StateCount <= 0) {
			return true;
	}
	else return false;
}
int Floorrequire(Elevator& E) {   //����¥�����ް��µ��ݰ�ť
	int i,j;
	i = E->Floor; j = E->Floor ;
	for ( j; j <= 4 ; j++) {
		if (j <= 4 && (button[j].down == 1 || button[j].up == 1)) {  //���Ϻ���
			return j;
		}
	}
	for (i; i >= 0; i--) {
		if (i >= 0 && (button[i].down == 1 || button[i].up == 1)) {
			return i;
		}
	}
	return 10;//����һ����Чֵ
}
int HighRequire(Elevator E) {
	for (int i = E->Floor; i <= 4; i++) {
		if (button[i].up) return i;
	}
	return -1;
}
int LowRequire(Elevator E) {
	for (int i = E->Floor; i >= 0; i--) {
		if (button[i].down)return i;
	}
	return - 1;
}

bool Stop(Elevator E) {       //�жϵ����Ƿ���ڸò�ͣ��
	if (E->State == GoingUp) {
		if (button[E->Floor].up==1 || E->Callcar[E->Floor]==1) return true;
		if (E->Floor == 4)return true;  //��߲�Ҫͣ��
		else return false;
	}
	else if (E->State == GoingDown) {
		if (button[E->Floor].down == 1 || E->Callcar[E->Floor] == 1) return true;
		if (E->Floor == 0)return true;  //��Ͳ�Ҫͣ��
		else return false;
	}
}
bool CheckIn_Out(Elevator& E) {
	if (E->State == GoingUp) {
		if (EmptyQueue_L(floorup[E->Floor])) {  //û�˽�����
			if (E->Callcar[E->Floor] == 0 || EmptyStack(E->HS[E->Floor])) return true;//û�˳�����
			else return false;
		}
		else return false;
	}
	else if (E->State == GoingDown) {
		if (EmptyQueue_L(floordown[E->Floor])) {  //û�˽�����
			if (E->Callcar[E->Floor] == 0 || EmptyStack(E->HS[E->Floor])) return true;//û�˳�����
			else return false;
		}
		else return false;
	}
	else return false;

}
bool Controller(Elevator E[],int time) {
	int i = 0;
	int floor;
	int floor0 = Floorrequire(E[0]);//�������°�ť��¥��
	int floor1 = Floorrequire(E[1]);
	if (E[0]->move == Waiting && E[1]->move == Waiting) { //�������ݶ��ǵȴ�������������˿͸����ĵ���
		if (fabs(floor0 - E[0]->Floor) <= fabs(floor1 - E[1]->Floor)) {  //����0����
			if (button[E[i]->Floor].up == 1) { //���Ϻ���    ��������Ҫ�ϵ���
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //��ֹ��һ̨����Ҳ��Ӧ��ָ��
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//����û��Ҫ������
				else {
					if (button[floor].up == 1) {// ����Ӧ����
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
			return true;
		}
		else {
			i = 1;
			if (button[E[i]->Floor].up == 1) { //���Ϻ���    ��������Ҫ�ϵ���
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //��ֹ��һ̨����Ҳ��Ӧ��ָ��
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//����û��Ҫ������
				else {
					if (button[floor].up == 1) {// ����Ӧ����
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
			return true;
		}
		return true;
	}
	i = 0;
		if (E[i]->move == Waiting) {        //E[0]ΪWaiting��E[1]��ΪWaiting                        //���ַ�ʽ����ʡ��
			if (button[E[i]->Floor].up == 1) { //���Ϻ���    ��������Ҫ�ϵ��ݣ���������
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //��ֹ��һ̨����Ҳ��Ӧ��ָ��
			}
			else if (button[E[i]->Floor].down == 1) {//��������Ҫ�ϵ��ݣ���������
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//����û��Ҫ������
				else {
					if (button[floor].up==1&&(E[i+1]->State!=GoingUp||E[i+1]->Floor>floor)) {// ����Ӧ������һ̨����Ŀ��¥�㲻������Ҫ��˵��ݵĳ˿�����¥�㣨������ݴ���¥ǰ��һ¥���˿�����¥������������еķ���ͳ˿�Ҫǰ����¥��ķ���һ�£�������ݴ���¥ǰ��һ¥���˿��ڶ�¥�����˿�Ŀ��¥��Ϊ��¥��
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1 && (E[i + 1]->State != GoingDown || E[i + 1]->Floor < floor)) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
		}
		i = 1;
		if (E[i]->move == Waiting) {//E[1]ΪWaiting��E[0]��ΪWaiting  
			if (button[E[i]->Floor].up == 1) { //���Ϻ���    ��������Ҫ�ϵ���
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //��ֹ��һ̨����Ҳ��Ӧ��ָ��
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//����û��Ҫ������
				else {
					if (button[floor].up == 1 && (E[i - 1]->State != GoingUp || E[i - 1]->Floor > floor)) {// ����Ӧ����
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1 && (E[i - 1]->State != GoingDown || E[i - 1]->Floor < floor)) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
		}
		/*for(i=0;i<2;i++){            //����Ϊ���ĵ��ݣ����Խ�Լ�ȴ�ʱ��
		if (E[i]->move == Waiting) {
			if (button[E[i]->Floor].up == 1) { //���Ϻ���    ��������Ҫ�ϵ���
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //��ֹ��һ̨����Ҳ��Ӧ��ָ��
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d���ڿ���\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//����û��Ҫ������
				else {
					if (button[floor].up==1) {// ����Ӧ����
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "ʱ��Ϊ" << time << "ʱ:";
							printf("����%d��ʼ��������\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
		}
		}*/
}
void ChangeMove(Elevator& E,int k,int time) {
	if (E->move == Opening) {
		E->move = Opened;
		cout << "ʱ��Ϊ" << time << "ʱ:";
		printf("����%d���ųɹ�\n",k);
		E->StateCount = TestTime;  //��״̬ʱ������Ϊ���������˽�������ʱ��
	}
	else if (E->move == Opened) {
		if (CheckIn_Out(E) || E->Humman_num == 10) {
			E->move = Closing;
			cout << "ʱ��Ϊ" << time << "ʱ:";
			printf("����%d���ڹ���\n",k);
			E->StateCount = DoorTime;
		}
		else E->StateCount = TestTime;  //���˽��������򲻹���
	}
	else if (E->move == Closing) {
		if (CheckIn_Out(E)) {  //û�˽�����Ź���
			E->move = Closed;
			cout << "ʱ��Ϊ" << time << "ʱ:";
			printf("����%d���ųɹ�\n",k);
		}
		else {   //���˽��ٰ��Ŵ�
			E->move = Opening;
			cout << "ʱ��Ϊ" << time << "ʱ:";
			printf("����%d���¿���\n",k);
			E->StateCount = DoorTime;
		}
	}
	else if (E->move == Closed) {       //�жϵ����ƶ�����
		if (E->State == GoingUp) {
			if (button[E->Floor].up == -1) button[E->Floor].up = 0;//�����������������ť
			if (E->Floor == 4) {
				E->move = Waiting;  //���ﶥ¥��ֹͣ
				E->State = Idle;
			}
			else {
				int j = E->Floor;
				for (j + 1; j <= 4; j++) {
					if (E->Callcar[j] == 1) { //�ж��Ƿ���������
						E->move = Accelerate;
						E->StateCount = AccTime;
						cout << "ʱ��Ϊ" << time << "ʱ:";
						printf("����%d��ʼ��������\n",k);
						break;
					}
				}
				if (j > 4) {  //˵������Ҫ������ʻ
					E->move = Waiting;
					E->State = Idle;
				}
			}
		}
		else if (E->State == GoingDown) {
			if (button[E->Floor].down == -1) button[E->Floor].down = 0;//�����������������ť
			if (E->Floor == 0) { //����ײ���ֹͣ
				E->move = Waiting;
				E->State = Idle;
			}
			else {
				int j = E->Floor;
				for (j - 1; j >= 0; j--) {//�ж��Ƿ���������
					if (E->Callcar[j] == 1) {
						E->move = Accelerate;
						E->StateCount = AccTime;
						cout << "ʱ��Ϊ" << time << "ʱ:";
						printf("����%d��ʼ��������\n",k);
						break;
					}
				}
				if (j <0) {  //˵������Ҫ������ʻ
					E->move = Waiting;
					E->State = Idle;
				}
			}
		}
	}
	else if (E->move == Accelerate) {
		E->move = Moving;
		cout << "ʱ��Ϊ" << time << "ʱ:";
		printf("����%d��ʼ������ʻ\n", k);
		if (E->State == GoingUp)E->StateCount = UpTime;
		else if (E->State == GoingDown)E->StateCount = DownTime;
	}
	else if (E->move == Moving) {
		if (E->State == GoingUp) {
			E->Floor++;
			printf("����%d��������%d��\n",k, E->Floor);
			if (Stop(E)) { //˵������Ҫ�����ͣ��
				E->move =SlowDown;
				E->StateCount = UpSlow;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d��ʼ����\n", k);
			}
			else {
				E->StateCount = UpTime;//���ݲ���Ҫ�ڸò�ͣ�£���������
			}
		}
		else if (E->State == GoingDown) {
			E->Floor--;
			printf("����%d��������%d��\n", k, E->Floor);
			if (Stop(E)) { //˵������Ҫ�����ͣ��
				E->move = SlowDown;
				cout << "ʱ��Ϊ" << time << "ʱ:";
				printf("����%d��ʼ����\n", k);
				E->StateCount = DownSlow;
			}
			else {
				E->StateCount = DownTime;//���ݲ���Ҫ�ڸò�ͣ�£���������
			}
		}
	}
	else if (E->move == SlowDown) {
		E->Callcar[E->Floor] = 0;    //���ݵ���ò�
		cout << "ʱ��Ϊ" << time << "ʱ:";
		printf("����%dͣ��%d��\n", k, E->Floor);
		if (E->State == GoingUp) {
			int flag = 1; //�ж��Ƿ���Ҫ�ı䷽��
			for (int i = E->Floor; i <= 4; i++) {
				if (E->Callcar[i]==1) {
					flag = 0;
					break;
				}
			}
			if (flag && (HighRequire (E)== -1)) {
				E->State = GoingDown; //���ߵ�¥��û�����󣬸ı�������з���
			}
		}
		else if (E->State == GoingDown) {
			int flag = 1;
			for (int i = E->Floor; i >= 0; i--) {
				if (E->Callcar[i]) {
					flag = 0;
					break;
				}
			}
			if (flag && (LowRequire(E) == -1)) {
				E->State = GoingUp;//���͵�¥��û����Ҫ���ı�������з���
			}
		}
		if (!EmptyQueue_L(floorup[E->Floor]) || !EmptyQueue_L(floordown[E->Floor]) || !EmptyStack(E->HS[E->Floor])) { //�ж��Ƿ���Ҫ����
			E->move = Opening;
			cout << "ʱ��Ϊ" << time << "ʱ:";
			printf("����%d���ڿ���\n", k);
			E->StateCount = DoorTime;
		}
		else {
			E->move = Waiting;
			E->State = Idle;
		}
	}
	else if (E->move == Waiting);//Waiting״̬��Controller��������
}