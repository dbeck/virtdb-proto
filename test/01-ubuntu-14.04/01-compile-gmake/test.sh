#!/bin/sh
cd /home/testuser
git clone https://github.com/starschema/virtdb-proto.git
cd /home/testuser/virtdb-proto
make -f proto.mk
echo MAKE_RETURNED: $?
