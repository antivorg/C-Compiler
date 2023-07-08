
numberOfTokens=10

src=../../../src/lexing.c\ ../../../inc/lexing.h\ unittest.c
out=tests.out

if [ $# -eq 0 ]
then
	gcc $src -o $out
	./tests.out $numberOfTokens
	rm *.out
elif [ $1 = "Wall" ] || [ $1 = "wall" ]
then
	gcc -Wall $src -o $out
	./tests.out $numberOfTokens
	rm *.out	
elif [ $1 = "debug" ]
then
	gcc -g -Wall $src -o $out
	./tests.out $numberOfTokens
else
	echo "Invalid Argument"
fi
