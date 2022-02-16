' укажите здесь идентификатор своего резюме 
HH_ID = "170669dfff0865af3b0039ed1f6b6d3752674b"

If WScript.Arguments.Length > 0 Then
   input = WScript.stdin.ReadAll()
   WScript.stdout.write Mid(input, 2, Len(input)-5)   
   WScript.Quit
End If

Function copy2clip(text)
  Set objShell = CreateObject("WScript.Shell")
  user=objShell.ExpandEnvironmentStrings("%USERPROFILE%")
  strPath = "cscript.exe //Nologo " & user & "\gen_url_hh.vbs arg1"
  cmd="cmd /c echo " & """" & text & """" & " | " & strPath & " | clip"
  objShell.run  cmd
End Function

Randomize ' Initialize random-number generator
page_number = Int((10) * Rnd() + 1 )   
url = "https://hh.ru/search/vacancy?resume=" & HH_ID & "&page=" & page_number
copy2clip(url)



