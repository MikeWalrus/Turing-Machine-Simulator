#include <stdio.h>

#define TAPELENGTH 5
int turingSim(int *tape, int table[][16]);

int main(void)
{
	int tape[] = {-1, 0, 1, 0, -1};
	int table[8][16] = {{-1, -1, 'L', 1,
						 0, 0, 'L', 0,
						 1, 1, 'L', 0},
						{-1, -1, 'L', 1,
						 1, 1, 'L', 2,
						 0, 0, 'L', 2},
						{1, 0, 'R', 3,
						 0, 0, 'L', 4},
						{0, 2, 'R', 3,
						 1, 3, 'R', 3,
						 -1, -1, 'R', 4},
						{-1, -1, 'R', 4,
						 1, 0, 'R', 5,
						 0, 0, 'N', 7},
						{0, 0, 'R', 6},
						{
							0,
							4,
							'N',
							7,
							1,
							5,
							'N',
							7,
							2,
							6,
							'N',
							7,
							3,
							7,
							'N',
							7,
						},
						{0}};
	turingSim(tape, table); /*
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
*/
	return 0;
}

int turingSim(int *tape, int table[][16])
{
	int state = 0, prevState;
	int read, index = 0;
	int move = 0;
	int write;
	while (move != 'N')
	{
		read = tape[index];
		for (int i = 0; i < 16; i += 4)
		{
			if (table[state][i] == read)
			{
				move = table[state][i + 2];
				write = table[state][i + 1];
				prevState = state;
				state = table[state][i + 3];
				break;
			}
		}

		for (int i = 0; i < TAPELENGTH; i++)
			if (tape[i] == -1)
				printf("| B ");
			else if (tape[i] < 10)
				printf("| %d ", tape[i]);
			else
				printf("| %c ", tape[i]);
		printf("|\n  ");
		for (int i = 0; i < index; i++)
			printf("    ");
		printf("^ q%d\n  ", prevState);
		for (int i = 0; i < index; i++)
			printf("    ");
		if (write == -1)
			printf("B\n");
		else if (write < 10)
			printf("%d\n", write);
		else
			printf("%c\n", write);
		//getchar();
		tape[index] = write;
		switch (move)
		{
		case 'L':
			if (index == 0)
				index = TAPELENGTH - 1;
			else
				index--;
			break;
		case 'R':
			if (index == TAPELENGTH - 1)
				index = 0;
			else
				index++;
			break;
		case 'N':
			break;
		}
	}
	for (int i = 0; i < TAPELENGTH; i++)
		if (tape[i] == -1)
			printf("| B ");
		else if (tape[i] < 10)
			printf("| %d ", tape[i]);
		else
			printf("| %c ", tape[i]);
	printf("|\n  ");
	return 0;
}
