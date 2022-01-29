Dim Response, nValue

Set coll = CreateObject("System.Collections.ArrayList")
Set coll_shuffled = CreateObject("System.Collections.ArrayList")

Set objHTML = CreateObject("htmlfile")
text = objHTML.ParentWindow.ClipboardData.GetData("text")
Set d = CreateObject("Scripting.Dictionary")
Set WShshell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%TMP%")

' take input from backup because in clipboard spelling errors from previuos run
' If fso.FileExists(tmp_folder + "\\1_bak.txt") Then 
  ' Set file = fso.OpenTextFile (tmp_folder + "\\1_bak.txt", 1)
  ' row = 0
  ' Do Until file.AtEndOfStream
    ' text2 = text2 + file.Readline
  ' Loop
  ' file.Close
' End If

' insertions of adjastment keys
d("a") = "swqz"
d("s") = "adwx"
d("d") = "esfc"
d("f") = "grcv"
d("g") = "aswd"
d("h") = "gyuj"
d("j") = "hukm"
d("k") = "juio"
d("l") = "kiop"
d("q") = "aswa"
d("w") = "sdrw"
d("e") = "esfc"
d("r") = "grcv"
d("t") = "tvbh"
d("y") = "ytfv"
d("u") = "hkun"
d("i") = "ijml"
d("o") = "oki;"
d("z") = "axsx"
d("x") = "cdsz"
d("c") = "ccnx"
d("v") = "ijml"
d("b") = "oki;"
d("m") = "ytfv"
d(",") = "hkun"

d(";") = "l'op"
d("'") = "[p;]"
d("я") = "фычс"
d("ч") = "яысв"
d("с") = "вамп"
d("м") = "сапи"
d("и") = "мпрт"
d("т") = "риоь"
d("ь") = "толб"
d("б") = "ьлдю"
d("ю") = "бдж."
d("ф") = "ыцйя"
d("ы") = "фцус"
d("в") = "уыск"
d("а") = "кмсе"
d("п") = "имае"
d("р") = "нпит"
d("о") = "рнгл"
d("л") = "огшд"
d("д") = "жщшо"
d("ж") = "дщзх"
d("э") = "жщзх"
d("й") = "фыцв"
d("у") = "вакы"
d("к") = "авпе"
d("е") = "капр"
d("н") = "епро"
d("г") = "олше"
d("ш") = "олдщ"
d("щ") = "лдщн"
d("з") = "джхх"
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
	' Splitting contents of clipboard by ws
	a=Split(text,  Chr(13))
	For each x in a
		If Len(x) > 2 Then
		   coll.Add x
		End if
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


Function AddSpellingErrors(in_text)
  Randomize
  Dim i
  Dim tmp  
  str = ""
  i = 2

  
  'strString = "As a bitwise operator, And returns 1 if the compared bits in both expressions are 1"
  strString = in_text
  
  Do While i < Len(strString) 
  	wi = Mid(strString,i-1,1)
    wi_1 = Mid(strString,i,1)
	str_add = ""
    random_number = Int( 100 * Rnd()  )  ' 0-100	
	If (random_number < 5) and (wi_1 <> " ") Then	' probability of delete 0.25
	  str_add = wi_1	  
	End If
	If (random_number > 85) and (wi_1 <> " ") Then	 ' probability of insert 0.25 
	  if  d.Exists(wi_1) Then
		 n = 1 + (random_number mod 3)
	     str_add = Mid(d(wi_1),n,1) & wi_1 & wi
	  End If	
	End If
	If StrComp("",str_add) = 0 Then
	  str_add = wi & wi_1
    End If	 
	str = str + str_add
	i = i + 2
  Loop 
  AddSpellingErrors = str    
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

text2 = ""

For i = 0 To coll_shuffled.Count - 1
  random_number = Rnd()   ' Initialize random-number generator
  line = coll_shuffled(i)
  if (i mod 2) = 0  Then
    line = AddSpellingErrors(coll_shuffled(i))
  End If
  text2 = text2 + line + Chr(13)
Next


' RestoreFile()

'text = AddSpellingErrors(text2)

'Wscript.echo text
'Wscript.echo text2



' If fso.FileExists(tmp_folder + "\\1.txt") Then 
  ' fso.CopyFile tmp_folder + "\\1.txt", tmp_folder + "\\1_bak.txt"
' End If 

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


