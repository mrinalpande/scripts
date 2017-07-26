#!/usr/bin/python

### Python script to connect to a pop server
### and check if it responds to USER and PASS parameters
### By sending a random username test and password test

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
	print "\nStarting..."
	s.connect(('192.168.1.105',110))
	data = s.recv(1024)
	print data
	s.send('USER test' +'\r\n')
	data = s.recv(1024)
	print data

	s.send('PASS test\r\n')
	data = s.recv(1024)
	print data

	s.close()
	print('\ndone')

except:
	print('Could not connect')

