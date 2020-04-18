#!/bin/bash

if [ -z $1 ] || [ -z $2 ]
then
	echo "./corewar_checker nb_dump champion.cor"
	exit 1;
fi

make -j8 d=1
../DOC/corewar -d $1 $2 > test.tmp
../corewar -dump $1 $2 > test2.tmp
diff test.tmp test2.tmp
rm test.tmp
rm test2.tmp
