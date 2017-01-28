#ifndef COMBOBOX_H
#define COMBOBOX_H

#include<QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT

public:

    explicit ComboBox(const int &currentIndex);
};

#endif // COMBOBOX_H
