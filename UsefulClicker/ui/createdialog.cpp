#include "ui/areaselectordialog.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/coordselector.h"
#include "ui/shelldialog.h"
#include "ui/dialogtype.h"

void createDialog(QObject* receiver_object, DialogType dialog_type)
{
    switch( dialog_type )
    {
         case AREA_SELECTOR:
         {
             AreaSelectorDialog* dlg = new AreaSelectorDialog((QWidget*)receiver_object);
             receiver_object->connect(dlg, SIGNAL(sigSetAreaRect(QMap<QString,QString>)), receiver_object, SLOT(slotSetAttrs(QMap<QString,QString>)));
             dlg->show();
         } break;
         case SCREEN_BUTTONS_DETECTOR:
         {
            ScreenButtonsDetector* dlg2 = new ScreenButtonsDetector((QWidget*)receiver_object);
            receiver_object->connect(dlg2, SIGNAL(sigSetAttrs(QMap<QString,QString>)), receiver_object, SLOT(slotSetAttrs(QMap<QString,QString>)));
            dlg2->show();
         } break;
         case COORDINATES_SELECTOR:
         {
             CoordSelector* dlg2 = new CoordSelector((QWidget*)receiver_object);
             receiver_object->connect(dlg2, SIGNAL(sigSetAttrs(QMap<QString,QString>)), receiver_object, SLOT(slotSetAttrs(QMap<QString,QString>)));
             dlg2->show();
         } break;
         case SHELL_COMMAND_DIALOG:
         {
             ShellDialog* dlg3 = new ShellDialog((QWidget*)receiver_object);
             receiver_object->connect(dlg3, SIGNAL(sigSetAttrs(QMap<QString,QString>)), receiver_object, SLOT(editCurrentItem(QMap<QString,QString>)));
             dlg3->show();

         } break;
    }
}