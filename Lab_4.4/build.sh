#!/bin/bash
if [[ $OSTYPE == 'darwin'* ]]; then
  echo "$0: OS is MacOS"
  (mkdir -p out; cd out; cmake  -DCMAKE_BUILD_TYPE=debug -S .. -B $(pwd) && cmake --build $(pwd) --verbose -j $(( $(sysctl -n hw.logicalcpu) / 2 )) ) 
else # [[ $OSTYPE == 'linux'* ]]; then
  echo why
  (mkdir -p out; cd out; cmake  -DCMAKE_BUILD_TYPE=debug -S .. -B $(pwd) && cmake --build $(pwd) --verbose -j $(( $(nproc) / 2 )) )
fi
