#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int main(){
	int sum, num_threads, npoints, sample_points_per_thread, i, seed;
	double rand_no_x, rand_no_y;
	double time_start, time_end;
	struct timeval tv;
	struct timezone tz;
	printf("Enter number of sample points: ");
	scanf("%d", &npoints);

	gettimeofday(&tv, &tz);
	time_start =(double)tv.tv_sec + (double)tv.tv_usec/ 1000000.0;

	#pragma omp parallel default(none) private(num_threads, sample_points_per_thread, seed, i, rand_no_x, rand_no_y) shared(npoints) reduction(+:sum) num_threads(8)
		{
			num_threads=omp_get_num_threads();
			sample_points_per_thread=npoints/num_threads;
			sum=0;
			seed=1;
			for(i=1; i<=sample_points_per_thread; i++){
				rand_no_x=(double)(rand_r(&seed))/(double)((2<<30)-1);
				rand_no_y=(double)(rand_r(&seed))/(double)((2<<30)-1);
				seed++;
				if(((rand_no_x-0.5)*(rand_no_x-0.5)+(rand_no_y-0.5)*(rand_no_y-0.5))<0.25)
					sum++;
			}
		}

	gettimeofday(&tv, &tz);
	time_end=(double)tv.tv_sec+(double)tv.tv_usec/1000000.0;

	double computed_pi= 4.0*(double)sum/((double)npoints);
	printf("Computed PI = %lf\n", computed_pi);
	printf("Time Taken = %lf\n", time_end-time_start);
	return 0;
}