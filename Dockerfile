# Using the Ubuntu image (our OS)
FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y software-properties-common

# Update package manager (apt-get) 
# and install (with the yes flag `-y`)
# Python and Pip
RUN apt-get update && apt-get install -y \
    python3.8 \
    python3-pip \
    build-essential

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt install -y gcc-11 \
    cmake \
    pstack
 
RUN DEBIAN_FRONTEND=noninteractive apt install -y clang-11

RUN apt-get update && apt-get install -y \
    git

RUN apt-get update && apt-get install -y apt-utils

RUN apt-get update && \
    apt-get -qy full-upgrade && \
    apt-get install -qy curl && \
    apt-get install -qy curl && \
    curl -sSL https://get.docker.com/ | sh

RUN apt-get update && apt-get install -y vim
RUN apt-get update && apt-get install -y fzf
RUN apt install -y tig
