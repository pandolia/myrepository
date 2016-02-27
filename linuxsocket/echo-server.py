#!/usr/bin/env python
# -*- coding: utf-8 -*-
"USAGE: {progname} <port>"

#from SocketServer import BaseRequestHandler, TCPServer
#import sys, socket
#
#class EchoHandler(BaseRequestHandler):
#    def handle(self):
#        print "Client connected:", self.client_address
#        self.request.sendall(self.request.recv(2**16))
#        self.request.close()
#
#if len(sys.argv) != 2:
#    print __doc__.format(progname=sys.argv[0])
#else:
#    TCPServer(('', int(sys.argv[1])), EchoHandler).serve_forever()

from socket import *
import sys

BLOCKSIZE = 32

def handleConnection(client_sock):
    while True:
        data = client_sock.recv(BLOCKSIZE)
        if not data:
            client_sock.close()
            break
        client_sock.sendall(data)

if len(sys.argv) != 2:
    print __doc__.format(progname=sys.argv[0])
    sys.exit(0)

server_sock = socket(AF_INET, SOCK_STREAM)
server_sock.bind(('', int(sys.argv[1])))
server_sock.listen(5)
while True:
    client_sock, client_addr = server_sock.accept()
    print "Client connected:", client_addr
    handleConnection(client_sock)
