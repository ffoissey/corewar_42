#!/bin/bash

ZAZ_ASM=../DOC/asm
MY_ASM=../asm

if [ -z $1 ]
then
	echo "Miss an argument: give a champion"
	echo "Usage: ./asm_checker.sh [champ.s]"
	exit 0
fi
make -j8 d=1
ARG=$1
file=`echo "${ARG%%.s}"`

$ZAZ_ASM $file.s && mv $file.cor $file.cor_asm
$MY_ASM $file.s
ARG=0
if [ -f $file.cor ]
then
	diff $file.cor $file.cor_asm
	ARG=$?
fi
rm -f $file.cor $file.cor_asm # Mute this line if you want keep .cor file
exit $ARG
