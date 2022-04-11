#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;       //char���� element������ �����ؼ� ���ڴ�.
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);           //queue�޸� ��ȯ
int isEmpty(QueueType *cQ);             //ť�� �������
int isFull(QueueType *cQ);              //ť�� �� á����
void enQueue(QueueType *cQ, element item);      //ť�� ��ҳֱ� (�ڿ��ִ°���)
void deQueue(QueueType *cQ, element* item);     //��� �����   (�տ�������)
void printQ(QueueType *cQ);             //ť���
void debugQ(QueueType *cQ);         //����Ʈ�� ���� ��ġ, ��� ���
element getElement();               //����Է¹ޱ�


int main(void)
{
	QueueType *cQ = createQueue();      //ť����
	element data;

	char command;       //��ɹ��� ����
	printf("[----- [������] [2021041021] -----]\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':     //ť�� ���� ����ְڴٰ� �ϸ�
			data = getElement();        //��Ҹ� �����ͼ� data�� �ְ�
			enQueue(cQ, data);          //q�� data�� ����
			break;
		case 'd': case 'D':     //d��
			deQueue(cQ,&data);  //delete���
			break;
		case 'p': case 'P':     //p��
			printQ(cQ);         //ť���
			break;
		case 'b': case 'B':     //b��
			debugQ(cQ);         //����Ʈ,������ġ�� ��ҵ� ���
			break;
		case 'q': case 'Q':     //q�� �ϰ͵����ϰ�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //q�̸� ��������������


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));        //�����Ҵ���
	cQ->front = 0;      //�����ʱ�ȭ
	cQ->rear = 0;
	return cQ;      //ť(�޸��ּ�)����
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;        //�ƹ��͵��Ȱ���Ű�� �׳� ����
    free(cQ);       //������Ű��������(���Ҵ�Ǿ�������)�޸𸮹�ȯ��
    return 1;       //����
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;        //�������ϳ� �޾Ƽ� ����
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){         //����Ʈ�� ����� ������(ť�� �������)
		printf("Circular Queue is empty!");
		return 1;   //1����
	}
	else return 0;  //�ƴϸ� 0����
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {       //(����+1)�̶� ����Ʈ�� ��ġ�� ������(����Ʈ�� ��� �Ⱦ� ����ť)
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;      //ť �� á���� �׳� ����
	else {      //�ƴϸ�
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     //��� 1�����ϰ�
		cQ->queue[cQ->rear] = item;     //��ҳֱ�
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;     //ť ��������� �׳� ����
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //����Ʈ�ٷδ�����(ù��°���)���� ����Ʈ�� ����Ű���ϰ�
		*item = cQ->queue[cQ->front];       //
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;     //ù��°�����ġ�ְ�
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;       //���������+1��ġ�ְ�

	printf("Circular Queue : [");

	i = first;      //i�� ù��°�����ġ�ְ�
	while(i != last){           //�����������ġ�� �ƴϸ�
		printf("%3c", cQ->queue[i]);        //��� ���
		i = (i+1)%MAX_QUEUE_SIZE;           //i�� ���� ����(������)����

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {            //����Ʈ ��ġ��
			printf("  [%d] = front\n", i);      //�� ��ġ�� ����Ʈ��� ���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);       //��ҵ鵵 ��¤�

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     //����Ʈ ��ġ�� ���� ��ġ�� ���
}

