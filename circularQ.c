#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;       //char형을 element형으로 정의해서 쓰겠다.
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);           //queue메모리 반환
int isEmpty(QueueType *cQ);             //큐가 비었는지
int isFull(QueueType *cQ);              //큐가 다 찼는지
void enQueue(QueueType *cQ, element item);      //큐에 요소넣기 (뒤에넣는거임)
void deQueue(QueueType *cQ, element* item);     //요소 지우기   (앞에걸지움)
void printQ(QueueType *cQ);             //큐출력
void debugQ(QueueType *cQ);         //프론트랑 리어 위치, 요소 출력
element getElement();               //요소입력받기


int main(void)
{
	QueueType *cQ = createQueue();      //큐생성
	element data;

	char command;       //명령받을 변수
	printf("[----- [곽민정] [2021041021] -----]\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':     //큐에 값을 집어넣겠다고 하면
			data = getElement();        //요소를 가져와서 data에 넣고
			enQueue(cQ, data);          //q와 data를 보냄
			break;
		case 'd': case 'D':     //d면
			deQueue(cQ,&data);  //delete요소
			break;
		case 'p': case 'P':     //p면
			printQ(cQ);         //큐출력
			break;
		case 'b': case 'B':     //b는
			debugQ(cQ);         //프론트,리어위치랑 요소들 출력
			break;
		case 'q': case 'Q':     //q는 암것도안하고
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //q이면 루프빠져나가기


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));        //동적할당후
	cQ->front = 0;      //변수초기화
	cQ->rear = 0;
	return cQ;      //큐(메모리주소)리턴
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;        //아무것도안가리키면 그냥 리턴
    free(cQ);       //뭐가리키고있으면(힙할당되어있으면)메모리반환후
    return 1;       //리턴
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;        //문자형하나 받아서 리턴
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){         //프론트랑 리어랑 같으면(큐가 비었으면)
		printf("Circular Queue is empty!");
		return 1;   //1리턴
	}
	else return 0;  //아니면 0리턴
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {       //(리어+1)이랑 프론트랑 위치가 같으면(프론트는 요소 안씀 원형큐)
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;      //큐 다 찼으면 그냥 리턴
	else {      //아니면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //리어를 1증가하고
		cQ->queue[cQ->rear] = item;     //요소넣기
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;     //큐 비어있으면 그냥 리턴
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //프론트바로다음거(첫번째요소)값을 프론트가 가리키게하고
		*item = cQ->queue[cQ->front];       //
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;     //첫번째요소위치넣고
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;       //마지막요소+1위치넣고

	printf("Circular Queue : [");

	i = first;      //i가 첫번째요소위치넣고
	while(i != last){           //마지막요소위치가 아니면
		printf("%3c", cQ->queue[i]);        //요소 출력
		i = (i+1)%MAX_QUEUE_SIZE;           //i값 증가 모듈로(나머지)연산

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {            //프론트 위치면
			printf("  [%d] = front\n", i);      //이 위치는 프론트라고 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);       //요소들도 출력ㄱ

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     //프론트 위치랑 리어 위치를 출력
}

