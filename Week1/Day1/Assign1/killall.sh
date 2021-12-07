#!/bin/bash

echo "Killing all containers..."
containers=`docker ps | tail -n +2 | awk '{print $1}'\\`
if [[ -z $containers ]]
then
	echo "No containers found"
else
	docker container stop $containers\
		&& docker container prune\
		&& echo "Killed all containers."
fi
