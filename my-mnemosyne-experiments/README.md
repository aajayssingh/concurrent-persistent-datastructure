# My Experiments with MNEMOSYNE

The following code contains following data-structure implementations using MNEMOSYNE:
1. Persistent coarse-grained list.    						-->	/usermode/examples/coarse-grained-plist
2. Persistent fine-grained list.							-->	/usermode/examples/fine-grained-plist
3. Persistent coarse-grained closed addressed hash table.	-->	/usermode/examples/ht-coarse-grained-plist
4. Persistent fine-grained closed addressed hash table.		-->	/usermode/examples/ht-fine-grained-plist

How to execute:

1) Install Mnemosyne as per the instruction-->  https://github.com/snalli/mnemosyne-gcc
2) cd /usermode
3) Compile: > scons --build-example=coarse-grained-plist   (replace coarse-grained-plist with apt name of the application you wanna run like: ht-coarse-grained-plist, fine-grained-plist).
4) Run:> ./build/examples/ht-coarse-grained-plist/ht-coarse-grained-plist     (replace coarse-grained-plist with apt name of the application you wanna run like: ht-coarse-grained-plist, fine-grained-plist).
