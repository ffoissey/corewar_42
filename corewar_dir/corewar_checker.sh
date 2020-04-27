#!/bin/bash

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]
then
	echo "./corewar_checker [[NB]/loop/one] [nb_dump] [champion.cor]{1...4}"
	exit 1;
fi

COR=../DOC/corewar

keyword=$1
nb_dump=$2

if [ "$keyword" == "loop" ]
then
	start=0
elif [ "$keyword" == "one" ]
then
	start=$nb_dump;
else
	start=$keyword;
fi
make -j8 d=1 > /dev/null
corewar_of=./result/test_corewar_origin.tmp
corewar_pf=./result/test_corewar_personal.tmp
diff_file=./result/diff.tmp

echo -e " - - - - - - - - - Start of Tests - - - - - - - - -\n"

rm -Rf result
mkdir result
for ((i=$start;i<=$nb_dump;++i))
do
	rm -f $corewar_of
	rm -f $corewar_pf
	if [ -z $4 ]
	then
		echo -n -e "\t./corewar -dump $i $3 $4"
		$COR -d $i $3 $4 > $corewar_of 2>&1
		../corewar -dump $i $3 $4 > $corewar_pf 2>&1
	elif [ -z $5 ]
	then
		echo -ne "\t ./corewar -dump $i $3 $4 $5"
		$COR -d $i $3 $4 $5 > $corewar_of 2>&1
		../corewar -dump $i $3 $4 $5 > $corewar_pf 2>&1
	elif [ -z $6 ]
	then
		echo -ne " ./corewar -dump $i $3 $4 $5 $6"
		$COR -d $i $3 $4 $5 $6 > $corewar_of 2>&1
		../corewar -dump $i $3 $4 $5 $6 > $corewar_pf 2>&1
	else 
		echo -ne "./corewar -dump $i $3"
		$COR -d $i $3 > $corewar_of 2>&1
		../corewar -dump $i $3 > $corewar_pf 2>&1
	fi
	diff $corewar_of $corewar_pf > $diff_file
	if [ -s $diff_file ]
	then
		echo -e "\t\033[31m[FAIL]\033[0m"
		echo -e "\n - - - - - - - - -  End of Tests  - - - - - - - - -\n"
		echo -e "\033[31mA difference was found in cycle $i !\033[0m"
		echo "Look at the diff file and the two output files in 'result' folder."
		exit 2
	else
		echo -e "\t\033[32m[OK]\033[0m"
	fi
	i=$((i++))
done
echo -e "\n\033[32mNo difference found! Good job !\033[0m"
#rm -Rf result
