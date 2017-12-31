#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(){
	int total_hits, seed, total_misses, sample_points, i;
	double computed_pi;
	double time_start, time_end;
	struct timeval tv;
	struct timezone tz;
	double rand_no_x, rand_no_y;

	printf("Enter the number of sample points: ");
	scanf("%d", &sample_points);

	gettimeofday(&tv, &tz);
	time_start=(double)tv.tv_sec + (double)tv.tv_usec/1000000.0;

	total_hits=0;

	for(int i=1; i<=sample_points; i++){
		rand_no_y=(double)(rand_r(&seed))/(double)((2<<30)-1);
		rand_no_x=(double)(rand_r(&seed))/(double)((2<<30)-1);
		if(((rand_no_x-0.5)*(rand_no_x-0.5) + (rand_no_y-0.5)*(rand_no_y-0.5))<0.25)
			total_hits++;
		seed*=i;
	}

	computed_pi= 4.0*(double)total_hits/((double)sample_points);

	gettimeofday(&tv, &tz);
	time_end=(double)tv.tv_sec + (double)tv.tv_usec/1000000.0;

	printf("Computed PI = %lf\n", computed_pi);
	printf("%lf\n", time_end-time_start);

	return 0;
}