import win32gui
import win32con
import os
import time
os.system('start notepad.exe')
time.sleep(1)
hwnd = win32gui.FindWindow('Notepad', None)
print(hwnd)
win32gui.SetWindowPos(hwnd, win32con.HWND_TOPMOST, 100, 100, 300, 200, 0) 
