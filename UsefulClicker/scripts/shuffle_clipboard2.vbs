Dim Response, nValue

Set coll = CreateObject("System.Collections.ArrayList")
Set coll0 = CreateObject("System.Collections.ArrayList")
Set coll_shuffled = CreateObject("System.Collections.ArrayList")

Set objHTML = CreateObject("htmlfile")
' take clipboard text
text = objHTML.ParentWindow.ClipboardData.GetData("text") 
Set d = CreateObject("Scripting.Dictionary")
Set crcD = CreateObject("Scripting.Dictionary")
Set WShshell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")
Set oShell = CreateObject( "WScript.Shell" )
user=oShell.ExpandEnvironmentStrings("%UserName%")
tmp_folder=oShell.ExpandEnvironmentStrings("%TMP%")
crc_of_clipboard = "0000AA00"
crc_from_file = "0000AA00"

'read crc from file if exist
If fso.FileExists(tmp_folder + "\\iluminati_file.txt") Then 
	Set stream = CreateObject("ADODB.Stream")
	stream.Open
	stream.Type     = 2 'text
	stream.Position = 0
	stream.Charset  = "utf-8"
	stream.LoadFromFile tmp_folder + "\\iluminati_file.txt"
	crc_from_file = stream.ReadText 
	stream.Close
End If

'Wscript.Echo crc_of_clipboard
'Wscript.Quit

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
d("p") = "ol-;"
d("z") = "axsx"
d("x") = "cdsz"
d("c") = "ccnx"
d("v") = "ijml"
d("b") = "oki;"
d("m") = "ytf "
d("n") = "bhmj"
d(",") = "hkun"
d(";") = "l'op"
d(":") = "::op"
d("""") = """"""""""
d("'") = "[p;]"
d("я") = "фычz"
d("ч") = "яысв"
d("с") = "вамп"
d("м") = "сапи"
d("и") = "мпрт"
d("т") = "риоь"
d("ь") = "толб"
d("б") = "ьлдю"
d("ю") = "бдж."
d("ф") = "ыцйa"
d(".") = "...."
d(",") = ",,,,"
d("?") = "&?&$"
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
d("й") = "фыцq"
d("ц") = "вакы"
d("у") = "вакы"
d("к") = "авпе"
d("е") = "капр"
d("н") = "епро"
d("г") = "олше"
d("ш") = "олдщ"
d("щ") = "лдщн"
d("з") = "джхх"
d("х") = "з-ъх"
d("ъ") = "ъхэх"

For Each objKey In d
  d(UCase(objKey)) = UCase(d(objKey))
Next
  
' Do something with the text
' text = replace(text, "you ", "you and your dog ")

' a = MsgBox(text,3,outString )

Function shr(plValue, pbBits)
' Shift bits to the right by <pbBits>
 shr = plValue \ (2 ^ pbBits)
End Function

Function Crc32(psString)
Dim sValues, alCRCTable, lCRC
Dim l
    sValues = "&h0,&h77073096,&hEE0E612C,&h990951BA,&h076DC419,&h706AF48F,&hE963A535,&h9E6495A3,&h0EDB8832,&h79DCB8A4,&hE0D5E91E,&h97D2D988,&h09B64C2B,&h7EB17CBD,&hE7B82D07,&h90BF1D91,&h1DB71064,&h6AB020F2,&hF3B97148,&h84BE41DE,&h1ADAD47D,&h6DDDE4EB,&hF4D4B551,&h83D385C7,&h136C9856,&h646BA8C0,&hFD62F97A,&h8A65C9EC,&h14015C4F,&h63066CD9,&hFA0F3D63,&h8D080DF5,&h3B6E20C8,&h4C69105E,&hD56041E4,&hA2677172,&h3C03E4D1,&h4B04D447," _
        + "&hD20D85FD,&hA50AB56B,&h35B5A8FA,&h42B2986C,&hDBBBC9D6,&hACBCF940,&h32D86CE3,&h45DF5C75,&hDCD60DCF,&hABD13D59,&h26D930AC,&h51DE003A,&hC8D75180,&hBFD06116,&h21B4F4B5,&h56B3C423,&hCFBA9599,&hB8BDA50F,&h2802B89E,&h5F058808,&hC60CD9B2,&hB10BE924,&h2F6F7C87,&h58684C11,&hC1611DAB,&hB6662D3D,&h76DC4190,&h01DB7106,&h98D220BC,&hEFD5102A,&h71B18589,&h06B6B51F,&h9FBFE4A5,&hE8B8D433,&h7807C9A2,&h0F00F934,&h9609A88E,&hE10E9818," _
        + "&h7F6A0DBB,&h086D3D2D,&h91646C97,&hE6635C01,&h6B6B51F4,&h1C6C6162,&h856530D8,&hF262004E,&h6C0695ED,&h1B01A57B,&h8208F4C1,&hF50FC457,&h65B0D9C6,&h12B7E950,&h8BBEB8EA,&hFCB9887C,&h62DD1DDF,&h15DA2D49,&h8CD37CF3,&hFBD44C65,&h4DB26158,&h3AB551CE,&hA3BC0074,&hD4BB30E2,&h4ADFA541,&h3DD895D7,&hA4D1C46D,&hD3D6F4FB,&h4369E96A,&h346ED9FC,&hAD678846,&hDA60B8D0,&h44042D73,&h33031DE5,&hAA0A4C5F,&hDD0D7CC9,&h5005713C,&h270241AA," _
        + "&hBE0B1010,&hC90C2086,&h5768B525,&h206F85B3,&hB966D409,&hCE61E49F,&h5EDEF90E,&h29D9C998,&hB0D09822,&hC7D7A8B4,&h59B33D17,&h2EB40D81,&hB7BD5C3B,&hC0BA6CAD,&hEDB88320,&h9ABFB3B6,&h03B6E20C,&h74B1D29A,&hEAD54739,&h9DD277AF,&h04DB2615,&h73DC1683,&hE3630B12,&h94643B84,&h0D6D6A3E,&h7A6A5AA8,&hE40ECF0B,&h9309FF9D,&h0A00AE27,&h7D079EB1,&hF00F9344,&h8708A3D2,&h1E01F268,&h6906C2FE,&hF762575D,&h806567CB,&h196C3671,&h6E6B06E7," _
        + "&hFED41B76,&h89D32BE0,&h10DA7A5A,&h67DD4ACC,&hF9B9DF6F,&h8EBEEFF9,&h17B7BE43,&h60B08ED5,&hD6D6A3E8,&hA1D1937E,&h38D8C2C4,&h4FDFF252,&hD1BB67F1,&hA6BC5767,&h3FB506DD,&h48B2364B,&hD80D2BDA,&hAF0A1B4C,&h36034AF6,&h41047A60,&hDF60EFC3,&hA867DF55,&h316E8EEF,&h4669BE79,&hCB61B38C,&hBC66831A,&h256FD2A0,&h5268E236,&hCC0C7795,&hBB0B4703,&h220216B9,&h5505262F,&hC5BA3BBE,&hB2BD0B28,&h2BB45A92,&h5CB36A04,&hC2D7FFA7,&hB5D0CF31," _
        + "&h2CD99E8B,&h5BDEAE1D,&h9B64C2B0,&hEC63F226,&h756AA39C,&h026D930A,&h9C0906A9,&hEB0E363F,&h72076785,&h05005713,&h95BF4A82,&hE2B87A14,&h7BB12BAE,&h0CB61B38,&h92D28E9B,&hE5D5BE0D,&h7CDCEFB7,&h0BDBDF21,&h86D3D2D4,&hF1D4E242,&h68DDB3F8,&h1FDA836E,&h81BE16CD,&hF6B9265B,&h6FB077E1,&h18B74777,&h88085AE6,&hFF0F6A70,&h66063BCA,&h11010B5C,&h8F659EFF,&hF862AE69,&h616BFFD3,&h166CCF45,&hA00AE278,&hD70DD2EE,&h4E048354,&h3903B3C2," _
        + "&hA7672661,&hD06016F7,&h4969474D,&h3E6E77DB,&hAED16A4A,&hD9D65ADC,&h40DF0B66,&h37D83BF0,&hA9BCAE53,&hDEBB9EC5,&h47B2CF7F,&h30B5FFE9,&hBDBDF21C,&hCABAC28A,&h53B39330,&h24B4A3A6,&hBAD03605,&hCDD70693,&h54DE5729,&h23D967BF,&hB3667A2E,&hC4614AB8,&h5D681B02,&h2A6F2B94,&hB40BBE37,&hC30C8EA1,&h5A05DF1B,&h2D02EF8D"
    alCRCTable = Split(sValues, ",")
    lCRC = &HFFFFFFFF
    For l = 1 To Len(psString)
        lCRC = alCRCTable(((lCRC And &HFFFF) Xor Asc(Mid(psString, l, 1))) And &HFF) Xor shr(lCRC, 8)
    Next 
    lCRC = lCRC Xor &HFFFFFFFF
    
    Crc32 = lCRC
End Function

Dim objDictionary
Set objDictionary = CreateObject("Scripting.Dictionary")
objDictionary.CompareMode = vbTextCompare

Function AddingToList
	a=Split(text,  Chr(10) )
	For each x in a
		If Len(x) > 2 Then
		   coll.Add x
		   coll0.Add x
		End if
	Next 

End Function

' Calculating crc of clipboard
crc_of_clipboard = Hex(Crc32(text))
' Wscript.Echo crc_of_clipboard
'Wscript.Quit

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
	If (random_number < 7) and (wi_1 <> " ") Then	' probability of delete 0.25
	  str_add = wi_1	  
	End If
	If (random_number > 95) and (wi_1 <> " ") Then	 ' probability of insert 0.25 
	  if  d.Exists(wi_1) Then
		 n = 1 + (random_number mod 3)
	     str_add = Mid(d(wi_1),n,1) & wi_1 & wi
      Else 
	     n = 1 + (random_number mod 8)
	     str_add = Mid("aleuvnshb",n,1) & wi
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
' shuffle strings
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
If crc_from_file = crc_of_clipboard Then
	For i = 0 To coll_shuffled.Count - 1  
	   text2 = text2 + coll_shuffled(i) + Chr(10)
	Next   
Else 
   ' Wscript.Echo "Aplying spelling errors"
	For i = 0 To coll_shuffled.Count - 1  
	   text2 = text2 + AddSpellingErrors( coll_shuffled(i) ) + Chr(10)
	Next   	
End If	

'Wscript.Echo "crc from clipboard not equals to 1.txt crc. Adding spelling errors"
'Wscript.Echo "crc_from_file = " & crc_from_file
'Wscript.Echo "crc_of_clipboard = " & crc_of_clipboard


text = ""
For i = 0 To coll0.Count - 1
   text = text + coll0(i)
Next   

'Wscript.echo "cols: " & coll_shuffled.Count
'Wscript.echo "1 line of file: " + Hex(Crc32(text2))

'write crc from file if exist
If fso.FileExists(tmp_folder + "\\iluminati_file.txt") Then 
  fso.DeleteFile tmp_folder + "\\iluminati_file.txt"
End If  

Set stream = CreateObject("ADODB.Stream")
stream.Open
stream.Type     = 2 'text
stream.Position = 0
stream.Charset  = "utf-8"
stream.WriteText Hex(Crc32(text2))
stream.SaveToFile tmp_folder + "\\iluminati_file.txt", 2
stream.Close



'Wscript.echo text
'Wscript.echo text2

If fso.FileExists(tmp_folder + "\\1.txt") Then 
  fso.DeleteFile tmp_folder + "\\1.txt"
End If 

Dim utfStr
Set stream2 = CreateObject("ADODB.Stream")
stream2.Open
stream2.Type     = 2 'text
stream2.Position = 0
stream2.Charset  = "utf-8"
stream2.WriteText text2
stream2.SaveToFile tmp_folder + "\\1.txt", 2
stream2.Close


