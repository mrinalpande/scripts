#!/bin/bash

# Simple Zone transfer script, attempts to do a
# DNS zone transfer

if [ -z "$1" ]; then
	echo "[*] Simple Zone transfer script"
exit 0
fi

for server in $(host -t ns $1 |cut -d" " -f4);do
	host -l $1 $server |grep "has address"
done
