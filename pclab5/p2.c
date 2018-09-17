#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>
int main()
{
	struct timeval TimeValue_Start;
	struct timezone TimeZone_Start;
	struct timeval TimeValue_Final;
	struct timezone TimeZone_Final;
	long time_start, time_end;
	double time_overhead;
	int i,res;
	int n=10000000;
	int a[n];
	for(i=0;i<n;i++)
	{
		a[i]=i ;
		//printf("%d ",a[i]);
	}

	res=a[0];
	gettimeofday(&TimeValue_Start,&TimeZone_Start);

	#pragma omp parallel for num_threads(10) reduction(min:res)
	for(i=1;i<n;i++)
	{
		if(a[i]<res)
		{
			res=a[i];
		}
	}

	gettimeofday(&TimeValue_Final,&TimeZone_Final);
	time_start=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	time_end=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	time_overhead=(time_end-time_start)/1000000.0;
	printf("Time in seconds: %lf\n",time_overhead);
	printf("Minimum element: %d\n",res);
}