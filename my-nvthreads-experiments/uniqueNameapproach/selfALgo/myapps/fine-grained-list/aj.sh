for i in {1..10}
do
echo "running........$i"
./ll_test_evalfg.o; ./ll_test_evalfg.o
sleep 3
done
