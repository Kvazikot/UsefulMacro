#ifndef DIALOGTYPE_H
#define DIALOGTYPE_H

#include <QObject>

enum DialogType
{
    AREA_SELECTOR=0,
    SCREEN_BUTTONS_DETECTOR=1,
    COORDINATES_SELECTOR=2,
    SHELL_COMMAND_DIALOG=3
};

void createDialog(QObject* receiver_object, DialogType dialog_type);

#endif // DIALOGTYPE_H
