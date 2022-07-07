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
		EnQueue_L(floordown[Human.Infloor], Human);  //将人放入相应楼层下楼队列
		floorbutton[Human.Infloor].down = 1;    //该楼层电梯向下按钮置1
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
			for (int i = 0; i < 5; i++) {   //找到需要前往楼层最低的电梯返回该层
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
		for (int i = 0; i < 5; i++) {   //找到需要前往楼层最低的电梯返回该层
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
			for (int i = 0; i < 5; i++) {   //找到需要前往楼层最高的电梯返回该层
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
			for (int i = 0; i < 5; i++) {   //找到需要前往楼层最高的电梯返回该层
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
bool TimeUp(Elevator e) //判断电梯周期时间是否到达
{
	if (e->State == Idle && e->Floor == 1)
		return false;
	else if (e->StateCount <= 0) {
			return true;
	}
	else return false;
}
int Floorrequire(Elevator& E) {   //附近楼层有无按下电梯按钮
	int i,j;
	i = E->Floor; j = E->Floor ;
	for ( j; j <= 4 ; j++) {
		if (j <= 4 && (button[j].down == 1 || button[j].up == 1)) {  //先上后下
			return j;
		}
	}
	for (i; i >= 0; i--) {
		if (i >= 0 && (button[i].down == 1 || button[i].up == 1)) {
			return i;
		}
	}
	return 10;//返回一个无效值
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

bool Stop(Elevator E) {       //判断电梯是否会在该层停下
	if (E->State == GoingUp) {
		if (button[E->Floor].up==1 || E->Callcar[E->Floor]==1) return true;
		if (E->Floor == 4)return true;  //最高层要停下
		else return false;
	}
	else if (E->State == GoingDown) {
		if (button[E->Floor].down == 1 || E->Callcar[E->Floor] == 1) return true;
		if (E->Floor == 0)return true;  //最低层要停下
		else return false;
	}
}
bool CheckIn_Out(Elevator& E) {
	if (E->State == GoingUp) {
		if (EmptyQueue_L(floorup[E->Floor])) {  //没人进电梯
			if (E->Callcar[E->Floor] == 0 || EmptyStack(E->HS[E->Floor])) return true;//没人出电梯
			else return false;
		}
		else return false;
	}
	else if (E->State == GoingDown) {
		if (EmptyQueue_L(floordown[E->Floor])) {  //没人进电梯
			if (E->Callcar[E->Floor] == 0 || EmptyStack(E->HS[E->Floor])) return true;//没人出电梯
			else return false;
		}
		else return false;
	}
	else return false;

}
bool Controller(Elevator E[],int time) {
	int i = 0;
	int floor;
	int floor0 = Floorrequire(E[0]);//附近按下按钮的楼层
	int floor1 = Floorrequire(E[1]);
	if (E[0]->move == Waiting && E[1]->move == Waiting) { //两个电梯都是等待动作，调用离乘客更近的电梯
		if (fabs(floor0 - E[0]->Floor) <= fabs(floor1 - E[1]->Floor)) {  //电梯0更近
			if (button[E[i]->Floor].up == 1) { //先上后下    本层有人要上电梯
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //防止另一台电梯也响应该指令
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//附近没人要坐电梯
				else {
					if (button[floor].up == 1) {// 先响应上行
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
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
			if (button[E[i]->Floor].up == 1) { //先上后下    本层有人要上电梯
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //防止另一台电梯也响应该指令
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//附近没人要坐电梯
				else {
					if (button[floor].up == 1) {// 先响应上行
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
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
		if (E[i]->move == Waiting) {        //E[0]为Waiting，E[1]不为Waiting                        //这种方式更加省电
			if (button[E[i]->Floor].up == 1) { //先上后下    本层有人要上电梯，且是上行
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //防止另一台电梯也响应该指令
			}
			else if (button[E[i]->Floor].down == 1) {//本层有人要上电梯，且是下行
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//附近没人要坐电梯
				else {
					if (button[floor].up==1&&(E[i+1]->State!=GoingUp||E[i+1]->Floor>floor)) {// 先响应上行另一台电梯目标楼层不包含需要搭乘电梯的乘客所在楼层（例如电梯从三楼前往一楼，乘客在四楼），或电梯运行的方向和乘客要前往的楼层的方向不一致（例如电梯从三楼前往一楼，乘客在二楼，但乘客目标楼层为四楼）
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1 && (E[i + 1]->State != GoingDown || E[i + 1]->Floor < floor)) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
		}
		i = 1;
		if (E[i]->move == Waiting) {//E[1]为Waiting，E[0]不为Waiting  
			if (button[E[i]->Floor].up == 1) { //先上后下    本层有人要上电梯
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //防止另一台电梯也响应该指令
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//附近没人要坐电梯
				else {
					if (button[floor].up == 1 && (E[i - 1]->State != GoingUp || E[i - 1]->Floor > floor)) {// 先响应上行
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1 && (E[i - 1]->State != GoingDown || E[i - 1]->Floor < floor)) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n", i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
				}
			}
		}
		/*for(i=0;i<2;i++){            //以人为本的电梯，可以节约等待时间
		if (E[i]->move == Waiting) {
			if (button[E[i]->Floor].up == 1) { //先上后下    本层有人要上电梯
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingUp;
				button[E[i]->Floor].up = -1;  //防止另一台电梯也响应该指令
			}
			else if (button[E[i]->Floor].down == 1) {
				E[i]->move = Opening;
				cout << "时间为" << time << "时:";
				printf("电梯%d正在开门\n", i);
				E[i]->StateCount = DoorTime;
				E[i]->State = GoingDown;
				button[E[i]->Floor].down = -1;
			}
			else {
				floor = Floorrequire(E[i]);
				if (floor < 0 || floor>4) return true;//附近没人要坐电梯
				else {
					if (button[floor].up==1) {// 先响应上行
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n",i);
							button[floor].up = -1;
							E[i]->Callcar[floor] = 1;
						}
					}
					else if (button[floor].down == 1) {
						if (floor > E[i]->Floor) {
							E[i]->move = Accelerate;
							E[i]->State = GoingUp;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速上行\n",i);
							button[floor].down = -1;
							E[i]->Callcar[floor] = 1;
						}
						else {
							E[i]->move = Accelerate;
							E[i]->State = GoingDown;
							E[i]->StateCount = AccTime;
							cout << "时间为" << time << "时:";
							printf("电梯%d开始加速下行\n",i);
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
		cout << "时间为" << time << "时:";
		printf("电梯%d开门成功\n",k);
		E->StateCount = TestTime;  //将状态时间设置为测试有无人进出电梯时间
	}
	else if (E->move == Opened) {
		if (CheckIn_Out(E) || E->Humman_num == 10) {
			E->move = Closing;
			cout << "时间为" << time << "时:";
			printf("电梯%d正在关门\n",k);
			E->StateCount = DoorTime;
		}
		else E->StateCount = TestTime;  //有人进出电梯则不关门
	}
	else if (E->move == Closing) {
		if (CheckIn_Out(E)) {  //没人进则把门关上
			E->move = Closed;
			cout << "时间为" << time << "时:";
			printf("电梯%d关门成功\n",k);
		}
		else {   //有人进再把门打开
			E->move = Opening;
			cout << "时间为" << time << "时:";
			printf("电梯%d重新开门\n",k);
			E->StateCount = DoorTime;
		}
	}
	else if (E->move == Closed) {       //判断电梯移动方向
		if (E->State == GoingUp) {
			if (button[E->Floor].up == -1) button[E->Floor].up = 0;//代表电梯已完成这个按钮
			if (E->Floor == 4) {
				E->move = Waiting;  //到达顶楼则停止
				E->State = Idle;
			}
			else {
				int j = E->Floor;
				for (j + 1; j <= 4; j++) {
					if (E->Callcar[j] == 1) { //判断是否仍需上行
						E->move = Accelerate;
						E->StateCount = AccTime;
						cout << "时间为" << time << "时:";
						printf("电梯%d开始加速上行\n",k);
						break;
					}
				}
				if (j > 4) {  //说明不需要向上行驶
					E->move = Waiting;
					E->State = Idle;
				}
			}
		}
		else if (E->State == GoingDown) {
			if (button[E->Floor].down == -1) button[E->Floor].down = 0;//代表电梯以完成这个按钮
			if (E->Floor == 0) { //到达底层则停止
				E->move = Waiting;
				E->State = Idle;
			}
			else {
				int j = E->Floor;
				for (j - 1; j >= 0; j--) {//判断是否仍需下行
					if (E->Callcar[j] == 1) {
						E->move = Accelerate;
						E->StateCount = AccTime;
						cout << "时间为" << time << "时:";
						printf("电梯%d开始加速下行\n",k);
						break;
					}
				}
				if (j <0) {  //说明不需要向下行驶
					E->move = Waiting;
					E->State = Idle;
				}
			}
		}
	}
	else if (E->move == Accelerate) {
		E->move = Moving;
		cout << "时间为" << time << "时:";
		printf("电梯%d开始匀速行驶\n", k);
		if (E->State == GoingUp)E->StateCount = UpTime;
		else if (E->State == GoingDown)E->StateCount = DownTime;
	}
	else if (E->move == Moving) {
		if (E->State == GoingUp) {
			E->Floor++;
			printf("电梯%d即将到达%d层\n",k, E->Floor);
			if (Stop(E)) { //说明电梯要在这层停下
				E->move =SlowDown;
				E->StateCount = UpSlow;
				cout << "时间为" << time << "时:";
				printf("电梯%d开始减速\n", k);
			}
			else {
				E->StateCount = UpTime;//电梯不需要在该层停下，继续上行
			}
		}
		else if (E->State == GoingDown) {
			E->Floor--;
			printf("电梯%d即将到达%d层\n", k, E->Floor);
			if (Stop(E)) { //说明电梯要在这层停下
				E->move = SlowDown;
				cout << "时间为" << time << "时:";
				printf("电梯%d开始减速\n", k);
				E->StateCount = DownSlow;
			}
			else {
				E->StateCount = DownTime;//电梯不需要在该层停下，继续下行
			}
		}
	}
	else if (E->move == SlowDown) {
		E->Callcar[E->Floor] = 0;    //电梯到达该层
		cout << "时间为" << time << "时:";
		printf("电梯%d停在%d层\n", k, E->Floor);
		if (E->State == GoingUp) {
			int flag = 1; //判断是否需要改变方向
			for (int i = E->Floor; i <= 4; i++) {
				if (E->Callcar[i]==1) {
					flag = 0;
					break;
				}
			}
			if (flag && (HighRequire (E)== -1)) {
				E->State = GoingDown; //更高的楼层没有需求，改变电梯运行方向
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
				E->State = GoingUp;//更低的楼层没有需要，改变电梯运行方向
			}
		}
		if (!EmptyQueue_L(floorup[E->Floor]) || !EmptyQueue_L(floordown[E->Floor]) || !EmptyStack(E->HS[E->Floor])) { //判断是否需要开门
			E->move = Opening;
			cout << "时间为" << time << "时:";
			printf("电梯%d正在开门\n", k);
			E->StateCount = DoorTime;
		}
		else {
			E->move = Waiting;
			E->State = Idle;
		}
	}
	else if (E->move == Waiting);//Waiting状态由Controller函数控制
}