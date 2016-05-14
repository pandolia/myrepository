# -*- coding: utf-8 -*-

import socket
import threading
import sys
import time
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from ChatPane import ChatPane

class Receiver(threading.Thread):
    def __init__(self, ulPane):
        super(Receiver, self).__init__()
        self.ulPane = ulPane
        self.setDaemon(True)

    def run(self):
        while True:
            try:                
                msg = self.ulPane.conn.recv(1024)
            except:
                self.ulPane.msgIn.emit('')
                break
            self.ulPane.msgIn.emit(msg.decode('gbk'))

class UsersListPane(QListWidget):
    msgIn = pyqtSignal(str)

    def __init__(self, hostUser, conn, parent = None):
        super(UsersListPane, self).__init__(parent)
        self.setWindowTitle(hostUser + "'s Friend List")        
        self.hostUser = hostUser
        self.conn = conn
        self.usersSet = {}

        self.itemDoubleClicked.connect(self.onUserDclk)

        self.msgIn.connect(self.onMsgIn)

    def onMsgIn(self, msg):
        msg = unicode(msg).encode('gbk')
        if( msg == '' ):
            QMessageBox.critical(self, 'Fatal Error', 'Server Disconnected')
            self.close()
        else:
            user, message = msg.split('-')
            if message == 'Login':
                self.addUser(user)
            elif message == 'Logout':
                self.removeUser(user)
            else:
                self.displayMessage(user, message)
    
    def addUser(self, user):
        userItem = QListWidgetItem(user, self)        
        self.addItem(userItem)
        userChatPane = ChatPane(self.hostUser, user, self.conn, self)
        userChatPane.setWindowFlags(Qt.Window)
        self.usersSet[user] = (userItem, userChatPane)
    
    def removeUser(self, user):
        self.takeItem( self.row(self.usersSet[user][0]) )
        self.usersSet[user][1].close()
        del self.usersSet[user]

    def displayMessage(self, user, message):
        self.usersSet[user][1].displayMessage(user, message)
    
    def onUserDclk(self, item):
        self.usersSet[str(item.text())][1].show()

def test():
    app = QApplication(sys.argv)
    ulp = UsersListPane('aaa','')
    ulp.addUser('asd')
    ulp.addUser('qwe')
    ulp.show()
    sys.exit( app.exec_() )

if __name__ == '__main__':
    test()