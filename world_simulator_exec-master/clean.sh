#!/bin/bash
sudo docker kill $(sudo docker ps -q) # stop all containers
sudo docker rm $(sudo docker ps -a -q) # remove all containers 
sudo docker rmi $(sudo docker images -q) # remove all images
sudo docker network prune # remove all networks
sudo docker volume prune # remove all volumes 