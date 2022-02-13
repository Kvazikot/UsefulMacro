Dim Response, nValue

Set WshShell = CreateObject("WScript.Shell")

Set coll = CreateObject("System.Collections.ArrayList")
Set coll_shuffled = CreateObject("System.Collections.ArrayList")
Set keywords = CreateObject("System.Collections.ArrayList")
Set questions = CreateObject("System.Collections.ArrayList")
text = ReadClipboardData()
Set WShshell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%USERPROFILE%")

arg1 = ""
arg2 = ""

Function ReadClipboardData()
	Set objHTML = CreateObject("htmlfile")
	ReadClipboardData = objHTML.ParentWindow.ClipboardData.GetData("text")
End Function

Function ParseWorldList(text, coll, sep)
	If Len(text) = 0 Then Wscript.Quit
	a=Split(text,  sep )
	For each x in a
		If Len(x) > 2 Then
		   coll.Add x
		End if
	Next 
End Function

text1 = "" 


Function LoadKeywords()
	Set fso = CreateObject("Scripting.FileSystemObject")
	'read keywords from file if its exist
	If arg2 = "clip" Then
	  text1 = ReadClipboardData()
	End If
	If fso.FileExists(arg2) Then 
		Set stream = CreateObject("ADODB.Stream")
		stream.Open
		stream.Type     = 2 'text
		stream.Position = 0
		stream.Charset  = "utf-8"
		stream.LoadFromFile arg2
		text1 = stream.ReadText 
		stream.Close
	End If
End Function	

Function copy2clip(text)
  Set objShell = CreateObject("WScript.Shell")
  cmd="cmd /c echo "  & text  & " | clip"
  objShell.run  cmd
End Function

Function select_rand_word()
	sep = Chr(10)
	ParseWorldList text1, keywords, sep
	'Wscript.Echo text1
	'Wscript.Echo "number of keywords: " & keywords.Count
	' select random keyword and copy it to clipboard
	Randomize
	n = Int( Rnd() * keywords.Count + 1)
	copy2clip keywords(n)
End Function	

Function extract_quora_questions()
	Dim Response, nValue

	Set coll = CreateObject("System.Collections.ArrayList")
	Set coll_shuffled = CreateObject("System.Collections.ArrayList")

	Dim oRE, oMatches
	Set oRE = New RegExp
	oRE.Pattern = "([\w\S ]+[?])[\r\n]+" 
	oRE.Global = True
	Set oMatches = oRE.Execute(text)
	For Each oMatch In oMatches
	  text2 = text2 + oMatch.Value
	Next

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
	stream.SaveToFile tmp_folder + "\\quora_questions.txt", 2
	stream.Close

	'Set objShell = CreateObject("Shell.Application")
	'objShell.ShellExecute "notepad", tmp_folder + "\\quora_questions.txt", "", "runas", 1
End Function

Function select_quora_question()
	
	'read crc from file if exist
	If fso.FileExists(tmp_folder + "\\quora_questions.txt") Then 
		Set stream = CreateObject("ADODB.Stream")
		stream.Open
		stream.Type     = 2 'text
		stream.Position = 0
		stream.Charset  = "utf-8"
		stream.LoadFromFile tmp_folder + "\\quora_questions.txt"
		text1 = stream.ReadText 
		stream.Close
	End If

	ParseWorldList text1, questions, Chr(10)
	' select random keyword and copy it to clipboard
	Randomize
	n = Int( Rnd() * questions.Count + 1)
	text2 = ""
	If n < questions.Count Then
	  text2 = questions(n)
	End If
	
	'Wscript.Echo text2
	
	Dim utfStr
	Set stream = CreateObject("ADODB.Stream")
	stream.Open
	stream.Charset  = "utf-8"
	stream.LoadFromFile tmp_folder + "\\selected_questions.txt"
	stream.Type     = 2 'text
	stream.Position = 0
	stream.Position = stream.Size
	stream.WriteText text2
	stream.SaveToFile tmp_folder + "\\selected_questions.txt", 2
	stream.Close

	'Set objShell = CreateObject("Shell.Application")
	'objShell.ShellExecute "notepad", tmp_folder + "\\selected_questions.txt", "", "runas", 1

End Function

'No arguments
If WScript.Arguments.Length = 0 Then
  str = "Help on parametres: unknow_genius.vbs function_name path_to_keywords"
  str = str + Chr(13) + "example1:" + Chr(13) + Chr(13)  +  " unknow_genius.vbs select_rand_word c:\common_english_shuffled.txt"
  str = str + Chr(13) + "this will select random word from a list contained in file c:\common_english_shuffled.txt with separator line end"
  str = str + Chr(13) + "example2:" + Chr(13) + Chr(13)  +  " unknow_genius.vbs extract_quora_questions c:\common_english_shuffled.txt"
  str = str + Chr(13) + "this will parse quora search results page contained in clipboard in plain text format (not html!) and copies questions to file %TMP%/quora_questions.txt "
  'Wscript.Echo str
End If

' parse first argumetn -function name
If WScript.Arguments.Length > 0 Then
	arg1 = WScript.Arguments.Item(0)
End If

If WScript.Arguments.Length > 1 Then	
	arg2 = WScript.Arguments.Item(1)
End If


'Wscript.Echo arg1
'Wscript.Echo arg2
LoadKeywords()

If arg1 = "select_rand_word" Then select_rand_word()
If arg1 = "extract_quora_questions" Then extract_quora_questions()
If arg1 = "select_quora_question" Then select_quora_question()

Wscript.Quit
















