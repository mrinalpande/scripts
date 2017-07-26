#!/usr/bin/python

### Pinging script to check which host are up.
### Will only print the ip's of the host that are up
### Using "ping" command of the terminal.
### Some computers do not respond to icmp ping requests
### So may give no output for them.


import os

#ip range to check for hosts.
hostname = "192.168.1."
i=0

while i<255:
	print(os.system("ping -c 1 " + hostname+`i`+ "| grep 'bytes from'| cut -d' ' -f4|cut -d':' -f1"))
	i = i+1