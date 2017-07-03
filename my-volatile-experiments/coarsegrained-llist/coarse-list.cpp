/*
 * coarse-plist.cpp
 * This implements a persistent concurrent set.
 * author: Ajay Singh
 */
#include "coarse-list.h"

//DEFAULT VALUES
const uint_t num_threads = 50; /*multiple of 10 the better, for exact thread distribution */

/*should sum upto 100*/
uint_t num_insert_percent = 50;
uint_t num_delete_percent = 40;
uint_t num_lookup_percent = 10;
uint_t num_insert, num_delete, num_lookup;

volatile_list list;
std::thread t[num_threads];


/*************************Barrier code begins*****************************/
std::mutex mtx;
std::condition_variable cv;
bool launch = false;
void wait_for_launch()
{
	std::unique_lock<std::mutex> lck(mtx);
	//printf("locked-waiting\n");
	while (!launch) cv.wait(lck);
}

void shoot()
{
	std::unique_lock<std::mutex> lck(mtx);
	launch = true;
	//printf("main locked-notify\n");
	cv.notify_all();
}
/*************************Barrier code ends*****************************/

void worker(uint_t tid)
{
	//barrier to synchronise all threads for a coherent launch :)
	wait_for_launch();

	if(tid < num_insert)
	{
		uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val = rand()%(MAX_KEY - 1) + 1;
		list.insert(key, val);
	}
	else if(tid < (num_insert + num_delete ))
    {
    	uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val;
		list.remove(key, &val);
    }
	else if(tid < (num_insert + num_delete + num_lookup))//init for lookup threads
	{
		uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val;
		list.find(key, &val);
	}
	else
	{
		std::cout<<"something wrong in thread distribution to operations"<<std::endl;
	}
}

int
main(int argc, char *argv[])
{
	double duration;
	struct timeval start_time, end_time;
	
	#ifdef TIME_EVAL
	FILE *fptr;
	fptr = fopen("time.txt","a");
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	#endif

	if (argc < 1) {
		std::cerr << "usage: " << argv[0]
			  << " [insert percentage "
			  << " delete percentage "
			  << " lookup percentage] " << std::endl;
		return 1;
	}

	if(argc == 4){
		num_insert_percent = atoll(argv[1]);
		num_delete_percent = atoll(argv[2]);
		num_lookup_percent = atoll(argv[3]);
	}

	if((num_insert_percent + num_delete_percent + num_lookup_percent) != 100)
	{
		std::cout<<"Oo LaLa! Seems you got arithmatic wrong :) #operations should sumup to 100" <<std::endl;
		return 0;
	}


	time_t tt;
	srand(time(&tt));

	std::cout <<"init the list first!" <<std::endl;
	list.init();
	for (uint_t i = 0; i < 10; ++i)
	{
		uint_t key = rand()%(MAX_KEY-1) + 1;
		uint_t val = rand()%(MAX_KEY-1) + 1;		
		list.insert(key, val);
	}

	list.print();
		
	num_insert = (uint_t)ceil((num_insert_percent*num_threads)/100);
	num_delete = (uint_t)ceil((num_delete_percent*num_threads)/100);
	num_lookup = (uint_t)ceil((num_lookup_percent*num_threads)/100);

	std::cout<<" num_insert:"<<num_insert<<"\n num_delete: "<<num_delete<<"\n num_lookup: "<<num_lookup<<std::endl;

	if((num_insert + num_delete + num_lookup) > num_threads)
	{
		std::cout<<"((insertNum + delNum + lookupNum) > number_of_threads)"<<std::endl;
		return 0;
	}
	
	for (uint_t i = 0; i < num_threads; ++i)
	{
		t[i] = std::thread(worker, i);
	}

	std::cout <<"\n********STARTING...\n";
	gettimeofday(&start_time, NULL);
	shoot(); //notify all threads to begin the worker();

	for (uint_t i = 0; i < num_threads; ++i)
	{
		t[i].join();
	}
	gettimeofday(&end_time, NULL);
	std::cout <<"\n********STOPPING...\n";

	list.print();

	duration = (end_time.tv_sec - start_time.tv_sec);
	duration += (end_time.tv_usec - start_time.tv_usec)/ 1000000.0;
	std::cout<<"time: "<<duration<<"seconds"<<std::endl;
	
	#ifdef TIME_EVAL
	fprintf(fptr,"%lf\n",duration);
	fclose(fptr);
	#endif
	
	return 0;
}
