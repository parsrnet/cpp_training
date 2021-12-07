#!/bin/bash

echo "Killing all containers..."
containers=`docker ps | tail -n +2 | awk '{print $1}'\\`
if [[ -z $containers ]]
then
	echo "No containers found"
else
	docker rm -f $containers\
		&& echo "Killed all containers."
fi
