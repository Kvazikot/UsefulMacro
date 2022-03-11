
## Общее описание UsefulClicker
ПРоект начался с описания недостатков программы AutoMouseClick, который был оформлен в докуенте 
[Недостатки Auto Mouse Clicker by MurGee](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/docs/%D0%9F%D1%80%D0%B8%D0%BD%D1%86%D0%B8%D0%BF%D0%B8%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5_%D0%BD%D0%B5%D0%B4%D0%BE%D1%81%D1%82%D0%B0%D1%82%D0%BA%D0%B8_AutoMouseClick.MD)
Постепенно я начал вести список фич которые я бы лично реализовал в своем кликере


## Таблица действий UsefulClicker. Компонент QTreeView.
Таблица отображает xml документ загруженный из одного из фалов подкаталога xml.
Читай схему в документе [sheme2.xml](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/xml/sheme2.xml)
Каждый тег этого документа отображается в таблице.
В файле настроек [settings.ini](https://github.com/Kvazikot/UsefulMacro/blob/master/UsefulClicker/settings/UsefulClicker.ini)
можно задать фильтры для отображения тегов в ячейках таблицы.
hideCodeTags - прячет все кодовые теги
hideAllNonClickerTags = оставляет только теги внутренних функций UsefulClicker

Описание виджетов читай в дрокументе [widgets/README.MD](https://github.com/Kvazikot/UsefulMacro/tree/master/UsefulClicker/widgets#readme)


 ## Стркуктура каталогов UsefulClicker
```
├──  scripts
│    ├──  youtube_search_by_list_shuffle_v2ю.py
│    ├──  shuffle_strings.vbs
│    ├──  extract_uppercase_pharazes.vbs
│    ├── gen_url_hh.vbs
├── docs
│   ├── README.MD
├──  xml
│   ├── rutracker_org_torrent_downloader.xml
│   ├── shit_head_hunter_wit_hurl_generation.xml
│   ├── piratebay_torrent_downloader.xml
├──  temp
├──  settings
├──  data
├──  lists
│   ├── medical_search_list_rus.txt
│   ├── 6000_inventions_20_century_eng
│   ├── ommon_english_shuffled.txt
├──  data
├──  images
    ├── Capture_15.01._16.03.20020.jpg
    ├── Screenshot_15.01._16.03.20020.jpg
``` 
## XML схема UsefulClicker
``` 
<?xml version="1.0"?>

<!--
при запуске UsefulClicker устанавливаются следующие переменные окружения
UsefulClicker_xml = "(CWD)\xml"    -  каталог где он ищет include
UsefulClicker_scripts = "(CWD)\scripts"    - каталог куда он сохраняет скрипты из этой схемы
UsefulClicker_settings = "%APPDATA%\Roaming\UsefulClicker"
-->
<xml>
<include> 1 sheme1.xml </include>
<include> sheme2.xml </include>

<code source_name="block.py" lang="python" >
  import random
  print( random.randint(0, 13) )
  A = 100
  def Wave(t):
     x = A * math.sin(t)
     return x
</code>

<shell name="cmd" bg="1" showConsole="1">
start / B date
</shell>


<py_call name=""/>

<func_call name="SetUrl" arg0="https://www.hh.ru" comment="set hh url" />

<func name = "SetUrl" arg0="https://www.youtube.com/results?search_query=" comment="function sets url in chrome browser" >
   <arg n="0" comment="url"> https://www.youtube.com/results?search_query </arg>
   <click area="Rect(0,1,200,200)"/>
   <click x="10" y="20"/>
   <dblclick x="10" y="20"/>
   <mouseup x="10" y="20" delay_fixed="1000" delay_random="300" repeat="10" />
   <mousedown x="10" y="20" />
   <hotkey> ctrl + C </hotkey>
   <type> this is text to insert . There $(arg0) is python variable  </type>
   <keydown arg0="F6"/>
   <keyup arg0="F6"/>
   <scrollup x="10" y="20"/>
   <scrolldown />
</func>

 <!--
<main>
<code name="init" >
mouseX = Wave(t_cycle)
</code>

<func_call name="SetUrl" />
<func_call name="Wave" arg0="t_cycle * $(dt)" />
</main>
-->
</xml>
``` 


