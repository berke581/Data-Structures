struct nodeFB
{
	int id;
	int age;
	struct nodeFB *next;
};

struct nodeGS
{
	int id;
	struct nodeGS *next;
};

struct newNodeFB
{
	int id;
	int age;
	struct newNodeGS *next;
};

struct newNodeGS
{
	int id;
	struct newNodeFB *next;
};

void insertFB(struct nodeFB** start, int id, int age)
{
	struct nodeFB* newNode = (struct nodeFB*)malloc(sizeof(struct nodeFB) * 1);
	newNode->id = id;
	newNode->age = age;
	newNode->next = NULL;

	struct nodeFB* ptrCurrent;

	if ( *start == NULL || (*start)->id >= newNode->id )
	{
		newNode->next = *start;
		*start = newNode;
	}
	else
	{
		ptrCurrent = *start;
		
		while ( ptrCurrent->next != NULL && ptrCurrent->next->id < newNode->id )
		{
			ptrCurrent = ptrCurrent->next;
		}

		newNode->next = ptrCurrent->next;
		ptrCurrent->next = newNode;
	}
}

void printFB(struct nodeFB* start)
{
	if (start == NULL)
		return;

	while (start != NULL)
	{
		printf("%d %d\n", start->id, start->age);
		start = start->next;
	}

	printf("\n");
}

void insertGS(struct nodeGS** start, int id)
{
	struct nodeGS* newNode = (struct nodeGS*)malloc(sizeof(struct nodeGS) * 1);
	newNode->id = id;
	newNode->next = NULL;

	struct nodeGS* ptrCurrent;

	if ( *start == NULL || (*start)->id <= newNode->id )
	{
		newNode->next = *start;
		*start = newNode;
	}
	else
	{
		ptrCurrent = *start;
        
		while ( ptrCurrent->next != NULL && ptrCurrent->next->id > newNode->id )
		{
			ptrCurrent = ptrCurrent->next;
		}

		newNode->next = ptrCurrent->next;
		ptrCurrent->next = newNode;
	}
}

void printGS(struct nodeGS* start)
{
	if (start == NULL)
		return;

	while (start != NULL)
	{
		printf("%d\n", start->id);
		start = start->next;
	}

	printf("\n");
}

void createFinalList(struct newNodeFB** startNewFB,struct nodeFB* startFB,struct nodeGS* startGS)
{
	struct newNodeFB* posFB = NULL;
	struct newNodeGS* posGS = NULL;

	if (startFB != NULL)
		*startNewFB = (struct newNodeFB*)malloc(sizeof(struct newNodeFB) * 1);
	else
		return;

	(*startNewFB)->id = startFB->id;
	(*startNewFB)->age = startFB->age;
	(*startNewFB)->next = NULL;

	posFB = (*startNewFB);

	if (startGS != NULL)
		(*startNewFB)->next = (struct newNodeGS*)malloc(sizeof(struct newNodeGS) * 1);
	else
		return;

	(*startNewFB)->next->id = startGS->id;
	(*startNewFB)->next->next = NULL;

	posGS = (*startNewFB)->next;

	startFB = startFB->next;
	startGS = startGS->next;


	while (startFB != NULL)
	{
		posGS->next = (struct newNodeFB*)malloc(sizeof(struct newNodeFB) * 1);
		posGS->next->id = startFB->id;
		posGS->next->age = startFB->age;
		posGS->next->next = NULL;

		posFB = posGS->next;

		if (startGS != NULL)
		{
			posFB->next = (struct newNodeGS*)malloc(sizeof(struct newNodeGS) * 1);
			posFB->next->id = startGS->id;
			posFB->next->next = NULL;

			posGS = posFB->next;

			startGS = startGS->next;
		}

		startFB = startFB->next;
	}
}

void printAll(struct newNodeFB* startNewFB)
{
	if (startNewFB == NULL)
		return;

	while (startNewFB != NULL)
	{
		printf("%d %d\n", startNewFB->id, startNewFB->age);

		if (startNewFB->next != NULL)
		{
			printf("%d\n", startNewFB->next->id);
		}

		if (startNewFB->next != NULL)
			startNewFB = startNewFB->next->next;
		else
			startNewFB = NULL;
	}
}

