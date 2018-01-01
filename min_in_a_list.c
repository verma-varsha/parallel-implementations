#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
void *find_min(void *list_ptr);
pthread_mutex_t minimum_value_lock;
int minimum_value, partial_list_size;

int main(){
	double time_start, time_end;
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	time_start =(double)tv.tv_sec + (double)tv.tv_usec/ 1000000.0;
	int arr[20]={30, 22, 28, 32, 9, 47, 12, 21, 18, 52, 36, 31, 29, 23, 17, 16, 11, 6, 3, 24};
	int i;
	pthread_t p_threads[5];
	pthread_attr_t attr;
	partial_list_size=4;
	minimum_value=INT_MAX;
	//pthread_init();
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_mutex_init(&minimum_value_lock, NULL);
	for(i=0; i<20; i+=partial_list_size){
		pthread_create(&p_threads[i/partial_list_size], &attr, find_min, (void *)&arr[i]);
	}
	for(i=0; i<5; i++){
		pthread_join(p_threads[i], NULL);
	}
	gettimeofday(&tv, &tz);
	time_end=(double)tv.tv_sec+(double)tv.tv_usec/1000000.0;

	printf("min value = %d\n", minimum_value);
	printf("%lf\n", time_end-time_start);
	return 0;
}

void *find_min(void *list_ptr){
	int *partial_list_pointer, my_min, i;
	my_min=INT_MAX;
	partial_list_pointer=(int *)list_ptr;
	for(i=0; i<partial_list_size; i++)
		if(partial_list_pointer[i]<my_min)
			my_min=partial_list_pointer[i];

	pthread_mutex_lock(&minimum_value_lock);
	if(my_min<minimum_value)
		minimum_value=my_min;
	pthread_mutex_unlock(&minimum_value_lock);
	pthread_exit(0);
}