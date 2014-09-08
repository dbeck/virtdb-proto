#!/bin/sh
cd /home/testuser
git clone https://github.com/starschema/virtdb-proto.git
cd /home/testuser/virtdb-proto
gyp --depth=. proto.gyp
make
echo MAKE_RETURNED: $?
