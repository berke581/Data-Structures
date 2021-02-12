#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
	int id;
	int workTime;
	struct stack* next;
}Stack;

typedef struct queue
{
	int id;
	int enterTime;
	int duration;
	struct queue* next;
}Queue;

typedef struct p_queue
{
	int id;
	Stack* emp;
	int enterTime;
	int exitTime;
	struct p_queue* next;
}pQueue;


// Functions related to allocating and deleting memory for employees
void initializeEmp(Stack** empList);
void freeEmp(Stack** empList);
void printEmp(Stack** empList);

// Stack related functions
void push(Stack** top, Stack* emp);
Stack* pop(Stack** top);
void clearStack(Stack** top);

// Queue related functions
void enqueue(Queue** head, Queue** tail, int id, int enterTime, int duration);
void dequeue(Queue** head, Queue** tail);

// Priority queue related functions
void pQPush(pQueue** head, int id, int enterTime, int exitTime, Stack* emp);
Stack* pQPop(pQueue** head);
int pQPeek(pQueue* head);
void clearPQueue(pQueue** head);

int main() {
	Stack* empList[6];
	initializeEmp(empList);

	Stack* empStack = NULL;

	Queue* head = NULL;
	Queue* tail = NULL;

	pQueue* pHead = NULL;

	// Pushing employees to the stack
	for (int i = 0; i < 6; ++i)
		push(&empStack, empList[i]);

	// Getting inputs and adding them to the queue
	int id, st, dur;
	scanf("%d", &id);
	while (id != -1)
	{
		scanf("%d%d", &st, &dur);
		enqueue(&head, &tail, id, st, dur);
		scanf("%d", &id);
	}

	int currentTime = head->enterTime;

	while (head != NULL)
	{
		// Push back free employee to the stack, I've used priority queue for storing finishing times and the employee that will be pushed back
		while (pHead != NULL && currentTime >= pQPeek(pHead))
			push(&empStack, pQPop(&pHead));

		while (head != NULL && empStack != NULL && head->enterTime <= currentTime)
		{
			Stack* emp = pop(&empStack);
			pQPush(&pHead, head->id, currentTime, currentTime + head->duration, emp);
			emp->workTime += head->duration;

			// Printing the customer that is serviced at the moment
			printf("%d %d %d %d %d\n", head->id, emp->id, currentTime, currentTime + head->duration, currentTime - head->enterTime);

			// Customer at the head of the queue leaves the queue
			dequeue(&head, &tail);
		}

		++currentTime;
	}

	printf("\n");

	// Print employees and working hours
	printEmp(empList);

	// Clearing up resources
	freeEmp(empList);
	clearStack(&empStack);
	clearPQueue(&pHead);

	return 0;
}


void initializeEmp(Stack** empList)
{
	for (int i = 0; i < 6; ++i)
	{
		empList[i] = (Stack*)malloc(sizeof(Stack) * 1);
		empList[i]->id = i + 1;
		empList[i]->workTime = 0;
		empList[i]->next = NULL;
	}
}

void freeEmp(Stack** empList)
{
	for (int i = 0; i < 6; ++i)
		free(empList[i]);
}

void printEmp(Stack** empList)
{
	for (int i = 5; i >= 0; --i)
		printf("%d %d\n", empList[i]->id, empList[i]->workTime);
}


//


void push(Stack** top, Stack* emp)
{
	emp->next = (*top);
	(*top) = emp;
}

Stack* pop(Stack** top)
{
	if (*top != NULL)
	{
		Stack* temp = *top;
		*top = (*top)->next;
		return temp;
	}

	return NULL;
}

void clearStack(Stack** top)
{
	*top = NULL;
}


//


void enqueue(Queue** head, Queue** tail, int id, int enterTime, int duration)
{
	Queue* newPtr = (Queue*)malloc(sizeof(Queue) * 1);
	newPtr->id = id;
	newPtr->enterTime = enterTime;
	newPtr->duration = duration;
	newPtr->next = NULL;

	if (*tail != NULL)
	{
		(*tail)->next = newPtr;
		*tail = newPtr;
	}
	else
	{
		*tail = newPtr;
		*head = *tail;
	}

}

void dequeue(Queue** head, Queue** tail)
{
	if (*head == NULL)
		return;

	Queue* temp = *head;
	*head = (*head)->next;
	free(temp);

	if (*head == NULL)
		*tail = NULL;
}


//


void pQPush(pQueue** head, int id, int enterTime, int exitTime, Stack* emp)
{
	pQueue* newPtr = (pQueue*)malloc(sizeof(pQueue) * 1);
	newPtr->id = id;
	newPtr->enterTime = enterTime;
	newPtr->exitTime = exitTime;
	newPtr->emp = emp;
	newPtr->next = NULL;

	if (*head == NULL)
	{
		*head = newPtr;
	}
	else if (newPtr->exitTime <= (*head)->exitTime) // ???
	{
		newPtr->next = *head;
		*head = newPtr;
	}
	else
	{
		pQueue* currentPtr = *head;

		while (currentPtr->next != NULL && newPtr->exitTime > currentPtr->next->exitTime)
			currentPtr = currentPtr->next;

		newPtr->next = currentPtr->next;
		currentPtr->next = newPtr;
	}
}

Stack* pQPop(pQueue** head)
{
	if (*head == NULL)
		return NULL;

	pQueue* temp = *head;
	Stack* res = (*head)->emp;
	*head = (*head)->next;
	free(temp);

	return res;
}

int pQPeek(pQueue* head)
{
	if (head != NULL)
		return head->exitTime;

	return -1;
}

void clearPQueue(pQueue** head)
{
	while (*head != NULL)
		pQPop(head);
}

