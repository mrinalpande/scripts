### SMTP user verify
### Provided with file of usernames
### this script uses the SMTP VRFY command 
### to check if the user exists.

#!/usr/bin/python

import socket
import sys

if len(sys.argv) != 2:
	print "Usage: smtp.py <filename>"
	sys.exit(0)

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connect=s.connect(('192.168.1.105',25))
banner=s.recv(1024)
print banner

f = open(sys.argv[1])
names = f.readlines()
f.close()

for name in names:
	s.send('VRFY ' + name + '\r')
	result=s.recv(1024)
	if result.startswith('250'):
		print result
s.close()

