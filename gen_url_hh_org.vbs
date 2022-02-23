'If WScript.Arguments.Length > 0 Then
'   input = WScript.stdin.ReadAll()
'   WScript.stdout.write Mid(input, 2, Len(input)-5)   
'   WScript.Quit
'End If

'--------------------------------------------------------------------------
' initialisations
'--------------------------------------------------------------------------
Set settings = CreateObject("Scripting.Dictionary")
Set WshShell = CreateObject("WScript.Shell")
Set coll = CreateObject("System.Collections.ArrayList")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%TMP%")

'--------------------------------------------------------------------------
'   Dict work to save state of a current script
'   Can be stored in %TMP% folder
'--------------------------------------------------------------------------
Set oShell = CreateObject( "WScript.Shell" )
' create script settings folder if it not exists
folder_name=Split(WScript.ScriptName, ".")(0)
cmd="cmd /c mkdir " & """" & tmp_folder & "\" & folder_name & """" 
settings_path = tmp_folder & "\" & folder_name 
settings_file = settings_path & "\" & folder_name & ".settings"
oShell.run  cmd
'WScript.Echo settings_path

Function AppentTextFile(filename, text2)
	Dim utfStr

	Set stream = CreateObject("ADODB.Stream")
	stream.Open
	stream.Charset  = "utf-8"
	If fso.FileExists(filename) Then 	
		stream.LoadFromFile filename
	End If
	stream.Type     = 2 'text
	stream.Position = 0
	stream.Position = stream.Size
	stream.WriteText text2
	stream.SaveToFile filename, 2
	stream.Close
End Function

Function ParseDict(d, textdata)
	lines=Split(textdata, Chr(10))
	For each line in lines
		If Len(line) > 4 Then
		   parts=Split(line, "=")
		   
		   If ubound(parts) = 1 Then
		   ' WScript.Echo parts(0) 		   
			d(parts(0)) = parts(1)
		   End if
		End if
	Next 
End Function

Function ReadDict(d, filename)
	'read crc from file if exist
	If fso.FileExists(filename) Then 
		Set stream = CreateObject("ADODB.Stream")
		stream.Open
		stream.Type     = 2 'text
		stream.Position = 0
		stream.Charset  = "utf-8"
		stream.LoadFromFile filename
		textdata = stream.ReadText 	
		ParseDict d, textdata		
		stream.Close
	End If
End Function

Function WriteDict(d, filename)
	If fso.FileExists(filename) Then 
		fso.DeleteFile filename
	End If 	
	'save dict as string
	text2 = ""
	For Each objKey In d
		text2 = text2 & objKey & "=" & d(objKey) & + Chr(10)
	Next
	Dim utfStr
	Set stream = CreateObject("ADODB.Stream")
	stream.Open
	stream.Type     = 2 'text
	stream.Position = 0
	stream.Charset  = "utf-8"
	stream.WriteText text2
	stream.SaveToFile filename, 2
	stream.Close
End Function

Function UpdateDict(d, filename)
	text2 = ""
	For Each objKey In d
		text2 = text2 & objKey & "=" & d(objKey) & + Chr(10)
	Next
	AppentTextFile filename, text2	
End Function

Function StrConv(Text,SourceCharset,DestCharset)
  Set Stream=CreateObject("ADODB.Stream")
  Stream.Type=2
  Stream.Mode=3
  Stream.Open
  Stream.Charset=DestCharset
  Stream.WriteText Text
  Stream.Position=0
  Stream.Charset=SourceCharset
  StrConv=Stream.ReadText
End Function

Function ReadClipboardData()
	Set objHTML = CreateObject("htmlfile")
	ReadClipboardData = objHTML.ParentWindow.ClipboardData.GetData("text")
End Function

'--------------- MAKE ITERATION (update state) -----------------------------
SetLocale 1049
ReadDict settings, settings_file
Set o = settings
'If no prevoius settings 
if o("n_cycle") = "" Then
	o("number_of_pages") = 10
	o("flag_404") = 0
End If
o("n_cycle") = o("n_cycle") + 1	
o("current_page") = o("current_page")  + 1
if o("number_of_pages") = o("current_page") Then	

	o("letter") =  o("letter") + 1
End If

WriteDict o, settings_file

'------------------- EXTRACT URLS FROM HTML SOURCE OF A PAGE --------------
html = ReadClipboardData()
Set employers = CreateObject("Scripting.Dictionary") 
'1. найти строку вида /employer/4114876
Dim oRE, oMatches
Set oRE = New RegExp
oRE.Pattern = "[/]employer[/]([\d]+)" 
oRE.Global = True
Set oMatches = oRE.Execute(html)
For Each oMatch In oMatches
  'text2 = text2 + oMatch.Value  
  WScript.stdout.writeline 	oMatch.Value  
  id = oMatch.Value
  'WScript.stdout.writeline 	Mid(html, oMatch.FirstIndex - 8, 200)
  '2. откатится на -8 по строке
  chunk = Mid(html, oMatch.FirstIndex - 8, 200) 
  '3. parse_a_tag
  Dim oRE1, oMatches1
  Set oRE1 = New RegExp
  oRE1.Pattern = ">([\S ]+)</a>" 
  oRE1.Global = True
  Set oMatches1 = oRE1.Execute(chunk)  
  For Each m in oMatches1
	company = Mid(chunk, m.FirstIndex+2, Len(m.Value)-5)  
	WScript.stdout.writeline company
	'4. add dictioary key employers
    employers(id) = company  
  Next

Next
Wscript.Echo text2

UpdateDict employers, settings_path + "\employers.txt"
 
Wscript.Quit

'-------------------------------------------------------------------------- 

Function copy2clip(text)
  Set objShell = CreateObject("WScript.Shell")
  user=objShell.ExpandEnvironmentStrings("%USERPROFILE%")
  strPath = "cscript.exe //Nologo " & user & "\gen_url_hh.vbs arg1"
  cmd="cmd /c echo " & """" & text & """" & " | " & strPath & " | clip"
  objShell.run  cmd
End Function

Randomize ' Initialize random-number generator
page_number = Int((30) * Rnd() + 1 )   
url = "https://spb.hh.ru/employers_list?" & "&page=" & page_number
copy2clip(url)



