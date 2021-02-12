#include <stdio.h>
#include <stdlib.h>


void fillGrid(char* grid, int* groups, int* visited);

void searchGroups(char* grid, int* groups, int* visited);
void insertionSortGroups(int* groups);
void printGroups(int* groups);

void walkRecursively(char* grid, int x, int y, int* visited, int* count);


size_t ColCount, RowCount;


int main(void)
{
	size_t rowCount, colCount;
	scanf("%zu%zu", &rowCount, &colCount);
	
	RowCount = rowCount;
	ColCount = colCount;
	
	// allocating contiguous memory on the heap
	char* grid = (char*)malloc(sizeof(char) * rowCount * colCount);
	
	// allocating groups array on the heap
	int* groups = (int*)malloc(sizeof(int) * rowCount * colCount);
	
	// allocating an array that holds the information whether an index has been visited on the heap
	int* visited = (int*)malloc(sizeof(int) * rowCount * colCount);
	
	fillGrid(grid, groups, visited);
	
	searchGroups(grid, groups, visited);
	insertionSortGroups(groups);
	printGroups(groups);
	
	// freeing up resources
	free(grid);
	free(groups);
	free(visited);
	
	return 0;
}

void fillGrid(char* grid, int* groups, int* visited)
{
	// filling grid with hash character at start
	for (int i = 0; i < RowCount * ColCount; ++i)
		grid[i] = '#';
	
	// filling visited array with all zeros denoting false at start
	for (int i = 0; i < RowCount * ColCount; ++i)
		visited[i] = 0;
	
	// getting positions of stars as input
	int y, x;
	scanf("%d", &y);
	
	while (y != -1)
	{
		scanf("%d", &x);
		
		grid[y * ColCount + x] = '*';
		
		scanf("%d", &y);
	}
	
	// filling the groups array with all zeros
	for (int i = 0; i < RowCount * ColCount; ++i)
		groups[i] = 0;
}

void searchGroups(char* grid, int* groups, int* visited)
{
	int count = 0;
	int pos = 0;
	
	for (int y = 0; y < RowCount; ++y)
	{
		for (int x = 0; x < ColCount; ++x)
		{
			walkRecursively(grid, x, y, visited, &count);
			
			groups[pos++] = count;
			count = 0;
		}
	}
}


void walkRecursively(char* grid, int x, int y, int* visited, int* count)
{
	if (y < 0 || x < 0 || y >= RowCount || x >= ColCount || grid[y * ColCount + x] != '*' || visited[y * ColCount + x] == 1)
		return;
	
	visited[y * ColCount + x] = 1;
	
	*count = *count + 1;
	
	walkRecursively(grid, x + 1, y, visited, count);
    walkRecursively(grid, x - 1, y, visited, count);
    walkRecursively(grid, x, y + 1, visited, count);
	walkRecursively(grid, x, y - 1, visited, count);
	walkRecursively(grid, x + 1, y + 1, visited, count);
	walkRecursively(grid, x - 1, y - 1, visited, count);
	walkRecursively(grid, x + 1, y - 1, visited, count);
	walkRecursively(grid, x - 1, y + 1, visited, count);
}


void insertionSortGroups(int* groups)
{
	for (int i = 1; i < RowCount * ColCount; ++i)
	{
		int key = groups[i];
		int j = i - 1;

		while (j >= 0 && groups[j] > key)
		{
			groups[j + 1] = groups[j];
			j = j - 1;
		}
		
		groups[j + 1] = key;
	}
}


void printGroups(int* groups)
{
	int groupCount = 0;
	int groupsStart = -1;
	
	for (int i = 0; i < RowCount * ColCount; ++i)
	{
		if (groups[i] > 0)
		{
			if (groupsStart < 0)
				groupsStart = i;
			
			++groupCount;
		}
	}
	
	if (groupsStart < 0 || groupCount == 0)
	{
		printf("%d\n", 0);
		return;
	}
	
	printf("%d ", groupCount);
	
	for (int i = groupsStart; i < RowCount * ColCount; ++i)
	{
		if (i == RowCount * ColCount - 1)
		{
			printf("%d", groups[i]);
			break;
		}
		
		printf("%d ", groups[i]);
	}
	
	printf("\n");
}

