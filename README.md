# UsefulMacro
Цель этого репозитория: Исследовательская. 

## Автоматический поиск работы на head hunter
Скрипт отсылает ваше резюме случайным работтодателям на сайте hh.ru
По теории вероятности вы увеличите шансы найти работу если каждый день будете рассылать свое резюме 200 разным работодателям. 
200 это лимит за сутки на сайте hh.ru. Причем не важно даже что они вам предлагают.

![image](https://github.com/Kvazikot/UsefulMacro/blob/master/hh_screenshot.png)

Для hh работает только в разрешении 1920x1080 и на 100% зуме страницы. Поскольку там поиск картинки "Откликнуться" и он не нейросетевой
Для запуска сценария вам потребуется программа AutoMouseClick by MurGee.com 
Ее можно [скачать](https://www.murgee.com/auto-mouse-click/download/setup.exe) здесь https://www.murgee.com/auto-mouse-click/
1. Установите Auto Mouse Click by MurGee.com
2. Откройте в браузере сайт hh.ru
3. Скиньте папку ["Images to Search On Screen"](https://github.com/Kvazikot/UsefulMacro/archive/refs/heads/master.zip) в %APPDATA%, но на один уровень выше
4. В проводнике windows (Win + E) забейте в адресную строку %USERPROFILE%
5. Положите скрипт генерирующий url-адреса [gen_url_hh.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/gen_url_hh.vbs) в каталог %USERPROFILE%
6. Откройте файл [gen_url_hh.vbs](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/gen_url_hh.vbs) блокнотом  
7. Найдите строчку HH_ID = "170669dfff0865af3b0039ed1f6b6d3752674b"
8. Нажмите ctrl + S
9. Если ctrl + S не сработал, зайдите в меню файл - > Сохранить
10. Замените "170669dfff0865af3b0039ed1f6b6d3752674b" на id своего резюме
11. Запустите [скрипт shit_head_hunter_wit_hurl_generation.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/shit_head_hunter_wit_hurl_generation.mamc) кнопкой Start или комбинацией ctrl + alt + F6


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

Этот вариант [youtube_search_by_list_shuffle_v2_signout](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube_search_by_list_shuffle_v2_signout%20.mamc) работает только без sign in т.е. анонимно. Проверено для в Edge и Chrome.

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
* [список "im not a man of two many faces"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/medical_search_list_rus.txt)

Списки вопросов по астрономии и инженерингу я взял с quora.com по ключевому слову: 
"NASA" "System enginering" "Electrical Enginering" "Linux"
Для вычленения вопросов из вывода поисковика quora цезарь чикен макнагетс дарит вам скрипт
[quora_extract_questions.vbs](https://github.com/Kvazikot/UsefulMacro/blob/master/quora_extract_questions.vbs)
Он берет на входе строку из буффера обмена, выделяет вопросы и запускает блокнот с ними

## Как быстро получить список вопросов в области в которой вы полный дилетант.
1. Заходите на [квору](https://www.quora.com/search?q=engine%20repair)
2. Забиваете в поиск интересующий термин
3. ctrl + a, ctrl + c
4. запускаете мой супер пупер огненный скрипт [quora_extract_questions.vbs](https://github.com/Kvazikot/UsefulMacro/blob/master/quora_extract_questions.vbs)
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
Еще в этом репозитории есть:
* Поиск в яндексе [yandex__search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex__search_shuffle_v0.mamc)
* Поиск в яндексе [yandex_news_search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex_news_search_shuffle_v0.mamc)
* [скрипт obi_stroi_hypermarket.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/obi_stroi_hypermarket.mamc) для поиска разных стройматериалов на сайте гипермаркета OBI он работает со [этим](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/obi_list.txt) списком
* vlc_random_pitch - скрипт для vlc который периодически меняет основную частоту звука, чтобы не было понятно у какго какой социальный статус.


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

## Донаты 
Если вы заинтересовались данной разработкой и нашли ее полезной, то можете донатить на мой Bitcon кошелек 
Заранее благодарю, 3↑3↑3 поклонов 


![image](https://github.com/Kvazikot/UsefulMacro/blob/master/donate.png)

QR-code для отправления Bitcoin



