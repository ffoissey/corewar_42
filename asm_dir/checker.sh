#!/bin/bash
if [ -z $1 ]
then
	echo "Miss an argument: give a champion"
	exit 0
fi
make -j8 d=1
ARG=$1
file=`echo "${ARG%%.s}"`

../doc/asm $file.s && mv $file.cor $file.cor_asm
../asm $file.s
ARG=0
if [ -f $file.cor ]
then
	diff $file.cor $file.cor_asm
	ARG=$?
fi
rm -f $file.cor $file.cor_asm
exit $ARG
