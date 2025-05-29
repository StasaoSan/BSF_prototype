#!/bin/bash

WD="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

#USERVER=ghcr.io/userver-framework/ubuntu-22.04-userver
USERVER=ghcr.io/userver-framework/ubuntu-22.04-userver-pg-dev
#USERVER=userver/ubuntu-24.04

docker run --rm -it \
 -v $WD/BSF_prototype:/home/bsf \
 -p 8181:8080 \
 -w /home/bsf \
 --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
 $USERVER
