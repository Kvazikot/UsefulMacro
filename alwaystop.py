import win32gui
import win32con
import os

os.system('notepad.exe')
sleep(2)
hwnd = win32gui.FindWindow('Notepad', None)
win32gui.SetWindowPos(hwnd, win32con.HWND_TOPMOST, 100, 100, 300, 200, 0) 
