import PyQt5
from PyQt5.QtGui import QScreen
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QGuiApplication

def dialog():
    mbox = QMessageBox()         
    mbox.exec_()

app = QApplication([])
# scr = QScreen()
#print(QGuiApplication.screens())
scr = QGuiApplication.screens()[0]
print(scr.geometry())
w = QWidget()
w.resize(300,300)
w.setWindowTitle("asasas")
w.show()
#print(scr.geometry(scr))
app.exec_()
