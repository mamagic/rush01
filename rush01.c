#include <stdio.h>
#include <stdlib.h>


void ft_write(int d)
{
	printf("%d ", d);
}

typedef struct p
{
	int expect[4];
	int confirmed;
} point;

void print(point **arr)
{
	int	i;
	int j;

	i = 0;
	j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ft_write(arr[i][j].confirmed);
			j++;
		}
		printf("\n");
		i++;
	}
}

void init(point **arr)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				arr[i][j].expect[k] = 0;
				k++;
			}
			arr[i][j].confirmed = 0;
			j++;
		}
		i++;
	}

}

int translate_number(char ch)
{
	return ch - '0';
}

void fill_expect_number(point **arr2D, int num, int i, int j)
{
	int k;

	k = 0;
	while (k < num)
	{
		arr2D[i][j].expect[k] = k + 1;
		k++;
	}

	while (k < 4)
	{
		arr2D[i][j].expect[k] = 0;
		k++;
	}
}

void remove_fill_expect_number(point** arr2D, int num, int i, int j)
{
	int k;

	k = 0;
	while (k < 4)
	{
		if(arr2D[i][j].expect[k] == num)
			arr2D[i][j].expect[k] = 0;
		k++;
	}
	
}

void check_point_4(point** arr2D, char* input)
{
	int		i;
	int		j;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (translate_number(input[i]) == 4)
				arr2D[j][i].confirmed = j + 1;
			if (translate_number(input[i + 4]) == 4)
				arr2D[j][i].confirmed = 4 - j;
			if (translate_number(input[i + 8]) == 4)
				arr2D[i][j].confirmed = j + 1;
			if (translate_number(input[i + 12]) == 4)
				arr2D[i][j].confirmed = 4 - j;
			j++;
		}
		i++;
	}
}

void check_point_1(point** arr2D, char* input)
{
	int		i;
	int		j;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (translate_number(input[i]) == 1 && j == 0)
				arr2D[j][i].confirmed = 4;
			if (translate_number(input[i + 4]) == 1 && j == 3)
				arr2D[j][i].confirmed = 4;
			if (translate_number(input[i + 8]) == 1 && j == 0)
				arr2D[i][j].confirmed = 4;
			if (translate_number(input[i + 12]) == 1 && j == 3)
				arr2D[i][j].confirmed = 4;
			j++;
		}
		i++;
	}
}

void check_point_3(point** arr2D, char* input)
{
	int		i;
	int		j;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (translate_number(input[i]) == 3 && j == 0)
				fill_expect_number(arr2D, 2, j, i);
			if (translate_number(input[i + 4]) == 3 && j == 3)
				fill_expect_number(arr2D, 2, j, i);
			if (translate_number(input[i + 8]) == 3 && j == 0)
				fill_expect_number(arr2D, 2, i, j);
			if (translate_number(input[i + 12]) == 3 && j == 3)
				fill_expect_number(arr2D, 2, i, j);
			j++;
		}
		i++;
	}
}

void check_point_2(point** arr2D, char* input)
{
	int		i;
	int		j;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (translate_number(input[i]) == 2 && j == 0)
				fill_expect_number(arr2D, 3, j, i);
			if (translate_number(input[i + 4]) == 2 && j == 3)
				fill_expect_number(arr2D, 3, j, i);
			if (translate_number(input[i + 8]) == 2 && j == 0)
				fill_expect_number(arr2D, 3, i, j);
			if (translate_number(input[i + 12]) == 2 && j == 3)
				fill_expect_number(arr2D, 3, i, j);
			j++;
		}
		i++;
	}
}

void remove_check_line(point **arr2D, int i, int j)
{
	int k;
	int l;

	k = 0;
	while (k < 4)
	{
		l = 0;
		while (l < 4)
		{
			if (arr2D[i][j].expect[k] == arr2D[i][l].confirmed)
				remove_fill_expect_number(arr2D, arr2D[i][l].confirmed, i, j);
			if (arr2D[i][j].expect[k] == arr2D[l][j].confirmed)
				remove_fill_expect_number(arr2D, arr2D[l][j].confirmed, i, j);
			l++;
		}
		k++;
	}
}

void check_line(point** arr2D)
{
	int	i;
	int j;
	int k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			remove_check_line(arr2D, i, j);
			j++;
		}
		i++;
	}
}

void set_confirmed_loop(point **arr2D, int i, int j)
{
	int k;
	int c;
	int n;

	k = 0;
	c = 0;
	n = 0;
	while (k < 4)
	{
		if (arr2D[i][j].expect[k] == 0)
			c++;
		else
			n = arr2D[i][j].expect[k];
		k++;
	}
	if (c == 3 && n != 0)
		arr2D[i][j].confirmed = n;
}

void set_confirmed(point** arr2D)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			set_confirmed_loop(arr2D, i, j);
			j++;
		}
		i++;
	}
}

void set_middle_expect_number(point **arr2D)
{
	int i;
	int j;
	int k;

	i = 1;
	while (i < 3)
	{
		j = 1;
		while (j < 3)
		{
			k = 0;
			while (k < 4)
			{
				arr2D[i][j].expect[k] = k + 1;
				k++;
			}
			j++;
		}
		i++;
	}
}

int find_expect_number(point** arr2D, int i, int j, int k)
{
    int l;
    int m;

    l = 0;
    while (l < 4)
    {
        m = 0;
        while (m < 4)
        {
            if (i != l && arr2D[i][j].expect[k] == arr2D[l][j].expect[m])
                return 1;
            m++;
        }
        l++;
    }

    return 0;
}

void just_one_expect_number(point** arr2D)
{
    int i;
    int j;
    int k;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            k = 0;
            while(k < 4)
            {
                if(arr2D[i][j].expect[k] != 0)
                {
                    if(find_expect_number(arr2D, i, j, k) != 0)
                    {
                        arr2D[i][j].confirmed = arr2D[i][j].expect[k];
                    }
                }
				k++;
            }
			j++;
        }
        i++;
    }
}

void remove_expect_confirmed(point** arr2D)
{
	int i;
	int j;
	int k;

	i = 0;
	while(i < 4)
	{
		j = 0;
		while(j < 4)
		{
			k = 0;
			if(arr2D[i][j].confirmed != 0)
			{
				while(k < 4)
				{
					arr2D[i][j].expect[k] = 0;
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

void game(point** arr2D, char* input)
{
	int i;

	i = 0;
	check_point_4(arr2D, input);
	check_point_1(arr2D, input);
	check_point_2(arr2D, input);
	check_point_3(arr2D, input);
	set_middle_expect_number(arr2D);

	while (i < 16)
	{
		check_line(arr2D);
		set_confirmed(arr2D);
        just_one_expect_number(arr2D);
		remove_expect_confirmed(arr2D);
		i++;
	}
}

void remove_space(char* input, char* result)
{
	int i;

	i = 0;
	while (i < 31)
	{
		*result = input[i];
		i += 2;
		result++;
	}
}

int main(int argc, char* argv[])
{
	char i[] = "2 1 3 2 2 3 1 2 2 4 1 2 3 1 3 2";
	char input[16];
	point** arr2D;
	
	remove_space(i, input);
	arr2D = malloc(4 * sizeof(point*));
	for (int i = 0; i < 4; i++)
	{
		arr2D[i] = malloc(4 * sizeof(point));
	}

	init(arr2D);
	game(arr2D, input);
	print(arr2D);

	for (int i = 0; i < 4; i++)
	{
		free(arr2D[i]);
	}
}