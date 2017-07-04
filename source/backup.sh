#!/bin/bash
cp $1 $2
if [ $? != 0 ]
then
	echo 'backup failed!'
	return -1
else
	echo 'backup succeed!'
	cat /dev/null > $1
fi
