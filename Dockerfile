FROM ubuntu:16.10
MAINTAINER Swen Kooij <swen@sectorlabs.ro>

RUN apt-get update
RUN apt-get install -y build-essential mesa-common-dev
RUN apt-get install -y cmake git git-gui vim nano sudo
RUN apt-get install -y qt5-default qtdeclarative5-dev qtcreator 
RUN apt-get install -y libmagick++-dev libmagickcore-dev libmagickwand-dev libcurl4-openssl-dev

RUN export uid=1000 gid=1000 && \
    mkdir -p /home/developer && \
    echo "developer:x:${uid}:${gid}:Developer,,,:/home/developer:/bin/bash" >> /etc/passwd && \
    echo "developer:x:${uid}:" >> /etc/group && \
    mkdir -p /etc/sudoers.d && \
    echo "developer ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/developer && \
    chmod 0440 /etc/sudoers.d/developer && \
    chown ${uid}:${gid} -R /home/developer

USER developer
ENV HOME /home/developer


