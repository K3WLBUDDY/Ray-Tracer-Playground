#include <QtWidgets>
#include "combobox.h"

ComboBox::ComboBox(const int value, QWidget *parent):QComboBox(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
