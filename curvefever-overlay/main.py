import sys
from PyQt4 import QtGui, QtCore

class TopWindow(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setWindowFlags(
            QtCore.Qt.WindowStaysOnTopHint |
            QtCore.Qt.FramelessWindowHint |
            QtCore.Qt.X11BypassWindowManagerHint
            )
        self.setGeometry(QtGui.QStyle.alignedRect(
            QtCore.Qt.LeftToRight, QtCore.Qt.AlignRight,
            QtCore.QSize(340, 768),
            QtGui.qApp.desktop().screenGeometry()))

        self.label = QtGui.QLabel(self)
        self.label.resize(self.size())
        self.redraw()

        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.redraw)
        self.timer.start(30)

    def redraw(self):
        pixmap = QtGui.QPixmap.grabWindow(QtGui.QApplication.desktop().winId())
        self.label.setPixmap(pixmap.copy(340, 0, 340, 768))        

    def mousePressEvent(self, event):
        QtGui.qApp.quit()

app = QtGui.QApplication(sys.argv)
topWindow = TopWindow()
topWindow.show()
app.exec_()
