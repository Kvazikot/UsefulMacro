Dim Response, nValue

Set coll = CreateObject("System.Collections.ArrayList")
Set coll_shuffled = CreateObject("System.Collections.ArrayList")

Set objHTML = CreateObject("htmlfile")
text = objHTML.ParentWindow.ClipboardData.GetData("text")

Dim oRE, oMatches
Set oRE = New RegExp
oRE.Pattern = "[(]more[)]([\r\n\w ]+)?" 
oRE.Global = True
Set oMatches = oRE.Execute(text)
For Each oMatch In oMatches
  'WScript.Echo "Match: " & oMatch.Value & " At: " & CStr(oMatch.FirstIndex + 1)
  'WScript.Echo Mid(text, oMatch.FirstIndex + 7, oMatch.Length - 5)
  text2 = text2 + Mid(text, oMatch.FirstIndex + 7, oMatch.Length - 5) 
Next

Set WShshell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%TMP%")
If fso.FileExists(tmp_folder + "\\1.txt") Then 
  fso.DeleteFile tmp_folder + "\\1.txt"
End If 

Dim utfStr
Set stream = CreateObject("ADODB.Stream")
stream.Open
stream.Type     = 2 'text
stream.Position = 0
stream.Charset  = "utf-8"
stream.WriteText text2
stream.SaveToFile tmp_folder + "\\1.txt", 2
stream.Close

Set objShell = CreateObject("Shell.Application")
objShell.ShellExecute "notepad", tmp_folder + "\\1.txt", "", "runas", 1

WScript.Quit

