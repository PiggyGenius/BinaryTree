#! /bin/bash

make binary

b=1
for length in 5 10 1000 2000 3000 5000
do
	echo "========== Benchmark $b =========="
	for i in `seq 1 5`
	do
		sleep 2
		time ./bin/computeABROpt $length benchmarks/benchmark$b.in > /dev/null
		echo "----------------------------------"
	done
	((b++))
done
