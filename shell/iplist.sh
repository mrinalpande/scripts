#!/bin/bash

# Generate ip list for rev_dns.sh

for ip in $(seq 1 255);do
echo 192.168.1.$ip
done; > ips
