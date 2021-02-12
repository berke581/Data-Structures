struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};

struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};


int reverseNumber(int num)
{
	int result = 0;

	while (num > 0)
	{
		result *= 10;
		result += num % 10;
		num /= 10;
	}

	return result;
}

int getClassID(int student_id)
{
	int reversedID = reverseNumber(student_id);

	if ( reversedID % 10 == 6 && (reversedID / 10) % 10 == 6 )
		return 1;
	else if ( reversedID % 10 == 7 && (reversedID / 10) % 10 == 7 )
		return 2;
	else if ( reversedID % 10 == 8 && (reversedID / 10) % 10 == 8)
		return 3;
	else if ( reversedID % 10 == 9 && (reversedID / 10) % 10 == 9 )
		return 4;

	return -1;
}


void insert(struct nodeClass** headPtr, int student_id, int midterm_mark)
{
	if (*headPtr == NULL)
	{
		(*headPtr) = (struct nodeClass*)malloc(sizeof(struct nodeClass) * 1);
		(*headPtr)->classID = 1;
		(*headPtr)->classMidtermAverage = 0.0;
		(*headPtr)->studentPtr = NULL;

		(*headPtr)->next = (struct nodeClass*)malloc(sizeof(struct nodeClass) * 1);
		(*headPtr)->next->classID = 2;
		(*headPtr)->next->classMidtermAverage = 0.0;
		(*headPtr)->next->studentPtr = NULL;

		(*headPtr)->next->next = (struct nodeClass*)malloc(sizeof(struct nodeClass) * 1);
		(*headPtr)->next->next->classID = 3;
		(*headPtr)->next->next->classMidtermAverage = 0.0;
		(*headPtr)->next->next->studentPtr = NULL;

		(*headPtr)->next->next->next = (struct nodeClass*)malloc(sizeof(struct nodeClass) * 1);
		(*headPtr)->next->next->next->classID = 4;
		(*headPtr)->next->next->next->classMidtermAverage = 0.0;
		(*headPtr)->next->next->next->studentPtr = NULL;

		(*headPtr)->next->next->next->next = NULL;
	}

	struct nodeStudent* newNode = (struct nodeStudent*)malloc(sizeof(struct nodeStudent) * 1);
	newNode->studentID = student_id;
	newNode->next = NULL;
	newNode->midterm = midterm_mark;

	struct nodeClass* headTemp = NULL;

	if ( getClassID(student_id) == 1 )
		headTemp = (*headPtr);
	else if ( getClassID(student_id) == 2 )
		headTemp = (*headPtr)->next;
	else if ( getClassID(student_id) == 3 )
		headTemp = (*headPtr)->next->next;
	else if ( getClassID(student_id) == 4 )
		headTemp = (*headPtr)->next->next->next;


	if ( headTemp->studentPtr == NULL || newNode->midterm > headTemp->studentPtr->midterm )
	{
		newNode->next = headTemp->studentPtr;
		headTemp->studentPtr = newNode;
	}
	else if ( newNode->midterm == headTemp->studentPtr->midterm )
	{
		if (newNode->studentID < headTemp->studentPtr->studentID)
		{
			newNode->next = headTemp->studentPtr;
			headTemp->studentPtr = newNode;
		}
		else
		{
			newNode->next = headTemp->studentPtr->next;
			headTemp->studentPtr->next = newNode;
		}
	}
	else
	{
		struct nodeStudent* currentPtr = headTemp->studentPtr;

		while ( currentPtr->next != NULL && newNode->midterm <= currentPtr->next->midterm )
		{
			if (newNode->midterm == currentPtr->next->midterm)
				if (newNode->studentID < currentPtr->next->studentID)
					break;

			currentPtr = currentPtr->next;
		}

		newNode->next = currentPtr->next;
		currentPtr->next = newNode;
	}
}

void printAll(struct nodeClass* headPtr)
{
	while (headPtr != NULL)
	{
		struct nodeStudent* currentPtr = headPtr->studentPtr;

		printf("%d %.2f\n", headPtr->classID, headPtr->classMidtermAverage);

		while (currentPtr != NULL)
		{
			printf("%d %d\n", currentPtr->studentID, currentPtr->midterm);

			currentPtr = currentPtr->next;
		}

		headPtr = headPtr->next;
	}
}

void computeClassAverage(struct nodeClass* head)
{
	while (head != NULL)
	{
		struct nodeStudent* currentPtr = head->studentPtr;

		double sum = 0;
		int count = 0;

		while (currentPtr != NULL)
		{
			sum += currentPtr->midterm;
			++count;

			currentPtr = currentPtr->next;
		}

		if (sum != 0 && count != 0)
			head->classMidtermAverage = sum/(double)count;
		else
			head->classMidtermAverage = 0;

		head = head->next;
	}
}

