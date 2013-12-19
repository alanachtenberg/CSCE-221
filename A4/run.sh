rm results/info.txt
echo "compiling main.cpp ";
g++-4.7 -std=c++11 main.cpp
sleep 1
echo "running all inputs automatically, no node removal "
sleep 1
for number in 1 2 3 4 5 6 7 8 9 10 11 12

do
	for algorithm in p r l
do
echo "n"| ./a.out -f $number$algorithm.txt

echo "completed" $number $algorithm;
	continue
done
done
exit 0
