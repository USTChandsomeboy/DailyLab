
#include"Elevator.h"
extern int IDnum;
extern floorbutton button[5];
extern LinkQueue floorup[5];
extern LinkQueue floordown[5];
bool InitQueue_L(LinkQueue& Q) {
	Q.front = Q.rear = (Queueptr)malloc(sizeof(LNode));
	if (!Q.front) {
		printf("内存分配错误");
		return false;
	}
	return true;
}
int QueueLength_L(LinkQueue Q) {
	int i = 0;
	Queueptr p = Q.front;
	while (p != Q.rear) {
		i++;
		p = p->next;
	}
	return i;
}
bool EnQueue_L(LinkQueue& Q, info e) {
	Queueptr p = (Queueptr)malloc(sizeof(LNode));
	if (!p)return false;
	p->Infloor = e.Infloor;
	p->Outfloor = e.Outfloor;
	p->InterTime = e.InterTime;
	p->GiveupTime = e.GiveupTime;
	p->ID = e.ID;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return true;
}
bool DeQueue_L(LinkQueue& Q, info& e) {
	if (Q.front == Q.rear)return false;
	Queueptr p = Q.front->next;
	if (Q.rear == p) {
		Q.rear = Q.front;
		e.Infloor = p->Infloor;
		e.Outfloor = p->Outfloor;
		e.InterTime = p->InterTime;
		e.GiveupTime = p->GiveupTime;
		e.ID = p->ID;
	}
	else {
		Q.front->next = p->next;
		e.Infloor = p->Infloor;
		e.Outfloor = p->Outfloor;
		e.InterTime = p->InterTime;
		e.GiveupTime = p->GiveupTime;
		e.ID = p->ID;
	}
	//free(p);
	return true;
}
bool EmptyQueue_L(LinkQueue Q) {
	if (Q.front == Q.rear) return true;
	else return false;
}
void DeleteQueue_L(LinkQueue& Q, Queueptr m) {
	Queueptr p = Q.front->next;
	Queueptr q;
	info e;
	e.Infloor = m->Infloor;
	e.Outfloor = m->Outfloor;
	e.InterTime = m->InterTime;
	e.GiveupTime = m->GiveupTime;
	e.ID = p->ID;

	if (p->ID==m->ID) DeQueue_L(Q, e);
	else {
		q = p;
		p = p->next;
		while (p !=Q.rear) {
			if (p->ID== m->ID) {
				q->next = p->next;
				break;
			}
			q = p;
			p = p->next;
		}
		if (m->ID == Q.rear->ID) {
			q->next = NULL;
			Q.rear = q;
		}
	}
}
int Rand(int l, int r) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(l, r);
	return distrib(gen);
}
info Generate() {
	info e;
	e.Infloor = Rand(0, 4);
	e.Outfloor = Rand(0, 4);
	e.ID = IDnum++;
	while(e.Outfloor == e.Infloor) {
		e.Outfloor = Rand(0, 4);
	}
	e.GiveupTime = Rand(1000, 1200);
	e.InterTime = Rand(120, 150);
	printf("一名ID为%d的乘客来到了%d楼，他将去%d楼\n", e.ID, e.Infloor, e.Outfloor);
	if (e.Infloor > e.Outfloor) {
		EnQueue_L(floordown[e.Infloor], e);
		if (button[e.Infloor].down ==0)button[e.Infloor].down = 1;

	}
	else {
		EnQueue_L(floorup[e.Infloor], e);
		if (button[e.Infloor].up ==0)button[e.Infloor].up = 1;
	}
	return e;
}
bool HumanIn(Elevator& E,int k) {
	info Hu;
	if (E->Humman_num == 10) return false;
	else {
		if (E->State == GoingUp) {
			if (!EmptyQueue_L(floorup[E->Floor])) {
				DeQueue_L(floorup[E->Floor], Hu);
				Push_sq(E->HS[Hu.Outfloor], Hu);
				E->Humman_num++;
				E->Callcar[Hu.Outfloor] = 1;
				cout <<"ID为" << Hu.ID << "的乘客进入电梯" << k;
				printf("\n");
				return true;
			}
			else return false;
		}
		else if (E->State == GoingDown) {
			if (!EmptyQueue_L(floordown[E->Floor])) {
				DeQueue_L(floordown[E->Floor], Hu);
				Push_sq(E->HS[Hu.Outfloor], Hu);
				E->Humman_num++;
				E->Callcar[Hu.Outfloor] = 1;
				cout << "ID为" << Hu.ID << "的乘客进入电梯" << k;
				printf("\n");
				return true;
			}
			else return false;
		}
		else if (E->State == Idle) return true;//
	}
}
bool HumanOut(Elevator& E,int k) {
	info Hu;
	if (!EmptyStack(E->HS[E->Floor])) {
		Pop_sq(E->HS[E->Floor], Hu);
		E->Humman_num--;
		printf("ID为%d的乘客出电梯%d\n", Hu.ID, k);
		return true;
	}
	else return false;
}
bool HumanIn_Out(Elevator& E, int k) {
	if (HumanOut(E, k) == false)
	{
		if (HumanIn(E, k) == false)
			return false;
	}
	return true;
}
bool Giveup(LinkQueue& Q, Elevator E[], int floor) {
	Queueptr p;
	p = Q.front->next;
	int flag = 0;
	while (p != NULL) {
		if (EmptyQueue_L(Q)) return false;
		else {
			if (p != NULL && p->GiveupTime < 0 && E[0]->Floor != floor && E[1]->Floor != floor) {//到达忍耐时间且没看到电梯
				printf("ID为%d的乘客放弃等待电梯\n", p->ID);
				DeleteQueue_L(Q, p);
				flag = 1;
			}
			else {
				p->GiveupTime--;
				flag = 0;
			}
		}
		//q = p;
		p = p->next;
		//if (flag == 1)free(q);
	}
	return true;
}
