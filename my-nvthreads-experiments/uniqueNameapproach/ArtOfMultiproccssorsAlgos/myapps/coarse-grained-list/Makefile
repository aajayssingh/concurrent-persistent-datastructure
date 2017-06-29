NVTHREAD_HOME=../../lib-nvthreads
CC = g++
CFLAGS = -std=c++11 -g -fpermissive
PLIB = -lpthread
NVLIB = $(NVTHREAD_HOME)/src/libnvthread.so -ldl
DLIB = $(NVTHREAD_HOME)/third-parties/dthreads/src/libdthread.so -ldl

#nvthread
INC_DIR = $(NVTHREAD_HOME)/src/include
SRC_DIR = $(NVTHREAD_HOME)/src/source

NVINCLUDE_DIRS = -I$(INC_DIR)
NVSRCS = $(SRC_DIR)/nvrecovery.cpp 

all: ll_test_evalcg
ll_test_evalcg:
	$(CC) $(CFLAGS) -DNVTHREAD $(NVINCLUDE_DIRS) $(NVSRCS) ll_test_eval.c linkedlist.c -o ll_test_evalcg.o -rdynamic $(NVLIB)
clean:
	rm *.o MemLog* varmap* _crashed _running /mnt/tmpfs/*
