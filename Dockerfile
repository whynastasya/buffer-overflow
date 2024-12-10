FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    nano \
    wget \
    curl \
    git \
    man \
    vim \
    && apt-get clean


RUN apt-get install -y \
    strace \
    ltrace \
    valgrind \
    clang-tools

WORKDIR /workspace

COPY ./src /workspace

CMD ["/bin/bash"]