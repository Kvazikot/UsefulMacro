# UsefulMacro
Цель этого репозитория: Исследовательская. Исследовать алгоритмы ютьюба.


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
Запуск кнопкой Start

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
9. Уберите панель закладок Chrome или firefox, если вы ее используете.

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

## Как быстро получить список воросов в области в которой вы полный дилетант.
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

## Пара слов о Auto Mouse Click
Отличный инструмент. В идеале функционал этой софтины хотелось бы перевести в полностью свободный софт. 
Т.е. с открытым кодом, записывайтесь в волонтеры free software foundation и дерзайте.
В крайнем случае можно было бы сделать ПРЕОБРАЗОВАТЕЛЬ скрипта .mamc в эквивалентный пайтоновский скрипт.
Не хватает остро нехватает условных переходов, хотябы в функции RegExp я бы сделал опреатор goto № 
Экспорт и импорт пива в cvs я бы сделал тоже поаккуратнее.
Копирование строчек скрипта
Но это минимальные импрувменты, а в целом программа простая и гениальная.

## Дополнительные сценарии
Еще в этом репозитории есть:
* Поиск в яндексе [yandex__search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex__search_shuffle_v0.mamc)
* Поиск в яндексе [yandex_news_search_shuffle_v0.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/yandex_news_search_shuffle_v0.mamc)
* [скрипт obi_stroi_hypermarket.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/obi_stroi_hypermarket.mamc)
для поиска разных стройматериалов на сайте гипермаркета OBI он работает со [этим](https://raw.githubusercontent.com/Kvazikot/UsefulMacro/master/youtube/obi_list.txt) списком

Известная проблема с яндексом. Иногда скрипт закрывает все вкладки и всете с ними окно браузера.
Лечится это пока созданием нескольих окон комбинацией ctrl + N

## Выводы по ютьюбу
НА данный омент 11.46 1.31.2022 у меня получился телевизор который сам преключает каналы.
В принципе сюда можно добавить контроль внимания телезрителя. Т.е. если контент совсем не нравится, человек отварачивает голову и программа ставится на паузу т.е. не переключает каналы. Как то так


