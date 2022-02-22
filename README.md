  + - - - + - + - -
  + - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
  + - + - + email: vsbaranov83@gmail.com  <br>
  + - + - + github: http://github.com/Kvazikot/BallPark  <br>
```
                            )            (
                           /(   (\___/)  )\
                          ( #)  \ ('')| ( #
                           ||___c\  > '__||
                           ||**** ),_/ **'|
                     .__   |'* ___| |___*'|
                      \_\  |' (    ~   ,)'|
                       ((  |' /(.  '  .)\ |
                        \\_|_/ <_ _____> \______________
                         /   '-, \   / ,-'      ______  \
                b'ger   /      (//   \\)     __/     /   \
                                            './_____/
```              
  
  
# UsefulMacro
Цель этого репозитория: Исследовательская. 

## Автоматический поиск работы на head hunter
Скрипт отсылает ваше резюме случайным работтодателям на сайте hh.ru
По теории вероятности вы увеличите шансы найти работу если каждый день будете рассылать свое резюме 200 разным работодателям. 
200 это лимит за сутки на сайте hh.ru. Причем не важно даже что они вам предлагают.

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/hh_screenshot.png)
<br/>рис1. Страница hh.ru при переполнении числа откликов

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/hh_screenshot2.png)
<br/>рис2. Где найти id вашего резюме?

Для hh работает только в разрешении 1920x1080 и на 100% зуме страницы. Поскольку там поиск картинки "Откликнуться" и он не нейросетевой
Для запуска сценария вам потребуется программа AutoMouseClick by MurGee.com 
Ее можно [скачать](https://www.murgee.com/auto-mouse-click/download/setup.exe) здесь https://www.murgee.com/auto-mouse-click/
1. Установите Auto Mouse Click by MurGee.com
2. Откройте в браузере сайт hh.ru
3. Скиньте папку ["Images to Search On Screen"](https://github.com/Kvazikot/UsefulMacro/archive/refs/heads/master.zip) на диск c:\ (в корень диска)
4. В проводнике windows (Win + E) забейте в адресную строку %USERPROFILE%
5. Положите скрипт генерирующий url-адреса [gen_url_hh.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/gen_url_hh.vbs) в каталог %USERPROFILE%
6. Откройте файл [gen_url_hh.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/gen_url_hh.vbs) блокнотом  
7. Найдите строчку HH_ID = "170669dfff0865af3b0039ed1f6b6d3752674b"
8. Замените "170669dfff0865af3b0039ed1f6b6d3752674b" на id своего резюме
9. Id вашего резюме можно найти на сайте hh. Зайдите в поиск и найдите линк "прямая ссылка" (см. рис 2)
10. Нажмите ctrl + S
11. Запустите [скрипт shit_head_hunter_wit_hurl_generation.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/shit_head_hunter_wit_hurl_generation.mamc) кнопкой Start или комбинацией ctrl + alt + F6

Если вы хотите максимально широкий веер поиска к примеру 357 303 вакансии, то сделайте следующее
1. Откройте файл [gen_url_hh.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/gen_url_hh.vbs) блокнотом  
2. Найдите строчку url = "https://hh.ru/search/vacancy?resume=" & HH_ID & "&page=" & page_number
3. Замените ее на url = "https://hh.ru/search/vacancy?area=113&area=2&employment=full&employment=probation&employment=part&employment=project&employment=volunteer&industry=43&industry=44&industry=41&industry=7.540&industry=7.539&industry=7.541&industry=8.484&professional_role=4&professional_role=5&professional_role=62&professional_role=70&professional_role=8&professional_role=33&professional_role=58&professional_role=76&professional_role=84&professional_role=88&professional_role=93&professional_role=110&professional_role=22&professional_role=90&professional_role=95&professional_role=116&professional_role=120&professional_role=26&professional_role=36&professional_role=37&professional_role=38&professional_role=53&professional_role=80&professional_role=87&professional_role=125&professional_role=135&professional_role=27&professional_role=28&professional_role=49&professional_role=63&professional_role=79&professional_role=66&professional_role=119&professional_role=21&professional_role=32&professional_role=89&professional_role=130&professional_role=10&professional_role=12&professional_role=25&professional_role=34&professional_role=73&professional_role=96&professional_role=104&professional_role=107&professional_role=112&professional_role=113&professional_role=114&professional_role=121&professional_role=124&professional_role=126&professional_role=13&professional_role=20&professional_role=41&professional_role=55&professional_role=98&professional_role=103&professional_role=139&professional_role=1&professional_role=2&professional_role=3&professional_role=68&professional_role=71&professional_role=99&professional_role=15&professional_role=19&professional_role=24&professional_role=29&professional_role=42&professional_role=64&professional_role=65&professional_role=133&professional_role=17&professional_role=23&professional_role=101&professional_role=132&professional_role=6&professional_role=51&professional_role=54&professional_role=57&professional_role=83&professional_role=97&professional_role=105&professional_role=106&professional_role=122&professional_role=129&professional_role=44&professional_role=45&professional_role=46&professional_role=48&professional_role=82&professional_role=85&professional_role=86&professional_role=109&professional_role=111&professional_role=115&professional_role=128&professional_role=141&professional_role=143&professional_role=144&professional_role=31&professional_role=52&professional_role=59&professional_role=78&professional_role=102&professional_role=131&professional_role=9&professional_role=35&professional_role=77&professional_role=123&professional_role=127&professional_role=7&professional_role=43&professional_role=56&professional_role=60&professional_role=61&professional_role=92&professional_role=138&professional_role=75&professional_role=134&professional_role=11&professional_role=91&professional_role=14&professional_role=30&professional_role=47&professional_role=100&professional_role=108&professional_role=39&professional_role=67&professional_role=81&professional_role=72&professional_role=74&professional_role=94&professional_role=140&professional_role=69&professional_role=117&professional_role=118&professional_role=16&professional_role=18&professional_role=50&professional_role=136&professional_role=137&professional_role=142&professional_role=145&professional_role=146&professional_role=40&schedule=fullDay&schedule=flexible&schedule=remote&schedule=shift&search_field=name&search_field=company_name&forceFiltersSaving=true&hhtmFrom=vacancy_search_list"
4. Найдите строчку page_number = Int((10) * Rnd() + 1 ) 
5. Замените на page_number = Int((200) * Rnd() + 1 ) 


## Второй сценарий для youtube
[сценарий 2](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube_search_by_list_shuffle_v2.mamc)
Сценарий работает на разрешении экрана Full HD т.е. 1980x1080
Это уже не макрос, а сценарий.
Он работает без иммитации траектории мыши как у реального пользователя.
Этот сценарий основывается на клике в случайную точку внутри прямоугольного окна.
Работает несколько побыстрее предыдущего
Он делает случайны скролл результатов поиска. Вы можете выставить задержи и настроить скрипт сами.
Или быть может у вас получиться что-то болеее интересное, я был бы рад если кто-то из вас поделился своими результатами с сообществом

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube_search_by_list.png)
рис 1. Режим разделенного пополам экрана (справа - блокнот, слева - браузер с youtube)
Запуск кнопкой Start или комбинацией ctrl + alt + F6

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/yotube_player_mode2.png)
рис 2. Youtube player mode (ширина видео = 1/2 ширины экрана)


## Третий сценарий для youtube с перемешиванием списка.
Сценарий работает на разрешении экрана Full HD т.е. 1980x1080

Для запуска макроса вам потребуется программа AutoMouseClick by MurGee.com 
Ее можно [скачать](https://www.murgee.com/auto-mouse-click/download/setup.exe) здесь https://www.murgee.com/auto-mouse-click/
1. Установите Auto Mouse Click by MurGee.com
2. Разделяете экран как на скриншоте. Для этого я разделяю экран на две части, по горизонтали пополам. Открываю блокнот(Notepad.exe) в левой части экрана (комбинация клавиш WIN + CAPS LOCK + LEFT) Открываю браузер хром в правой части экрана (комбинация клавиш WIN + CAPS LOCK + RIGHT)
3. В youtube плеере сделайте так чтобы рекомендуемые видео были внизу (т.е. чтобы видеоокно по ширине было в половину ширины экрана)
4. Откройте ключевые слова в блокноте (Notepad.exe или Notepad++)
5. В проводнике windows (Win + E) забейте в адресную строку %USERPROFILE%
6. Положите скрипт перемешивающий строки [shuffle_clipboard.vbs](https://github.com/Kvazikot/UsefulMacro/raw/master/shuffle_clipboard.vbs) в каталог %USERPROFILE%
7. Проверьте что расширение у файла shuffle_clipboard.vbs именно .vbs, а не txt, иначе он не запустится.
8. Запустите [youtube_search_by_list_shuffle_v2.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube_search_by_list_shuffle_v2.mamc) кнопкой Start или комбинацией ctrl + alt + F6

Если вам не нравится что программа вносит случаные ошибки в ваш список ключевых фраз, 
то используйте [эту версию shuffle_clipboard.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/6ac0ab5b5273aacfde10d046d6bdb9488677f378/shuffle_clipboard.vbs) без spelling errors

Примечание: Если вы как и я используете Notepad++. ТО удостоверьтесь что в настройках выставлено тихое(slient) обновление файла

## Известные проблемы этого скрипта
Иногда может быть заблокирован временный файл. 
Это происходит если после перемешивания слов список не обновляется в окне блокнота.
Чтобы решить эту проблему нажмите Win, введите cmd
В консоле наберите команду, которая удалит временный файл

```del /F %TMP%\1.txt```


## Четвертый сценарий для youtube. Работа сразу с несколькими окнами параллельно

В данный момент наша доблесная команда трудится не покладая рук над новой версией
сценария который будет работать с несколькими окнами ютьюба.
В планах также адаптация под другие разрешения экрана отличные от Full HD 1980x1080

## Списки ключевых фраз для поиска
в каталоге youtube этого репозитория содержаться списки для поиска:

* [список "сленг поколения z"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/z_gen_slang.txt)
* [список "фанат Unity"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/unity_fan_list.txt)
* [список "общеупотребимые английские слова"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/common_english_shuffled.txt)
* [список "водопроводчик"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/plumber_keywords.txt)
* [список "психический"](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/mentalist_list.txt)
* [список "смелость города берет"](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/courage_list.txt)
* [список "новости политики"](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/search_news_list.txt)
* [список "Astronomy, a star"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/astronomy_the_stars_list.txt)
* [вопросы из mail.ru по термину "конфуцианство"](https://otvet.mail.ru/search/%D0%BA%D0%BE%D0%BD%D1%84%D1%83%D1%86%D0%B8%D0%B0%D0%BD%D1%81%D1%82%D0%B2%D0%BE/)
* [список "im not a man of two many faces"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/medical_search_list_rus.txt)
* [список "6001 изобретений Конфуция"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/6000_inventions_confucius_20_century.txt)

Списки вопросов по астрономии и инженерингу я взял с quora.com по ключевому слову: 
"NASA" "System enginering" "Electrical Enginering" "Linux"
Для вычленения вопросов из вывода поисковика quora цезарь чикен макнагетс дарит вам скрипт
[quora_extract_questions.vbs](https://github.com/Kvazikot/UsefulMacro/blob/master/quora_extract_questions.vbs)
Он берет на входе строку из буффера обмена, выделяет вопросы и запускает блокнот с ними

## Как быстро получить список вопросов в области в которой вы полный дилетант.
1. Заходите на [квору](https://www.quora.com/search?q=engine%20repair) или на [mail.ru вопросы](https://otvet.mail.ru/search/%D0%BA%D0%B0%D0%BA_%D0%BF%D0%BE%D0%B7%D0%BD%D0%B0%D0%BA%D0%BE%D0%BC%D0%B8%D1%82%D1%81%D1%8F_%D1%81_%D0%B6%D0%B5%D0%BD%D1%89%D0%B8%D0%BD%D0%BE%D0%B9/)
2. Забиваете в поиск интересующий термин
3. ctrl + a, ctrl + c
4. запускаете мой супер пупер огненный скрипт [extract_questions.vbs](https://github.com/Kvazikot/UsefulMacro/blob/master/extract_questions.vbs)
5. дальше можно их скармливать ютубу или любому другому поисковику
6. для полноты эксперимента советую загребать оттудава вопросы из абсолютно неизвестной вам области знания

Медицинские симптомы взяты из Оксфордовского мед справочника и википедии.
Мед справочник лежит на z-lib.org 

## Выбор ключевых слов из разных кластеров. Загрузка вопросов из кворы по этим словам.
![image](http://intelligentonlinetools.com/blog/wp-content/uploads/2017/07/Kmeans-CLustering-S1-dataset--300x211.png)
[в этом репозитории](https://github.com/rezacsedu/Clustering_wikipedia_articles) 
находится готовое решение по кластеризации статей википедии. Обьединение их по определенным категориям.
Новые списки я буду делать так чтобы они лежали в одном кластере или в одной категории.
Потом можно брать ключевые слова из сводки статьи, например с помощью модели keyBERT. 
Дальше находить по этим словам вопросы в кворе. 
Для чего я попробую написать скрипт который составляет большой список вопросов на разные темы, используя базу quora.
В конечных скриптах лучше обойтись без использования пайтона если использовать сохраненные кластеры, готовые датасеты и частотные таблицы.

## Дополнительные сценарии
Еще в этом репозитории есть следущие сценарии (все они работают тоже с перемешиванием списка):
* Поиск в яндексе [yandex__search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex__search_shuffle_v0.mamc)
* Поиск в яндексе [yandex_news_search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex_news_search_shuffle_v0.mamc)
* [скрипт obi_stroi_hypermarket.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/obi_stroi_hypermarket.mamc) для поиска разных стройматериалов на сайте гипермаркета OBI он работает со [этим](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/obi_list.txt) списком
* vlc_random_pitch - скрипт для vlc который периодически меняет основную частоту звука, чтобы не было понятно у какго какой социальный статус.
* [rutracker_org downloader](https://github.com/Kvazikot/UsefulMacro/raw/master/rutracker_org_torrent_downloader.mamc)
* [piratebay downloader (adapted for qbittorrent)](https://github.com/Kvazikot/UsefulMacro/raw/master/piratebay_qbittorrent_downloader.mamc)
* [Поиск в duck duck go](https://github.com/Kvazikot/UsefulMacro/raw/master/duck_duck%20.mamc)


Известная проблема с яндексом. Иногда скрипт закрывает все вкладки и всете с ними окно браузера.
Лечится это пока созданием нескольих окон комбинацией ctrl + N

## Выводы по ютьюбу
НА данный омент 11.46 1.31.2022 у меня получился телевизор который сам преключает каналы.
В принципе сюда можно добавить контроль внимания телезрителя. Т.е. если контент совсем не нравится, человек отварачивает голову и программа ставится на паузу т.е. не переключает каналы. Как то так.

## Контроль внимания пользователя через веб камеру. Gaze direction
Этот вообще военный подход в истребителях давно применяется выбор цели взглядом. Нужно курить в сторону инфракрасных датчиков зрачков. Но и нейросетевой метод на основе CNN может принести некоторые результаты. Тут вопрос только в калибровке системы под конкретные условия в плане диапазонов углов. 
Что накладывает некоторые требования к оператору который все это будет настраивать
Также здесь можно собрать некие данные по тому что реально интересует пользователя и манипулирует ли ютьюб вниманием пользователя. 
Или пользователи заказывают музыку. 
Цель этой нацчно-исследовательской работы можно переформулировать как попытку найти ответ на вопрос "Пользователь управляет ютубом или ютуб пользователем?"
Но использование следящей за пользователем системы не обязательно превращает нас в фашистов и сторонников оруэловской дистопии.
Если подумать философски, то фашисты сделали много полезного для человечества. Не буду приводить пример вы сами можете их найти в интернете.
В каждом из нас сидит частичка фашиста и парная ему его античастичка хиппи.
Я лично не хочу роли фашиста из страны фашистов статусом ниже, который все время проигрывает фашисту статусом выше.
После чего он сушит штаны и готовит новые чтобы показать в твиттере как он снова обделался, за что получить свой кусок колбасы.

## Промотка видео наклоном головы. Обратное обучение с подкреплением. Обучение дикарей не знающих языка как в фильме "пятый элемент".
Используюя нейросеть CNN наподобии [deepgaze](https://github.com/mpatacchiola/deepgaze)
Можно управлять плеером ютуба используя наклон головы пользователя.
НУ а если пользователь вообще не знает как управлять видео плеером. 
Мы можем найти некую функцию по движениям его головы, т.е. подстроится под его движения. 
Это может быть полезно если вы пытаемся делать [устройство](https://github.com/Kvazikot/BallPark/wiki/Time-capsule) которое обучает людей языку, которого они не знают.

## Интерфейс выбора ключевых слов. Интерфейс выбора формы вопроса.
Во время экспериментов с обезьяной Канзи исследователи использовали таблички со словами, чтобы обучить ее языку.
Им удалось достичь определенных успехов, научить е более 500 словам.
Я готов перенять опыт зоослингвистов в этой работе и разработать две формы лдля выбора ключевых слов.
Слова будут появляться на глинянных плиток разного размера с прогресс баром, который будет показывать 
сколько человек щелкал на какое-то слово. Слова перемешиваются скриптом shuffle_words.
После выбора слова обезьяне предлагают щелкнуть на один из вариатов обобщенных мета вопросов 
Вторая форма нужна чтобы сформировать вопрос к поисковому движку ютуба.
НА продежении всеей сессии обучения ведется подсчет статистики, 
те ключевые слова которые чаще всего выбирал человек окрашиваются в ярко коричневый цыет.
Можно делать морфинг какой-то картинки (раздевание картинки из плейбоя), которая
будет стимулировать выьброс дофамина. Картинка должна быть знакома человеку. 
Новые девушки из playboy рисуются сбоку плитки. 
Новые картинки должны вызывать интерес к изучению новых слов

```

-------------------------- +++-
 [частота выбора таблички = 30%]   +
 |              |
 |Плейбой image |     СЛОВО     |
 |   45% nude   |   Progressbar |
--------------------------------|
рис 34. формат глинянной таблички из первой формы выбора ключевого слова

                -------------
                 Where ? 
                 -------------\
                                \
                                  \
                                    \
  ----------------------              \
   What is?                             \   ^
  -----------------------------------|    (   )  |--------------------------------------                                    
                                            v                  How ? 
                                          /                   -------------------------     
                                        /                      
                                      /
              ------------------    /
               Build ?            /
               -----------------/

рис 34. Форма выбора вопроса
```
![image](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/IMAGES/time_capsule_lang_gui._ver5.png)

рис 64. Форма выбора вопроса


[![image](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/KANZI.png)](https://youtu.be/wRM7vTrIIis)
рис 44. Интерфейс Канзи

![image](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/IMAGES/KANZI_BOARD.png)
рис 45. Интерфейс Канзи

## Дальнейшие планы
В этой работе применяются классические варварские методы. 
В том смысле что вам не требуется знание о том что такое хтмли, джейсоны и даже вам не нужно знать как работает стек протоколов OSI.
При желании вы можете работать с удаленными машинами в правом окне хрома. Для этого вам все же надо будет почитать чисто поверхностно про то что такое wsl, ssh и X server.
В одной голове все не уместится.
В правом окне может быть окно клиентской машины VcXsrv X Server. 
Конечно настоящий инженер должен знать все. Но мы живем в эпоху перманентного цейтнота от которого не защищены даже крупные корпорации.
Которые не являются сферическими конями в вакууме и испытывают те же проблемы что и более мелкие компании, например текучесть кадров. 
Второй варварский принцип, который здесь успешно применяется можно сформулировать как "Мы используем технологии фашистов против самих фашистов".

Следующие фронтиры этой работы мне видятся в двух эпостасиях.

Первое - это работа с сайтом quora из скрипта. Кеширование списка вопросов. Программа будет называться "Непризнанный гений".
Суть в том что он интересуется всем подряд и яростно пытается найти ответы на бесконечное количество вопросов в ютьюбе, википедии и других популярных сайтах.
Когда фашисты создадут оракла это будет очень кстати.

Второе - это избавление от костыля crc32. Выбор входного списка из внешнего скрипта, тогда мы заказываем музыку. 
Но в случае работы с quora не всегда есть определенность в ее выводе, ведб пользователи добавляют тысячи вопросов каждую минуту 
и может оказаться что по отдному и тому же запросу вы получите разные результаты в разное время.
Поэтому на первых парах можно оставить идею с crc32.
crc32 Возможно заменится на хеши отдельных строк, чтобы не повторяться с вопросами которые уже были в этой сессии. 

## Пара слов о Auto Mouse Click
Отличный инструмент. В идеале функционал этой софтины хотелось бы перевести в полностью свободный софт. 
Т.е. с открытым кодом. Если народ заинтересуется, я готов сделать полностью бесплатный аналог этой программы на базе Qt. 
В крайнем случае можно было бы сделать ПРЕОБРАЗОВАТЕЛЬ скрипта .mamc в эквивалентный пайтоновский скрипт.
Не хватает остро нехватает условных переходов, хотябы в функции RegExp я бы сделал опреатор goto № 
Экспорт и импорт пива в cvs я бы сделал тоже поаккуратнее.
Копирование строчек скрипта
Но это минимальные импрувменты, а в целом программа простая и гениальная.
Кликер не поддерживает относительные пути с переменными %USERPROFILE% или %APPDATA%


## Донаты 
Если вы заинтересовались данной разработкой и нашли ее полезной, то можете донатить на мой Bitcon кошелек 
Заранее благодарю, 3↑3↑3 поклонов 


![image](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/IMAGES/qrcode.png)

QR-code для отправления Bitcoin

АДРЕС ДЛЯ ПРИЕМА БИТКОИНОВ 

bc1q04rtvw7hyvsy7s9kd5jxnvplykvvgz5flruusj





