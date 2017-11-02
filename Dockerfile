FROM ubuntu:trusty


RUN apt-get update -y && \
    apt-get install -y gcc g++ make build-essential \
    curl m4 openssh-client

COPY download /tmp/download

USER nobody
WORKDIR /tmp

RUN ./download

COPY build /tmp/build

RUN ./build i486-linux-musl
RUN ./build x86_64-linux-musl
RUN ./build aarch64-linux-musl
RUN ./build arm-linux-musleabi
RUN ./build arm-linux-musleabihf

