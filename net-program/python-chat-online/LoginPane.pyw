# -*- coding: utf-8 -*-

import socket
import threading
import sys
import time
from PyQt4.QtCore import *
from PyQt4.QtGui import *

from Hostip import hostname, port
from WrapConn import WrapConn
from UsersListPane import Receiver, UsersListPane

class LoginPane(QWidget):
    def __init__(self, parent = None):
        super(LoginPane, self).__init__(parent)
        userLabel = QLabel('User name:')
        self.userEdit = QLineEdit()
        passLabel = QLabel('Password:')
        self.passEdit = QLineEdit()
        self.passEdit.setEchoMode( QLineEdit.Password )
        loginButton = QPushButton('Login')
        registerButton = QPushButton('Register')
        cancelButton = QPushButton('Cancel')

        lay1 = QGridLayout()
        lay1.addWidget(userLabel, 0, 0)
        lay1.addWidget(self.userEdit, 0, 1)
        lay1.addWidget(passLabel, 1, 0)
        lay1.addWidget(self.passEdit, 1, 1)

        lay2 = QHBoxLayout()
        lay2.addWidget(loginButton)
        lay2.addWidget(registerButton)
        lay2.addWidget(cancelButton)

        layout = QVBoxLayout()
        layout.addLayout(lay1)
        layout.addLayout(lay2)
        self.setLayout(layout)

        QObject.connect(loginButton, SIGNAL('clicked()'), self.onLogin)
        QObject.connect(registerButton, SIGNAL('clicked()'), self.onRegister)
        QObject.connect(cancelButton, SIGNAL('clicked()'), self, SLOT('close()'))

        self.conn = None

    def onLogin(self):
        if self.conn == None:
            try:
                self.conn = socket.socket()
                self.conn.connect((hostname, port))
                self.conn = WrapConn(self.conn)
            except:
                QMessageBox.critical(self, 'Fatal Error', 'Server Unavailable')
                sys.exit(0)

        try:
            self.conn.send( str(self.userEdit.text()) + '-'
                              + str(self.passEdit.text()) )
            answer = self.conn.recv(1024)
        except:
            QMessageBox.critical(self, 'Fatal Error', 'Server Disconnect')
            sys.exit(0)
            
        if answer == 'Right':
            self.hide()
            ulPane = UsersListPane(str(self.userEdit.text()), self.conn, self)
            ulPane.setWindowFlags(Qt.Window)
            ulPane.show()
            Receiver(ulPane).start()
        else:
            QMessageBox.warning(self, 'Warning:', answer + ' Code')

    def onRegister(self):
        self.userEdit.setText('onRegister')

def main():
    app = QApplication(sys.argv)
    lp = LoginPane()
    lp.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()