# UsefulMacro
Цель этого репозитория: Исследовательская. Исследовать алгоритмы ютьюба.

## Первый сценарий для youtube (макрос)

Макрос работает на разрешении экрана Full HD т.е. 1980x1080

Смотрите видео урок
https://youtu.be/CgkG_xl4GiE

Для закачки мароса кликните [здесь](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube5_SPLITSCREEN.macrorecording)

1. Для запуска макроса вам потребуется программа. AutoMouseClick by MurGee.com
https://www.murgee.com/auto-mouse-click/
2. Запустите Auto Mouse Click by MurGee.com
3. Нажимаете кнопку Start.  
4. Выбираете из выпадающего меню Macrorecorder
5. В окне Macrorecorder выбираете файл макроса youtube5_SPLITSCREEN.macrorecording
6. Разделяете экран как на скриншоте.
Для этого я разделяю экран на две части, по горизонтали пополам.
Открываю блокнот с ключевыми словами [keywords_youtube.txt](https://github.com/Kvazikot/UsefulMacro/blob/master/keywords_youtube.txt) в левой части экрана (комбинация клавиш WIN + CAPS LOCK + LEFT)
Открываю браузер хром в правой части экрана (комбинация клавиш WIN + CAPS LOCK + RIGHT)
7. Комбинация ctr + alt + f6 - запуск макроса
8. Комбинация ctr + alt + f7 - пауза \ пуск
![Screenshot](https://github.com/Kvazikot/UsefulMacro/blob/master/AUTOCLIKER_SCREENSHOT2.png)


### Известные проблемы этого макроса:
Иногда изза девиации мышки, робот попадает не туда. Промах по цели так сказать.
Вместо поиска (увеличительное стекло) он иногда нажимает голосовой поиск(микрофон).
Чтобы преодолеть эту проблему - запустите мой супер пупер скрипт [alwaysontop.py](https://github.com/Kvazikot/UsefulMacro/blob/master/alwaystop.py)
Скрипт alwaysontop.py создает окно Notepad.exe которое будет всегда поверх других окон. 
Закройте этим окном кнопку микрофона на главной странице ютьюба. Этот фикс работает на 10-ке.

Сейчас все силы нашей команды брошены на разработку нового скрипта, который будет лишен недостатков этой версии.
Он будет использовать тот же принцип сменяемых списков слева. Но с помощью базового функционала Auto Mouse Click.
Клики будут происходить мгновенно, т.е. без движения курсора мыши. Без использования Macros Recorder.
Работаем в три смены. 

## Второй сценарий для youtube
[сценарий 2](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube_search_by_list.mamc)
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
Уберите панель закладок Chrome или firefox, если вы ее используете.
1. Подготовте окна браузера и блокнота как для 1-ого макроса 
2. В проводнике windows (ctrl + E) забейте в адресную строку %USERPROFILE%
3. Положите скрипт перемешивающий строки [shuffle_clipboard.vbs](https://github.com/Kvazikot/UsefulMacro/raw/master/shuffle_clipboard.vbs) в каталог %USERPROFILE%
4. Проверьте что расширение у файла shuffle_clipboard.vbs именно .vbs, а не txt, иначе он не запустится.
5. Откройте ключевые слова в блокноте (Notepad.exe или Notepad++)
6. Запустите [youtube_search_by_list_shuffle.mamc](https://github.com/Kvazikot/UsefulMacro/raw/master/youtube_search_by_list_shuffle.mamc) кнопкой Start

Примечание: Если вы как и я используете Notepad++. ТО удостоверьтесь что в настройках выставлено тихое(quiet) обновление файла

## Четвертый сценарий для youtube. Работа сразу с несколькими окнами параллельно
![image](https://github.com/Kvazikot/UsefulMacro/blob/master/4_window_mode.png)
В данный момент наша доблесная команда трудится не покладая рук над новой версией
сценария который будет работать с несколькими окнами ютьюба.
В планах также адаптация под другие разрешения экрана отличные от Full HD 1980x1080

## Списки 
в каталоге youtube этого репозитория содержаться списки для поиска:

* [список "сленг поколения z"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/z_gen_slang.txt)
* [список "фанат Unity"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/unity_fan_list.txt)
* [список "общеупотребимые английские слова"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/keywords_youtube.txt)
* [список "водопроводчик"](https://github.com/Kvazikot/UsefulMacro/blob/master/youtube/plumber_keywords.txt)
* 


## Пара слов о Auto Mouse Click
Отличный инструмент. В идеале функционал этой софтины хотелось бы перевести в полностью свободный софт. 
Т.е. с открытым кодом, записывайтесь в волонтеры free software foundation и дерзайте.
В крайнем случае можно было бы сделать ПРЕОБРАЗОВАТЕЛЬ скрипта .mamc в эквивалентный пайтоновский скрипт.


