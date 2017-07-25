# My Experiments with NVML

The following code contains following data-structure implementations using NVML:
1. Persistent coarse-grained list.    						-->	/src/examples/libpmemobj/cpp/coarsegrained-llist
2. Persistent fine-grained list.							-->	/src/examples/libpmemobj/cpp/finegrained-llist
3. Persistent coarse-grained closed addressed hash table.	-->	/src/examples/libpmemobj/cpp/ht-coarsegrained
4. Persistent fine-grained closed addressed hash table.		-->	/src/examples/libpmemobj/cpp/ht-finegrained

How to execute:

1) Install NVML as per the instruction-->  https://github.com/pmem/nvml
2) cd /src/examples/libpmemobj/cpp/coarsegrained-llist  (or appropriate application directory you wangt to run.)
3) Compile: > make
4) Run:> ./coarse-plist "file-name"
