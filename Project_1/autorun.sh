echo "running sort";
for algorithm in  S I B H R
do
	for infile in 1 2 3 4 11 12 13 14 21 22 23 24
do
	./sort -a $algorithm -f $infile.txt -o $algorithm._$infile.txt -t -c -p
	continue
	done
echo "algorithm done" $algorithm;
	continue
done

exit 0
