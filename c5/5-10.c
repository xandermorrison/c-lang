#include <stdio.h>
#include <ctype.h>
#define MAXSTACK 1000
#define NUMBER '0'

int pop(void);
void push(int n);

int main(int argc, char *argv[])
{
	char c;
	int num, op2;
	int total = 0;

	while (--argc > 0 && (*++argv)[0]) {
		c = (isdigit(*argv[0])) ? NUMBER : *argv[0];
		switch (c) {
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				push(pop() / op2);
				break;
			case NUMBER:
				num = 0;
				while (isdigit(*argv[0])) {
					num = num * 10 + (*argv[0] - '0');
					argv[0]++;
				}
				push(num);
				break;
			default:
				printf("error: unrecognized option\n");
				break;
		}
	}
	printf("%d\n", pop());
}

int i = 0;
int stack[MAXSTACK];

void push(int n) 
{
	if (i >= MAXSTACK) {
		printf("error: no room in stack");
	}
	else {
		stack[i++] = n;
	}
}

int pop(void)
{
	if (i < 0) {
		printf("error: stack empty");
		return 0;
	}
	else {
		return stack[--i];
	}
}
