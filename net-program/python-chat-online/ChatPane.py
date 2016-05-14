# -*- coding: utf-8 -*-

import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import time

class ChatPane(QWidget):
    def __init__(self, hostUser, objectUser, conn, parent=None):
        super(ChatPane, self).__init__(parent)
        
        self.hostUser = hostUser
        self.objectUser = objectUser
        self.setWindowTitle(hostUser + "'s Dialog - To " \
                                     + objectUser)
        self.conn = conn
        
        self.msgContent = QTextEdit()
        self.msgContent.setReadOnly(True)
        
        self.msgEdit = QTextEdit()

        self.sendButton = QPushButton('Send')
        self.sendButton.clicked.connect(self.onSend)
        
        self.cancelButton = QPushButton('Cancel')
        self.cancelButton.clicked.connect(self.close)
        
        lay1 = QVBoxLayout()
        lay1.addStretch()
        lay1.addWidget(self.sendButton)
        lay1.addWidget(self.cancelButton)
        
        lay2 = QHBoxLayout()
        lay2.addWidget(self.msgEdit)
        lay2.addLayout(lay1)
        
        line = QFrame()
        line.setFrameStyle(QFrame.HLine|QFrame.Sunken)
        
        lay3 = QVBoxLayout()        
        lay3.addWidget(self.msgContent)
        lay3.addWidget(line)
        lay3.addLayout(lay2)
        
        self.setLayout(lay3)        
    
    def onSend(self):
        message = unicode(self.msgEdit.toPlainText()).encode('gbk')
        try:
            if self.conn!=None: self.conn.send(self.objectUser + '-' + message)
        except:
            QMessageBox.critical(self, 'Fatal Error', 'Server Disconnect')
            sys.exit(0)
        self.msgEdit.setPlainText('')
        self.displayMessage(self.hostUser, message)

    def displayMessage(self, user, message):
        message = message.decode('gbk')
        self.msgContent.append( time.strftime("%Y-%m-%d %X", time.localtime()) 
                                  + ' - ' + user + '\n' + message + '\n' )

    def closeEvent(self, event):
        self.hide()
        event.ignore()

def test():    
    app = QApplication(sys.argv)
    cp = ChatPane('asd','a',None)
    cp.show()
    sys.exit( app.exec_() )

if __name__ == '__main__':
    test()