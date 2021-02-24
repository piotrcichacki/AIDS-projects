#include <stdio.h>
#include <stdlib.h>

#define TOP_RIGHT 1
#define DOWN_LEFT 0
#define FIRST_METHOD 1
#define SECOND_METHOD 0

struct Tree {
	struct Tree* parent_node;
	struct Tree* child_node;
	struct Tree* sibling_node;
	int number;
};

struct Tables {
	int** topLeft;
	int** topRight;
	int** downLeft;
	int** downRight;
	int numberOfVerticesA;
	int numberOfVerticesB;
	int numberOfLabelsA;
	int numberOfLabelsB;
}; 


void initialisationStruct(struct Tree* tree)
{
	tree->child_node = NULL;
	tree->parent_node = NULL;
	tree->sibling_node = NULL;
	tree->number = 0;
}

struct Tree* createChild(struct Tree* current, int label)
{
	current->child_node = (struct Tree*)malloc(sizeof(struct Tree));
	initialisationStruct(current->child_node);
	current->child_node->parent_node = current;
	current->number = label;
	return current->child_node;
}

struct Tree* createSibling(struct Tree* current)
{
	current->sibling_node = (struct Tree*)malloc(sizeof(struct Tree));
	initialisationStruct(current->sibling_node);
	current->sibling_node->parent_node = current->parent_node;
	return current->sibling_node;
}

void readNewick(struct Tree* tree, int* numberOfVertices, int* numberOfLabels)
{
	initialisationStruct(tree);
	char input;
	int number = 0, label = -1, vertices = 0;
	struct Tree* current = tree;
	
	input = getc(stdin);

	while (input != ';')
	{
		if (input <= '9' && input >= '0')
		{
			while (input <= '9' && input >= '0')
			{
				number *= 10;
				number += (int)(input - '0');
				input = getc(stdin);
			}
			vertices++;
			current->number = number;
			number = 0;
		}

		if (input == '(')
		{
			current = createChild(current, label);
			label--;
		}
		else if (input == ',')
			current = createSibling(current);
		else if (input == ')')
			current = current->parent_node;
		
		input = getc(stdin);
	} 

	*numberOfLabels = abs(label+1);
	*numberOfVertices = vertices;
	current = NULL;
	free(current);
}

void createTables(struct Tables* tables, int numberOfVerticesA, int numberOfVerticesB, int numberOfLabelsA, int numberOfLabelsB)
{
	int i = 0;
	tables->numberOfVerticesA = numberOfVerticesA;
	tables->numberOfVerticesB = numberOfVerticesB;
	tables->numberOfLabelsA = numberOfLabelsA;
	tables->numberOfLabelsB = numberOfLabelsB;

	tables->topLeft = (int**)malloc((numberOfVerticesA + 1) * sizeof(int*));
	tables->downLeft = (int**)malloc((numberOfLabelsA + 1) * sizeof(int*));
	tables->topRight = (int**)malloc((numberOfVerticesA + 1) * sizeof(int*));
	tables->downRight = (int**)malloc((numberOfLabelsA + 1) * sizeof(int*));


	for (i = 0; i <= tables->numberOfVerticesA; i++)
	{
		tables->topLeft[i] = (int*)malloc((tables->numberOfVerticesB + 1) * sizeof(int));
		tables->topRight[i] = (int*)malloc((tables->numberOfLabelsB + 1) * sizeof(int));
	}
	for (i = 0; i <= tables->numberOfLabelsA; i++)
	{
		tables->downLeft[i] = (int*)malloc((tables->numberOfVerticesB + 1) * sizeof(int));
		tables->downRight[i] = (int*)malloc((tables->numberOfLabelsB + 1) * sizeof(int));
	}

}

void allVertices(struct Tree* tree, int* table, int* counter)
{
	if (tree->child_node == NULL)
	{
		table[*counter] = tree->number;
		(*counter)++;
	}
	if (tree->child_node != NULL)
	{
		allVertices(tree->child_node, table, counter);
	}
	if (tree->sibling_node != NULL)
	{
		allVertices(tree->sibling_node, table, counter);
	}
	return;
}

void compareVertices(struct Tables* tables)
{
	int i = 0, j = 0;
	for (i = 1; i <= tables->numberOfVerticesA; i++)
	{
		for (j = 1; j <= tables->numberOfVerticesB; j++)
		{
			if (tables->topLeft[0][j] == tables->topLeft[i][0]) tables->topLeft[i][j] = 1;
			else tables->topLeft[i][j] = 0;
		}
	}
}

void verticesTable(struct Tables* tables, struct Tree* treeFirst, struct Tree* treeSecond)
{
	int counter = 0, i = 0;
	int* tableA = (int*)malloc(tables->numberOfVerticesA * sizeof(int));
	int* tableB = (int*)malloc(tables->numberOfVerticesB * sizeof(int));

	tables->topLeft[0][0] = 0;

	counter = 0;
	allVertices(treeFirst, tableA, &counter);
	for (i = 1; i <= tables->numberOfVerticesA; i++)
	{
		tables->topLeft[i][0] = tableA[i - 1];
	}
	counter = 0;
	allVertices(treeSecond, tableB, &counter);
	for (i = 1; i <= tables->numberOfVerticesB; i++)
	{
		tables->topLeft[0][i] = tableB[i - 1];
	}
	compareVertices(tables);
	free(tableA);
	free(tableB);
}



void findVertices(struct Tree* tree, int* vertices, int* verticesNumber)
{
	struct Tree* current = tree->child_node;
	vertices[*verticesNumber] = current->number;
	(*verticesNumber)++;
	while (current->sibling_node != NULL)
	{
		current = current->sibling_node;
		vertices[*verticesNumber] = current->number;
		(*verticesNumber)++;
	}
	current = NULL;
	free(current);
}

void findLabel(struct Tree* tree, struct Tree* current, int currentLabel, int* vertices, int* verticesNumber)
{
	if (tree->number == currentLabel)
	{
		findVertices(tree, vertices, verticesNumber);
	}
	else
	{
		if (tree->child_node != NULL) findLabel(tree->child_node, current, currentLabel, vertices, verticesNumber);
		if (tree->sibling_node != NULL) findLabel(tree->sibling_node, current, currentLabel, vertices, verticesNumber);
	}
	return;
}

void fillTopRightTable(struct Tables* tables, int* vertices, int verticesNumber, int currentLabel)
{
	int i = 0, j = 0, currentVertice;

	for (i = 1; i <= tables->numberOfVerticesA; i++)
	{
		tables->topRight[i][-currentLabel] = 0;
	}
	for (i = 0; i < verticesNumber; i++)
	{
		currentVertice = *(vertices + i);
		if (currentVertice  < 0)
		{
			for (j = 1; j <= tables->numberOfVerticesA; j++)
			{
				if (tables->topRight[j][-currentVertice] == 1) tables->topRight[j][-currentLabel] = 1;
			}
		}
		else
		{
			for (j = 1; j <= tables->numberOfVerticesA; j++)
			{			
				if (tables->topRight[j][0] == currentVertice) tables->topRight[j][-currentLabel] = 1;
			}
		}
	}
}

void fillDownLeftTable(struct Tables* tables, int* vertices, int verticesNumber, int currentLabel)
{
	int i = 0, j = 0, currentVertice;

	for (i = 1; i <= tables->numberOfVerticesB; i++)
	{
		tables->downLeft[-currentLabel][i] = 0;
	}

	for (i = 0; i < verticesNumber; i++)
	{
		currentVertice = *(vertices + i);
		if (currentVertice < 0)
		{
			for (j = 1; j <= tables->numberOfVerticesB; j++)
			{
					if (tables->downLeft[-currentVertice][j] == 1) tables->downLeft[-currentLabel][j] = 1;
			}
		}
		else
		{
			for (j = 1; j <= tables->numberOfVerticesB; j++)
			{
					if (tables->downLeft[0][j] == currentVertice) tables->downLeft[-currentLabel][j] = 1;
			}
		}
	}


}

void topRightTable(struct Tables* tables, struct Tree* tree)
{
	int i = 0, verticesNumber = 0, currentLabel = -tables->numberOfLabelsB;
	struct Tree* current = tree;
	int* vertices = (int*)malloc(tables->numberOfVerticesA * sizeof(int));
	
	tables->topRight[0][0] = 0;

	for (i = 1; i <= tables->numberOfLabelsB; i++)
	{
		tables->topRight[0][i] = -i;
	}
	for (i = 1; i <= tables->numberOfVerticesA; i++)
	{
		tables->topRight[i][0] = tables->topLeft[i][0];
	}
	for (i = 1; i <= tables->numberOfLabelsB; i++)
	{
		findLabel(tree, current, currentLabel, vertices, &verticesNumber);
		fillTopRightTable(tables, vertices, verticesNumber, currentLabel);
		verticesNumber = 0;
		currentLabel++;
	}

	current = NULL;
	free(current);
	free(vertices);
}

void downLeftTable(struct Tables* tables, struct Tree* tree)
{
	int i = 0, verticesNumber = 0, currentLabel = -tables->numberOfLabelsA;
	struct Tree* current = tree;

	int* vertices = (int*)malloc(tables->numberOfVerticesB * sizeof(int));

	tables->downLeft[0][0] = 0;

	for (i = 1; i <= tables->numberOfLabelsA; i++)
	{
		tables->downLeft[i][0] = -i;
	}
	for (i = 1; i <= tables->numberOfVerticesB; i++)
	{
		tables->downLeft[0][i] = tables->topLeft[0][i];
	}
	for (i = 1; i <= tables->numberOfLabelsA; i++)
	{
		findLabel(tree, current, currentLabel, vertices, &verticesNumber);
		fillDownLeftTable(tables, vertices, verticesNumber, currentLabel);
		verticesNumber = 0;
		currentLabel++;
	}
	current = NULL;
	free(current);
	free(vertices);
}



int secondMethodValue(struct Tables* tables, int vertice, int node)
{
	int value = 0, i = 0;
	int index = 0;
	if (vertice > 0)
	{
		for (i = 1; i <= tables->numberOfVerticesB; i++)
		{
			if (tables->downLeft[0][i] == vertice)
			{
				index = i;
				if (tables->downLeft[-node][index] > value) value = tables->downLeft[-node][index];
				return value;
			}
		}
	}
	else
	{
		for (i = 1; i <= tables->numberOfLabelsB; i++)
		{
			if (tables->downRight[0][i] == vertice)
			{
				index = i;
				if (tables->downRight[-node][index] > value) value = tables->downRight[-node][index];
				return value;
			}
		}
	}
	return value;
}

int secondMethod(struct Tables* tables, struct Tree* tree, int nodeAX, int nodeBX)
{
	int maks = 0, i = 0, value = 0, verticesNumber = 0;
	struct Tree* current = tree;

	int* vertices = (int*)malloc(tables->numberOfVerticesB * sizeof(int));

	findLabel(tree, current, nodeBX, vertices, &verticesNumber);

	for (i = 0; i < verticesNumber; i++)
	{
		value = secondMethodValue(tables, *(vertices + i), nodeAX);

		if (value > maks) maks = value;
		value = 0;
	}
	free(vertices);
	return maks;
}

int firstMethodValue(struct Tables* tables, int vertice, int node)
{
	int value = 0, i = 0;
	int index = 0;

	if (vertice > 0)
	{
		for (i = 1; i <= tables->numberOfVerticesA; i++)
		{
			if (tables->topRight[i][0] == vertice)
			{
				index = i;
				if (tables->topRight[index][-node] > value) value = tables->topRight[index][-node];
				return value;
			}
		}

	}
	else
	{
		for (i = 1; i <= tables->numberOfLabelsA; i++)
		{
			if (tables->downRight[i][0] == vertice)
			{
				index = i;
				if (tables->downRight[index][-node] > value) value = tables->downRight[index][-node];
				return value;
			}
		}
	}
	return value;
}

int firstMethod(struct Tables* tables, struct Tree* tree, int nodeAX, int nodeBX)
{
	int maks = 0, i = 0, value = 0, verticesNumber = 0;
	struct Tree* current = tree;

	int* vertices = (int*)malloc(tables->numberOfVerticesA * sizeof(int));

	findLabel(tree, current, nodeAX, vertices, &verticesNumber);

	for (i = 0; i < verticesNumber; i++)
	{
		value = firstMethodValue(tables, *(vertices + i), nodeBX);
		
		if (value > maks) maks = value;
		value = 0;
	}
	free(vertices);
	return maks;
}

void initializationTable(int** table, int moreVertices, int lessVertices, int* Vertices1, int* Vertices2)
{
	int i = 0, j = 0;
	table[0][0] = 0;
	for (i = 1; i <= moreVertices; i++)
	{
		table[i][0] = *(Vertices1 + i - 1);
	}
	for (i = 1; i <= lessVertices; i++)
	{
		table[0][i] = *(Vertices2 + i - 1);
	}
	for (i = 1; i <= moreVertices; i++)
	{
		for (j = 1; j <= lessVertices; j++)
		{
			table[i][j] = 0;
		}
	}
}

int compare(struct Tables* tables, int verticeA, int verticeB)
{
	int indexA = 0, indexB = 0, i = 0;
	if (verticeA > 0 && verticeB > 0)
	{
		for (i = 1; i <= tables->numberOfVerticesA; i++)
		{
			if (tables->topLeft[i][0] == verticeA) indexA = i;
		}
		for (i = 1; i <= tables->numberOfVerticesB; i++)
		{
			if (tables->topLeft[0][i] == verticeB) indexB = i;
		}
		return tables->topLeft[indexA][indexB];
	}
	else if (verticeA > 0 && verticeB < 0)
	{
		indexB = -verticeB;
		for (i = 1; i <= tables->numberOfVerticesA; i++)
		{
			if (tables->topRight[i][0] == verticeA) indexA = i;
		}
		return tables->topRight[indexA][indexB];
	}
	else if (verticeA < 0 && verticeB > 0)
	{
		indexA = -verticeA;
		for (i = 1; i <= tables->numberOfVerticesB; i++)
		{
			if (tables->downLeft[0][i] == verticeB) indexB = i;
		}
		return tables->downLeft[indexA][indexB];
	}
	else
	{
		indexA = -verticeA;
		indexB = -verticeB;
		return tables->downRight[indexA][indexB];
	}
}

void fillTable(struct Tables* tables, int** table, int moreVertices, int lessVertices, char more)
{
	int i = 0, j = 0, verticeA = 0, verticeB = 0;

	for (i = 1; i <= moreVertices; i++)
	{
		for (j = 1; j <= lessVertices; j++)
		{
			if (more == 'A')
			{
				verticeA = table[i][0];
				verticeB = table[0][j];
			}
			else if (more == 'B')
			{
				verticeA = table[0][j];
				verticeB = table[i][0];
			}
			table[i][j] = compare(tables, verticeA, verticeB);
		}
	}
	for (i = 0; i <= moreVertices; i++)
	{
		for (j = 0; j <= lessVertices; j++)
		{
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n");
}

void combination(int** table, int currentRow, int rowNumber, int colNumber, int* usedVertices, int* maks, int sum)
{
	int i = 0;
	if (currentRow >= (rowNumber+1))
	{
		if (sum > *maks)
		{
			*maks = sum;
		}
		return;
	}
	for (i = 1; i <= colNumber; i++)
	{
		if (usedVertices[i] == 0)
		{
			usedVertices[i] = 1;
			combination(table, currentRow + 1, rowNumber, colNumber, usedVertices, maks, sum + table[currentRow][i]);
			usedVertices[i] = 0;
		}
	}
}

void theBiggestSum(int** table, int rowNumber, int colNumber, int* maks)
{
	int i = 0;
	int* usedVertices = (int*)malloc((colNumber+1)*sizeof(int));
	for (i = 0; i <= colNumber; i++)
	{
		usedVertices[i] = 0;
	}
	combination(table, 1, rowNumber, colNumber, usedVertices, maks, 0);
	free(usedVertices);
}

void sonsComparisionMethod(struct Tables* tables, struct Tree* treeA, struct Tree* treeB, int nodeAX, int nodeBX, int* maks)
{
	int i = 0, verticesNumberA = 0, verticesNumberB = 0, moreVertices=0;
	struct Tree* current;
	int* verticesA = (int*)malloc(tables->numberOfVerticesA * sizeof(int));
	int* verticesB = (int*)malloc(tables->numberOfVerticesB * sizeof(int));

	if (tables->numberOfVerticesA >= tables->numberOfVerticesB)
		moreVertices = tables->numberOfVerticesA;
	else
		moreVertices = tables->numberOfVerticesB;

	int** table = (int**)malloc((moreVertices+1) * sizeof(int*));
	
	for (i = 0; i <= moreVertices; i++)
	{
		table[i] = (int*)malloc((moreVertices + 1) * sizeof(int));
	}

	current = treeA;
	findLabel(treeA, current, nodeAX, verticesA, &verticesNumberA);
	current = treeB;
	findLabel(treeB, current, nodeBX, verticesB, &verticesNumberB);

	if (verticesNumberA >= verticesNumberB)
	{
		initializationTable(table, verticesNumberB, verticesNumberA, verticesB, verticesA);
		fillTable(tables, table, verticesNumberB, verticesNumberA, 'B');
		theBiggestSum(table, verticesNumberB, verticesNumberA, maks);
	}
	else
	{
		initializationTable(table, verticesNumberA, verticesNumberB, verticesA, verticesB);
		fillTable(tables, table, verticesNumberA, verticesNumberB, 'A');
		theBiggestSum(table, verticesNumberA, verticesNumberB, maks);
	}

	for (i = 0; i <= moreVertices; i++)
	{
		free(table[i]);
	}
	free(table);

	free(verticesB);
	free(verticesA);

}

void comparisionTable(struct Tables* tables, struct Tree* treeFirst, struct Tree* treeSecond)
{
	int i = 0, j = 0, maks = 0, maks1 = 0, maks2 = 0, maks3 = 0;

	tables->downRight[0][0] = 0;
	for (i = 1; i <= tables->numberOfLabelsA; i++)
	{
		tables->downRight[i][0] = -i;
	}
	for (i = 1; i <= tables->numberOfLabelsB; i++)
	{
		tables->downRight[0][i] = -i;
	}

	for (i = 1; i <= tables->numberOfLabelsA; i++)
	{
		for (j = 1; j <= tables->numberOfLabelsB; j++)
		{
			tables->downRight[i][j] = 0;
		}
	}

	for (i = tables->numberOfLabelsA; i >= 1 ; i--)
	{
		for (j = tables->numberOfLabelsB; j >= 1; j--)
		{
			maks1 = firstMethod(tables, treeFirst, tables->downRight[i][0], tables->downRight[0][j]);
			if (maks1 > maks) maks = maks1;
			maks2 = secondMethod(tables, treeSecond, tables->downRight[i][0], tables->downRight[0][j]);
			if (maks2 > maks) maks = maks2;
			sonsComparisionMethod(tables, treeFirst, treeSecond, tables->downRight[i][0], tables->downRight[0][j], &maks3);
			if (maks3 > maks) maks = maks3;

			tables->downRight[i][j] = maks;
			maks1 = 0;
			maks2 = 0;
			maks3 = 0;
			maks = 0;
		}
	}

}



int findResult(struct Tables* tables)
{
	int i = 0, j = 0, maks = 0;
	for (i = 1; i <= tables->numberOfLabelsA; i++)
	{
		for (j = 1; j <= tables->numberOfLabelsB; j++)
		{
			if (tables->downRight[i][j] > maks) maks = tables->downRight[i][j];
		}
	}
	return maks;
}

void printTable(struct Tables* tables)
{
	int k = 0, m = 0;

	printf("\n");
	for (k = 0; k <= tables->numberOfVerticesA; k++)
	{
		for (m = 0; m <= tables->numberOfVerticesB; m++)
		{
			printf("%d ", tables->topLeft[k][m]);
		}
		printf("\t");
		for (m = 0; m <= tables->numberOfLabelsB; m++)
		{
			printf("%d ", tables->topRight[k][m]);
		}
			printf("\n");
	}
	printf("\n");
	for (k = 0; k <= tables->numberOfLabelsA; k++)
	{
		for (m = 0; m <= tables->numberOfVerticesB; m++)
		{
			printf("%d ", tables->downLeft[k][m]);
		}
		printf("\t");
		for (m = 0; m <= tables->numberOfLabelsB; m++)
		{
			printf("%d ", tables->downRight[k][m]);
		}
		printf("\n");
	}
}

void freeTable(struct Tables* tables)
{
	int i = 0;

	for (i = 0; i <= tables->numberOfVerticesA; i++)
	{
		free(tables->topLeft[i]);
		free(tables->topRight[i]);
	}
	for (i = 0; i <= tables->numberOfLabelsA; i++)
	{
		free(tables->downLeft[i]);
		free(tables->downRight[i]);
	}
	free(tables->topLeft);
	free(tables->downLeft);
	free(tables->topRight);
	free(tables->downRight);
}

void freeTree(struct Tree* tree)
{
	if (tree->child_node != NULL)
	{
		freeTree(tree->child_node);
	}
	if (tree->sibling_node != NULL)
	{
		freeTree(tree->sibling_node);
	}
	if (tree->child_node == NULL && tree->sibling_node == NULL)
	{
		tree->parent_node = NULL;
		free(tree);
	}
	return;
}


int main()
{
	int numberOfTrees = 0, i = 0, j = 0, maks = 0, result = 0;

	scanf_s("%d", &numberOfTrees);
	struct Tree* treePointer = (struct Tree*)malloc(numberOfTrees*sizeof(struct Tree));
	int* numberOfVertices = (int*)malloc(numberOfTrees * sizeof(int));
	int* numberOfLabels = (int*)malloc(numberOfTrees * sizeof(int));
	struct Tables tables;

	for (i = 0; i < numberOfTrees; i++)
	{
		readNewick(&treePointer[i], &numberOfVertices[i], &numberOfLabels[i]);
		getc(stdin);
	}

	for (i = 0; i < numberOfTrees-1; i++)
	{
		for (j = i + 1; j < numberOfTrees; j++)
		{
			createTables(&tables, numberOfVertices[i], numberOfVertices[j], numberOfLabels[i], numberOfLabels[j]);
			
			verticesTable(&tables, &treePointer[i], &treePointer[j]);
			topRightTable(&tables, &treePointer[j]);
			downLeftTable(&tables, &treePointer[i]);
			comparisionTable(&tables, &treePointer[i], &treePointer[j]);
			
			maks = findResult(&tables);
			if(tables.numberOfVerticesA < tables.numberOfVerticesB)
				result = tables.numberOfVerticesA - maks;
			else result = tables.numberOfVerticesB - maks;

			printf("%d\n", result);
			printTable(&tables);

			freeTable(&tables);
			maks = 0;
			result = 0;
		}
		freeTree(&treePointer[i]);
	}

	freeTree(&treePointer[numberOfTrees-1]);
	
	free(numberOfLabels);
	free(numberOfVertices);

	return 0;
}