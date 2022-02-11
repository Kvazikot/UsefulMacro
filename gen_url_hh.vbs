Function copy2clip(text)
  Set objShell = CreateObject("WScript.Shell")
  cmd="cmd /c echo " & """" & text & """" & " | clip"
  objShell.run  cmd
End Function

Randomize ' Initialize random-number generator
page_number = Int((10) * Rnd() + 1 )   
url = "https://hh.ru/search/vacancy?resume=170669dfff0865af3b0039ed1f6b6d3752674b&page=" & page_number
copy2clip(url)