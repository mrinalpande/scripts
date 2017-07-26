#!/bin/bash

# shell script to ping the hosts in a ip range that are up
# may not show some computers as sometimes computers
# do not respond to icmp ping requests

for ip in $(seq 0 255); do
ping 10.11.1.$ip -c1 | grep "bytes from"| cut -d" " -f4|cut -d":" -f1 &
done
