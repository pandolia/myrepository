# -*- coding: utf-8 -*-

import socket
import threading
import time
from WrapConn import WrapConn
from Hostip import hostname, port

userPass = {"Kate":"123", "Jane":"123", "Mary":"123", 'More':'123'}
senssionsSet = {}

def check(user, password):
    try:
        return userPass[user] == password
    except KeyError:
        return False

def broadcast(msg):
    for session in senssionsSet.values():
        try:
            session.conn.send(msg)
        except:
            pass
    print msg

def post(user, msg):    
    try:
        senssionsSet[user].conn.send(msg)
    except:
        pass
    print msg + '->' + user

def login(senssion):
    while True:
        user, password = senssion.conn.recv(1024).split('-')
        if( check(user, password) ):
            if user in senssionsSet.keys():
                senssion.conn.send('Occupied')
            else:
                senssion.conn.send('Right')
                for otherUser in senssionsSet.keys():
                    senssion.conn.send( otherUser + '-Login' )
                senssion.user = user
                broadcast( user + '-Login' )
                senssionsSet[user] = senssion
                break
        else:
            senssion.conn.send('Wrong')

def logout(senssion):
    try:
        senssion.conn.close()
    except:
        pass
    del senssionsSet[senssion.user]
    broadcast( senssion.user + '-Logout' )

class Senssion(threading.Thread):
    def __init__(self, conn_addr):
        super(Senssion, self).__init__()
        self.conn, self.addr = conn_addr
        self.conn = WrapConn(self.conn)
        self.addr = str(self.addr)

    def run(self):
        try:
            login(self)
        except:
            return

        while True:
            try:
                userTo, msg = self.conn.recv(1024).split('-')
            except:
                logout(self)
                return
            post(userTo, self.user + '-' + msg)

def main():
    s = socket.socket()
    s.bind((hostname, port))
    s.listen(20)
    i = 0
    while i < 20:
        Senssion( s.accept() ).start()
        i = i + 1

if __name__ == '__main__':
    main()