Dim Response, nValue

Set coll = CreateObject("System.Collections.ArrayList")
Set coll_shuffled = CreateObject("System.Collections.ArrayList")

Set objHTML = CreateObject("htmlfile")
text = objHTML.ParentWindow.ClipboardData.GetData("text")

' Do something with the text
' text = replace(text, "you ", "you and your dog ")

' a = MsgBox(text,3,outString )


Dim objDictionary
Set objDictionary = CreateObject("Scripting.Dictionary")
objDictionary.CompareMode = vbTextCompare

Function AddingToList
    ' Add items
    ' coll.Add "Apple" 
    ' coll.Add "Watermelon"
	' coll.Add "Orange"
	' Splitting contents of clipboard by words
	a=Split(text,vbLf)
	For each x in a
		coll.Add x
	Next 
	For i = 0 To coll.Count - 1
		objDictionary.Add i, -1 
    Next

End Function

Function PrintToImmediateWindow(coll)

	Dim i
    For i = 0 To coll.Count - 1
        Wscript.Echo coll(i)
    Next
    
End Function

AddingToList()

Randomize

Dim count 
count = coll.Count

' Wscript.Echo "coll.Count ", count

For i = 0 To count - 1  
	random_number = Int((coll.Count) * Rnd() + 1 )   ' Initialize random-number generator
	coll_shuffled.Add(coll(random_number-1))
	coll.RemoveAt(random_number - 1) 
	' Wscript.Echo random_number
Next

' PrintToImmediateWindow(coll_shuffled)

Dim i
Dim text2

text2 = " "

For i = 0 To coll_shuffled.Count - 1
	text2 = text2 + coll_shuffled(i) 
Next

' Wscript.Echo text2

' a = MsgBox(text2,3,"Press Enter Blease" )

Set WShshell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%TMP%")
' Set wshSystemEnv = WShshell.Environment( "TMP" ) 
' Wscript.Echo tmp_folder
Dim a
'Set a = fso.CreateTextFile(tmp_folder + "\\1.txt", True)
'a.WriteLine(utfStr)
'a.WriteLine("a")
'a.WriteLine("b")
'a.WriteLine("c")
Dim utfStr
Set stream = CreateObject("ADODB.Stream")
stream.Open
stream.Type     = 2 'text
stream.Position = 0
stream.Charset  = "utf-8"
stream.WriteText text2
stream.SaveToFile tmp_folder + "\\1.txt", 2
stream.Close


If coll_shuffled.Count > 0 Then 
	For i = 0 To coll_shuffled.Count - 1	
		' a.WriteLine(StrConv(coll_shuffled(i),vbFromUnicode))
	Next	
End If	

