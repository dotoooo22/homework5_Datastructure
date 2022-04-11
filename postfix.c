//후위표기
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum{       //열거형 선언
	lparen = 0,         //0은 앞괄호
	rparen = 9,         //9는 뒷괄호
	times = 7,          //7은 곱하기
	divide = 6,         //6은 나누기
	plus = 5,           //5는 더하기
	minus = 4,          //2는 빼기
	operand = 1         //1은 걍 숫자들(피연산자)
} precedence;
//편하게 이름으로 쓸려고 이렇게함 숫자가 높은게 우선순위 더 높음
char infixExp[MAX_EXPRESSION_SIZE];     //중위식 저장할거
char postfixExp[MAX_EXPRESSION_SIZE];   //후위식 저장할거
char postfixStack[MAX_STACK_SIZE];      //후위식 스택
int evalStack[MAX_STACK_SIZE];          //연산자 스택

int postfixStackTop = -1;       //중위식스택탑
int evalStackTop = -1;          //구한값스택탑

int evalResult = 0;             //결과

void postfixPush(char x);		//후위연산식스택에 x푸쉬
char postfixPop();				//후위연산스택팝
void evalPush(int x);			//결과스택x푸쉬
int evalPop();					//결과스택팝
void getInfix();				//중위식입력받기
precedence getToken(char symbol);	//문자에 맞는 enum리턴
precedence getPriority(char x);		//우선순위구하기
void charCat(char* c);				//문자이어붙이기
void toPostfix();					//중위식을 후위식으로 바꾸기
void debug();						//스택, 결과 출력
void reset();						//다 초기화
void evaluation();      //결과구하기

int main()
{
	char command;
    printf("[----- [곽민정] [2021041021] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);		//명령어입력

		switch(command) {
		case 'i': case 'I':     //i면
			getInfix();         //중위식입력받기
			break;
		case 'p': case 'P':     //p면
			toPostfix();        //후위식으로변환
			break;
		case 'e': case 'E':		//e면
			evaluation();		//결과값구하기
			break;
		case 'd': case 'D':		//d면
			debug();			//스택값, 구한값 출력
			break;
		case 'r': case 'R':		//r이면
			reset();			//리셋
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q면 루프빠져나와서 종료

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;        //후위스택에 x넣기
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)       //비어잇으면 널리턴
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];        //탑에 있는거빼고 탑1줄이기
    }
    return x;       //팝한 값 리턴
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;		//구한값스택에 x푸쉬
}

int evalPop()
{
    if(evalStackTop == -1)      //비어있으면
        return -1;              //-1리턴
    else
        return evalStack[evalStackTop--];       //아니면 탑에있는걸 리턴하고 탑을 하나 줄이기
}



void getInfix()
{
    printf("Type the expression >>> ");     
    scanf("%s",infixExp);       //중위식으로 입력을 받음
}

precedence getToken(char symbol)
{
	switch(symbol) {        //각 연산자에 대응하는 enum 리턴
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;       //다아니면 연산자라고 리턴
	}
}

precedence getPriority(char x)
{
	return getToken(x);     //x가 우선순위숫자 받아서 리턴
}


void charCat(char* c)
{
	if (postfixExp == '\0')     //postfixExp가 비어있으면
		strncpy(postfixExp, c, 1);      //후위식연산자에 c를 카피
	else
		strncat(postfixExp, c, 1);      //후위식연산자에 c를 이어붙이기
}


void toPostfix()
{
	char *exp = infixExp;       //중위식을 exp에 넣기
	char x;     //문자하나저장할 변수
	while(*exp != '\0')     //exp가 비어있지 않을 동안
	{
		if(getPriority(*exp) == operand)        //피연산자(숫자)이면
		{
			x = *exp;       //exp가 가리키는값을 x에 넣고
        	charCat(&x);    //x를 후위연산식에 이어붙이기
		}
        else if(getPriority(*exp) == lparen) {      //앞괄호면

        	postfixPush(*exp);      //후위연산스택에 푸쉬
        }
        else if(getPriority(*exp) == rparen)        //뒷괄호면
        {
        	while((x = postfixPop()) != '(') {      //앞괄호랑 만날 때까지
        		charCat(&x);        //괄호속에있는거 다 후위연산식에 이어 붙이기
        	}
        }
        else        //숫자도 괄호도 아니면
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))      //후위연산스택탑에있는 것보다 우선순위가 작다면
            {
            	x = postfixPop();       //그 높은 후위연산스택의 탑값은 팝하고
            	charCat(&x);            //후위연산식에 이어붙이기
            }
            postfixPush(*exp);          //그리고 현재값을 후위연산스택에 넣기
        }
        exp++;      //다음문자
	}

    while(postfixStackTop != -1)        //후위연산스택탑이 -1이 아니면 비어있지않으면(남아있는값을 다)
    {
    	x = postfixPop();           //후위연산스택에서 팝하고 팝한 값을
    	charCat(&x);                //후위연산식에 이어붙이기
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);       //중위식출력
	printf("postExp =  %s\n", postfixExp);      //후위식출력
	printf("eval result = %d\n", evalResult);   //결과출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);        //연산자스택출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';			//중위연산식초기화
	postfixExp[0] = '\0';		//후위연산식초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)		//후위연산자스택초기화
		postfixStack[i] = '\0';
    
	postfixStackTop = -1;	//스탭탑초기화, 결과초기화
	evalStackTop = -1;
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);        //후위연산식스택길이를 length에 저장
	char symbol;
	evalStackTop = -1;      //결과스택탑초기화

	for(i = 0; i < length; i++)     //앞에서부터
	{
		symbol = postfixExp[i];     //후위연산식에 i번째를 symbol에 넣고
		if(getToken(symbol) == operand) {       //symbol우선순위가 피연산자랑 같으면(symbol이 피연산자(숫자)면)
			evalPush(symbol - '0');         //symbol에서 문자'0'을뺌(이러면 int형으로 바뀜)
		}
		else {      //숫자가아니라 연산자면
			opr2 = evalPop();       //결과스택에서 두개(둘다숫자임)를 팝해서
			opr1 = evalPop();
			switch(getToken(symbol)) {      //symbol하나가
			case plus: evalPush(opr1 + opr2); break;        //더하기면 숫자두개더하기
			case minus: evalPush(opr1 - opr2); break;       //빼기면 숫자두개를 빼기
			case times: evalPush(opr1 * opr2); break;       //곱하기면 숫자두개를 곱하기
			case divide: evalPush(opr1 / opr2); break;      //나누기면 숫자두개를 나누기 한거를 결과스택에 푸쉬
			default: break;
			}
		}
	}
	evalResult = evalPop();     //결과스택에 남아있는 값을 팝해서 결과에 넣음
}
