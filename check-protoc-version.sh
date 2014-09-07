#!/bin/sh

REF_VERSION=$1

if [ "X" = "X$REF_VERSION" ]
then
  echo usage: check-protoc-version.sh '<minimum-version>'
  echo "     " where: minimum-version is like x.y.z
fi


REF_MAJOR=`echo $REF_VERSION | cut -f1 -d'.'`
REF_MINOR=`echo $REF_VERSION | cut -f2 -d'.'`
REF_INSIG=`echo $REF_VERSION | cut -f3 -d'.'`
REF_VERSION=`expr $REF_MAJOR '*' 10000 '+' $REF_MINOR '*' 100 '+' $REF_INSIG`

PROTOC=`which protoc`
ACT_VERSION=`$PROTOC --version | cut -f2 -d' '`

ACT_MAJOR=`echo $ACT_VERSION | cut -f1 -d'.'`
ACT_MINOR=`echo $ACT_VERSION | cut -f2 -d'.'`
ACT_INSIG=`echo $ACT_VERSION | cut -f3 -d'.'`
ACT_VERSION=`expr $ACT_MAJOR '*' 10000 '+' $ACT_MINOR '*' 100 '+' $ACT_INSIG`

if [ $ACT_VERSION -ge $REF_VERSION ]
then
  echo "OK"
  exit 0
else
  echo "protocol buffer compiler $PROTOC is not supported because it looks too old: version=$ACT_VERSION required=$REF_VERSION"
  exit 100
fi

 
