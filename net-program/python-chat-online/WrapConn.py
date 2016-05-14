# -*- coding: utf-8 -*-
"""
Created on Sun Nov 24 11:03:49 2013

@author: huang_cj2
"""
import socket
import time

class WrapConn():
    def __init__(self, conn):
        self.conn = conn
        self.bufStr = ''
    
    def send(self, msg):
        self.conn.send(msg + '$')
    
    def recv(self, bufLength=1024):
        while True:
            msg, sep, self.bufStr = self.bufStr.partition('$')
            if sep:
                return msg
            else:
                self.bufStr = msg + self.conn.recv(bufLength)
    
    def close(self):
        self.conn.close()      
