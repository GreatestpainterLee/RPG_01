
#include "Util.h"
#include <time.h>
#include <limits>

int Util::GetRandomNum(int a,int b)// ��ȡ����[a,b)�ڵ������
{
	static int nInit = 0;
	if (nInit == 0)
	{
		srand((unsigned)time(NULL)); 
		nInit = 1;
	}
	

	return rand()%(b-a)+a;
}

float Util::GetProbability()
{
	int n = GetRandomNum(1,101);

	return (n / 100.0);
}