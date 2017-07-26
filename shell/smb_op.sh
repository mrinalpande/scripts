#!/bin/bash

# use nmap to check for all clients with running
# smb service. Smb service ports 445, 139


for ip in $(seq 1 255);do
        nmap -p445,139 -Pn  10.11.1.$ip --open
done
