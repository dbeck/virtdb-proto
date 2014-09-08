#!/bin/sh


TEST_DIR=`pwd`
for i in [0-9][0-9]*
do
  echo testing in $* / $i
  cd $i
  ./start.sh $* / $i
  cd $TEST_DIR
done
  
