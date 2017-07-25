/*!
 * DESCP:			Driver file for fine-grained persistent list implemented using NVML. The algorithm
 * 					used is taken from Art of multiprocessor programming book chapter 9. 
 
 * AUTHOR:			Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION: 	LIP6 - INRIA&UPMC.
 * DATE:			Jul 25, 2017.
 */
#include <fine-plist.h>
#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <sys/time.h>

//DEFAULT VALUES
const uint_t num_threads = 50; /*multiple of 10 the better, for exact thread distribution */

/*should sum upto 100*/
uint_t num_insert_percent = 50;
uint_t num_delete_percent = 40;
uint_t num_lookup_percent = 10;
uint_t num_insert, num_delete, num_lookup;

pool<pmem_list> pop;
std::thread t[num_threads];

/*************************Barrier code begins*****************************/
std::mutex mtx;
std::condition_variable cv;
bool launch = false;

/*
* DESCP:	barrier to sychronize all threads after creation.
* AUTHOR:	Ajay Singh
*/
void wait_for_launch()
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!launch) cv.wait(lck);
}

/*
* DESCP:	let threads execute their task after final thread has arrived.
* AUTHOR:	Ajay Singh
*/
void shoot()
{
	std::unique_lock<std::mutex> lck(mtx);
	launch = true;
	cv.notify_all();
}

/*
* DESCP:	worker for threads that call list's function as per their distribution.
* AUTHOR:	Ajay Singh
*/
void worker(uint_t tid)
{
	//barrier to synchronise all threads for a coherent launch :)
	wait_for_launch();

	auto q = pop.get_root();
	
	if(tid < num_insert)
	{
		uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val = rand()%(MAX_KEY - 1) + 1;
		q->insert(pop, key, val);
	}
	else if(tid < (num_insert + num_delete ))
    {
    	uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val;
		q->remove(pop, key, &val);
    }
	else if(tid < (num_insert + num_delete + num_lookup))//init for lookup threads
	{
		uint_t key = rand()%(MAX_KEY - 1) + 1;
		uint_t val;
		q->find(pop, key, &val);
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
	char buf[10];
	sprintf(buf, "%lu", num_threads);
	fptr = fopen(buf,"a");
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	#endif

	if (argc < 2) {
		std::cerr << "usage: " << argv[0]
			  << " file-name "
			  << " [insert percentage "
			  << " delete percentage "
			  << " lookup percentage] " << std::endl;
		return 1;
	}

	if(argc == 5){
		num_insert_percent = atoll(argv[2]);
		num_delete_percent = atoll(argv[3]);
		num_lookup_percent = atoll(argv[4]);
	}

	if((num_insert_percent + num_delete_percent + num_lookup_percent) != 100)
	{
		std::cout<<"Oo LaLa! Seems you got arithmatic wrong :) #operations should sumup to 100" <<std::endl;
		return 0;
	}

	const char *path = argv[1];
	if (file_exists(path) != 0) 
	{
		pop = pool<pmem_list>::create(path, LAYOUT, AJPMEMOBJ_MIN_POOL, CREATE_MODE_RW);
	} 
	else
	{
		pop = pool<pmem_list>::open(path, LAYOUT);
	}

	auto q = pop.get_root();
	time_t tt;
	srand(time(&tt));

	if(!q->is_inited())
	{
		std::cout <<"init the list first!" <<std::endl;
		q->init(pop);
		for (uint_t i = 0; i < 2; ++i)
		{
			uint_t key = rand()%(MAX_KEY-1) + 1;
			uint_t val = rand()%(MAX_KEY-1) + 1;		
			q->insert(pop, key, val);
		}

		q->print();
	}
	else
	{
		std::cout <<"list already inited, carry on operations" <<std::endl;
		q->print();
	}

	//thread distribution
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

	q->print();
	pop.close();

	duration = (end_time.tv_sec - start_time.tv_sec);
	duration += (end_time.tv_usec - start_time.tv_usec)/ 1000000.0;
	std::cout<<"time: "<<duration<<"seconds"<<std::endl;
	#ifdef TIME_EVAL
	fprintf(fptr,"%lf\n",duration);
	fclose(fptr);
	#endif

	return 0;
}
