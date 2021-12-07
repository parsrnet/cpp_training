#!/bin/bash
# Build new Image from Dockerfile
docker build -f Dockerfile -t dockerdev .

# Spin up new container
# We'll use the coreutil `realpath` to convert our relative path to an absolute path as to create a valid map

realpath=`realpath ./code`
docker run -d -it dockerdev bash

# Join to container
container=`docker ps | tail -1 | awk '{print $1}'`
docker exec -it --user dev $container bash
