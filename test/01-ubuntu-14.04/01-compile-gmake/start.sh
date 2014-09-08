#!/bin/sh

IMAGE_NAME="virtdb-proto-test:01-ubuntu-14.04-01-compile-gmake"
TEST_CMD="docker run --rm -t -v $PWD/test.sh:/home/testuser/test.sh $IMAGE_NAME /home/testuser/test.sh"

DOCKER_BUILD=`docker build --force-rm=true -t "$IMAGE_NAME" . 2>&1`

if [ $? -ne 0 ]
then
  echo "ERROR during docker build " $DOCKER_BUILD
  exit 101
fi

X=`$TEST_CMD`
RESULT=`echo $X | grep -c "MAKE_RETURNED: 0"`

if [ $RESULT -ne 1  ]
then
  echo "ERROR during execution: $X"
  exit 100
else
  echo "OK"
  return 0
fi


