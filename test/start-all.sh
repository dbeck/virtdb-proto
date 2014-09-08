#!/bin/sh

TOP_DIR=`pwd`
for i in [0-9][0-9]*
do
  echo testing in $TOP_DIR '/' $i 
  cd $i
  ./start-all.sh $TOP_DIR '/' $i
  cd $TOP_DIR
done
  
