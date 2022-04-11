//����ǥ��
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum{       //������ ����
	lparen = 0,         //0�� �հ�ȣ
	rparen = 9,         //9�� �ް�ȣ
	times = 7,          //7�� ���ϱ�
	divide = 6,         //6�� ������
	plus = 5,           //5�� ���ϱ�
	minus = 4,          //2�� ����
	operand = 1         //1�� �� ���ڵ�(�ǿ�����)
} precedence;
//���ϰ� �̸����� ������ �̷����� ���ڰ� ������ �켱���� �� ����
char infixExp[MAX_EXPRESSION_SIZE];     //������ �����Ұ�
char postfixExp[MAX_EXPRESSION_SIZE];   //������ �����Ұ�
char postfixStack[MAX_STACK_SIZE];      //������ ����
int evalStack[MAX_STACK_SIZE];          //������ ����

int postfixStackTop = -1;       //�����Ľ���ž
int evalStackTop = -1;          //���Ѱ�����ž

int evalResult = 0;             //���

void postfixPush(char x);		//��������Ľ��ÿ� xǪ��
char postfixPop();				//�������꽺����
void evalPush(int x);			//�������xǪ��
int evalPop();					//���������
void getInfix();				//�������Է¹ޱ�
precedence getToken(char symbol);	//���ڿ� �´� enum����
precedence getPriority(char x);		//�켱�������ϱ�
void charCat(char* c);				//�����̾���̱�
void toPostfix();					//�������� ���������� �ٲٱ�
void debug();						//����, ��� ���
void reset();						//�� �ʱ�ȭ
void evaluation();      //������ϱ�

int main()
{
	char command;
    printf("[----- [������] [2021041021] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);		//��ɾ��Է�

		switch(command) {
		case 'i': case 'I':     //i��
			getInfix();         //�������Է¹ޱ�
			break;
		case 'p': case 'P':     //p��
			toPostfix();        //���������κ�ȯ
			break;
		case 'e': case 'E':		//e��
			evaluation();		//��������ϱ�
			break;
		case 'd': case 'D':		//d��
			debug();			//���ð�, ���Ѱ� ���
			break;
		case 'r': case 'R':		//r�̸�
			reset();			//����
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q�� �����������ͼ� ����

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;        //�������ÿ� x�ֱ�
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)       //��������� �θ���
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];        //ž�� �ִ°Ż��� ž1���̱�
    }
    return x;       //���� �� ����
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;		//���Ѱ����ÿ� xǪ��
}

int evalPop()
{
    if(evalStackTop == -1)      //���������
        return -1;              //-1����
    else
        return evalStack[evalStackTop--];       //�ƴϸ� ž���ִ°� �����ϰ� ž�� �ϳ� ���̱�
}



void getInfix()
{
    printf("Type the expression >>> ");     
    scanf("%s",infixExp);       //���������� �Է��� ����
}

precedence getToken(char symbol)
{
	switch(symbol) {        //�� �����ڿ� �����ϴ� enum ����
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;       //�پƴϸ� �����ڶ�� ����
	}
}

precedence getPriority(char x)
{
	return getToken(x);     //x�� �켱�������� �޾Ƽ� ����
}


void charCat(char* c)
{
	if (postfixExp == '\0')     //postfixExp�� ���������
		strncpy(postfixExp, c, 1);      //�����Ŀ����ڿ� c�� ī��
	else
		strncat(postfixExp, c, 1);      //�����Ŀ����ڿ� c�� �̾���̱�
}


void toPostfix()
{
	char *exp = infixExp;       //�������� exp�� �ֱ�
	char x;     //�����ϳ������� ����
	while(*exp != '\0')     //exp�� ������� ���� ����
	{
		if(getPriority(*exp) == operand)        //�ǿ�����(����)�̸�
		{
			x = *exp;       //exp�� ����Ű�°��� x�� �ְ�
        	charCat(&x);    //x�� ��������Ŀ� �̾���̱�
		}
        else if(getPriority(*exp) == lparen) {      //�հ�ȣ��

        	postfixPush(*exp);      //�������꽺�ÿ� Ǫ��
        }
        else if(getPriority(*exp) == rparen)        //�ް�ȣ��
        {
        	while((x = postfixPop()) != '(') {      //�հ�ȣ�� ���� ������
        		charCat(&x);        //��ȣ�ӿ��ִ°� �� ��������Ŀ� �̾� ���̱�
        	}
        }
        else        //���ڵ� ��ȣ�� �ƴϸ�
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))      //�������꽺��ž���ִ� �ͺ��� �켱������ �۴ٸ�
            {
            	x = postfixPop();       //�� ���� �������꽺���� ž���� ���ϰ�
            	charCat(&x);            //��������Ŀ� �̾���̱�
            }
            postfixPush(*exp);          //�׸��� ���簪�� �������꽺�ÿ� �ֱ�
        }
        exp++;      //��������
	}

    while(postfixStackTop != -1)        //�������꽺��ž�� -1�� �ƴϸ� �������������(�����ִ°��� ��)
    {
    	x = postfixPop();           //�������꽺�ÿ��� ���ϰ� ���� ����
    	charCat(&x);                //��������Ŀ� �̾���̱�
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);       //���������
	printf("postExp =  %s\n", postfixExp);      //���������
	printf("eval result = %d\n", evalResult);   //������

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);        //�����ڽ������

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';			//����������ʱ�ȭ
	postfixExp[0] = '\0';		//����������ʱ�ȭ

	for(int i = 0; i < MAX_STACK_SIZE; i++)		//���������ڽ����ʱ�ȭ
		postfixStack[i] = '\0';
    
	postfixStackTop = -1;	//����ž�ʱ�ȭ, ����ʱ�ȭ
	evalStackTop = -1;
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);        //��������Ľ��ñ��̸� length�� ����
	char symbol;
	evalStackTop = -1;      //�������ž�ʱ�ȭ

	for(i = 0; i < length; i++)     //�տ�������
	{
		symbol = postfixExp[i];     //��������Ŀ� i��°�� symbol�� �ְ�
		if(getToken(symbol) == operand) {       //symbol�켱������ �ǿ����ڶ� ������(symbol�� �ǿ�����(����)��)
			evalPush(symbol - '0');         //symbol���� ����'0'����(�̷��� int������ �ٲ�)
		}
		else {      //���ڰ��ƴ϶� �����ڸ�
			opr2 = evalPop();       //������ÿ��� �ΰ�(�Ѵټ�����)�� ���ؼ�
			opr1 = evalPop();
			switch(getToken(symbol)) {      //symbol�ϳ���
			case plus: evalPush(opr1 + opr2); break;        //���ϱ�� ���ڵΰ����ϱ�
			case minus: evalPush(opr1 - opr2); break;       //����� ���ڵΰ��� ����
			case times: evalPush(opr1 * opr2); break;       //���ϱ�� ���ڵΰ��� ���ϱ�
			case divide: evalPush(opr1 / opr2); break;      //������� ���ڵΰ��� ������ �ѰŸ� ������ÿ� Ǫ��
			default: break;
			}
		}
	}
	evalResult = evalPop();     //������ÿ� �����ִ� ���� ���ؼ� ����� ����
}
