#!/usr/bin/env python
# -*- coding: utf-8 -*-
'USAGE: {progname} <server> <port> <message>'

from socket import *
import sys

if len(sys.argv) != 4:
    print __doc__.format(progname=sys.argv[0])
    sys.exit(0)


sock = socket(AF_INET, SOCK_STREAM)
sock.connect((sys.argv[1], int(sys.argv[2])))
message, msglen = sys.argv[3], len(sys.argv[3])
sock.sendall(message)
received, BLOCKSIZE = 0, 32
print 'Received: ',
while received < msglen:
    data = sock.recv(BLOCKSIZE)
    print data,
    received += len(data)
sock.close()