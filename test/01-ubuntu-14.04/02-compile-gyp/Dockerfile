FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install -y git git-core
RUN apt-get install -y make
RUN apt-get install -y protobuf-compiler
RUN apt-get install -y g++ 
RUN apt-get install -y libprotobuf-dev
RUN apt-get install -y libprotoc-dev
RUN apt-get install -y pkg-config
RUN apt-get install -y gyp
RUN adduser --system --disabled-password --shell /bin/bash testuser
USER testuser
