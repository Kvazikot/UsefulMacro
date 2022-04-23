#ifndef DIALOGTYPE_H
#define DIALOGTYPE_H

#include <QObject>
#include <QMap>

enum DialogType
{
    AREA_SELECTOR=0,
    SCREEN_BUTTONS_DETECTOR=1,
    COORDINATES_SELECTOR=2,
    SHELL_COMMAND_DIALOG=3,
    TYPE_DIALOG=4,
    DELAY_WIDGET=5
};

static QMap<QString, DialogType> action_map{{"Add left click", COORDINATES_SELECTOR},
                                     {"Add right click", COORDINATES_SELECTOR},
                                     {"Add scroll down", COORDINATES_SELECTOR},
                                     {"Add Shell", SHELL_COMMAND_DIALOG},
                                     {"Set delay for this", DELAY_WIDGET},
                                    };

void createDialog(QObject* receiver_object, DialogType dialog_type);

#endif // DIALOGTYPE_H
