
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
