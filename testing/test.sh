#!/bin/bash

if [ -n "$1" ] && [ -n "$2" ]; then
    echo "World simulaotr's host is $1"
    echo "UPS server's host is $2"
else
    echo "Usage: ./test.sh <world_simulator_host> <ups_host> <option>"
fi

# 0: make and run program.
# 1: rebuild program
# 2: rebuild libprotocpl.a and then rebuild program
if [ -n "$3" ]; then
  if [ $3 = 2 ]; then
    echo "rebuild libprotocpl.a and then rebuild program"
    ./cleanfiles.sh
    protoc -I=protocolfiles --cpp_out=protocolcodes protocolfiles/world_ups.proto
    protoc -I=protocolfiles --cpp_out=protocolcodes protocolfiles/world_amazon.proto
    protoc -I=protocolfiles --cpp_out=protocolcodes protocolfiles/ups_amazon.proto
    cd protocolcodes && make && cd ../
    make
  elif [ $3 = 1 ]; then
      echo "rebuild program"
      make clean && make
  else
      echo "make and run program"
      make
  fi
fi

./AmazonServer "$1" "$2"
