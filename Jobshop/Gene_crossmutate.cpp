#include"jobhead.h"
int counting;
int all;
int *p;
int *value;
int *bestp;
int *recentp;
int mintime;
int evolve()
{
	counting = 1;
	int i;
	int ran;
	int* avoid = (int *)malloc(sizeof(int)*(chronum + 1));
	if (ProcedureTotal>4)
	{
		memset(avoid, 0, sizeof(int)*(chronum + 1));
		int lena = (chronum - 1)*Pcross;
		for (i = 1; i <= lena; i++)
		{
			ran = rand() % chronum;
			if (ran == 0)
			{
				i--;
				goto ppp;
			}
			if (avoid[ran] == 0)
			{
				cross(ran);
				avoid[ran]++;
			}
			else i--;
		ppp:
			;
		}
	}
	memset(avoid, 0, sizeof(int)*(chronum + 1));
	int lenb = (chronum - 1)*Pmutate;
	for (i = 1; i <= lenb; i++)
	{
		ran = rand() % chronum;
		if (ran == 0)
		{
			i--;
			continue;
		}
		if (avoid[ran] == 0)
		{
			mutate(ran);
			avoid[ran]++;
		}
		else i--;
	}

	free(avoid);
	freethem();
	return 0;
}
int cross(int flag)
{
	int po[4];
	int i, j, temp;
	for (i = 0; i<4; i++)
	{
		while (1)
		{
			po[i] = rand() % ProcedureTotal + 1;
			if (check(po, i))break;
		}
	}
	for (i = 3; i>0; i--)
	{
		for (j = 0; j<i; j++)
		{
			if (po[j]>po[j + 1])
			{
				temp = po[j];
				po[j] = po[j + 1];
				po[j + 1] = temp;
			}
		}
	}
	int position = 1;
	if (generation % 2 == 1)
	{
		for (i = 1; i <= ProcedureTotal; i++)
		{
			if (i == po[0])
			{
				for (j = po[2]; j <= po[3]; j++)
				{
					ChroSon[counting][position] = ChroOne[flag][j];
					position++;
				}
			}
			else if (i == po[2])
			{
				for (j = po[0]; j <= po[1]; j++)
				{
					ChroSon[counting][position] = ChroOne[flag][j];
					position++;
				}
			}
			else if ((i>po[0] && i <= po[1]) || (i>po[2] && i <= po[3]))continue;
			else
			{
				ChroSon[counting][position] = ChroOne[flag][i];
				position++;
			}
		}
	}
	else
	{
		for (i = 1; i <= ProcedureTotal; i++)
		{
			if (i == po[0])
			{
				for (j = po[2]; j <= po[3]; j++)
				{
					ChroSon[counting][position] = ChroTwo[flag][j];
					position++;
				}
			}
			else if (i == po[2])
			{
				for (j = po[0]; j <= po[1]; j++)
				{
					ChroSon[counting][position] = ChroTwo[flag][j];
					position++;
				}
			}
			else if ((i>po[0] && i <= po[1]) || (i>po[2] && i <= po[3]))continue;
			else
			{
				ChroSon[counting][position] = ChroTwo[flag][i];
				position++;
			}
		}

	}
	decode(ChroSon[counting]);
	counting++;
	return 0;
}
int mutate(int flag)
{
	if (N >= 4)all = 4;
	else all = N;
	p = (int*)malloc(sizeof(int)*(all));
	value = (int*)malloc(sizeof(int)*(all));
	bestp = (int*)malloc(sizeof(int)*(all));
	recentp =(int*) malloc(sizeof(int)*(all));
	int i;
	if (generation % 2 == 1)
	{
		mintime = decode(ChroOne[flag]);
		for (i = 0; i<all; i++)
		{
			while (1)
			{
				p[i] = rand() % ProcedureTotal + 1;
				if (!check(p, i))continue;
				value[i] = ChroOne[flag][p[i]];
				if (check(value, i))break;
			}
		}
		for (i = 0; i<all; i++)
		{
			bestp[i] = ChroOne[flag][p[i]];
		}
		dfs1(flag, 0);
		for (i = 0; i<all; i++)
		{
			ChroOne[flag][p[i]] = bestp[i];
		}
	}
	else
	{
		mintime = decode(ChroTwo[flag]);
		for (i = 0; i<all; i++)
		{
			while (1)
			{
				p[i] = rand() % ProcedureTotal + 1;
				if (!check(p, i))continue;
				value[i] = ChroTwo[flag][p[i]];
				if (check(value, i))break;
			}
		}
		for (i = 0; i<all; i++)
		{
			bestp[i] = ChroTwo[flag][p[i]];
		}
		dfs2(flag, 0);
		for (i = 0; i<all; i++)
		{
			ChroTwo[flag][p[i]] = bestp[i];
		}
	}
	return 0;
}
void freethem()
{
	free(p);
	free(value);
	free(bestp);
	free(recentp);
}
int check(int *a, int recent)
{
	int i;
	for (i = 0; i<recent; i++)
	{
		if (a[recent] == a[i])return 0;
	}
	return 1;
}
int dfs1(int flag, int step)
{
	int i;
	if (step == all)
	{
		for (i = 0; i<all; i++)
		{
			ChroOne[flag][p[i]] = recentp[i];
		}
		if (decode(ChroOne[flag])<mintime)
		{
			mintime = decode(ChroOne[flag]);
			for (i = 0; i<all; i++)
			{
				bestp[i] = recentp[i];
			}
		}
		return 0;
	}
	for (i = 0; i<all; i++)
	{
		recentp[step] = value[i];
		if (check(recentp, step))
		{
			dfs1(flag, step + 1);
		}
	}
	return 0;
}
int dfs2(int flag, int step)
{
	int i;
	if (step == all)
	{
		for (i = 0; i<all; i++)
		{
			ChroTwo[flag][p[i]] = recentp[i];
		}
		if (decode(ChroTwo[flag])<mintime)
		{
			mintime = decode(ChroTwo[flag]);
			for (i = 0; i<all; i++)
			{
				bestp[i] = recentp[i];
			}
		}
		return 0;
	}
	for (i = 0; i<all; i++)
	{
		recentp[step] = value[i];
		if (check(recentp, step))
		{
			dfs2(flag, step + 1);
		}
	}
	return 0;
}
int addChro()
{
	int* countnum = (int *)malloc(sizeof(int)*(N + 1));
	int i, j;
	int Arandom;
	int times = 0;
	int Atemp;
	int temp;
	for (i = 1; i<Nextgen; i++)
	{
		times++;
		memset(countnum, 0, sizeof(int)*(N + 1));
		for (j = 1; j <= ProcedureTotal; j++)
		{
			temp = rand() % N + 1;
			if (countnum[temp] >= n_num[temp])
			{
				j--;
				continue;
			}
			else
			{
				ChroSon[i][j] = temp;
				countnum[temp]++;
			}
		}
		Arandom = rand() % 100 + 1;
		Atemp = decode(ChroSon[i]);
		if (Atemp>1.05*GreatGeneNum&&Arandom >= GreatGeneNum * 112 / Atemp)
			i--;
	}
	free(countnum);
	return 0;
}