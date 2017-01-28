#ifndef SRAY_H
#define SRAY_H

#include <QWidget>
#include "combobox.h"
#include "sVector.h"
#include "sphere.h"
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

#define MAX_RAY_DEPTH 5

namespace Ui {
class sRay;
}

class sRay : public QWidget
{
    Q_OBJECT

public:
    explicit sRay(QWidget *parent = 0);
    ~sRay();
    void init();

private:
    std::vector<Sphere> spheres;

    Ui::sRay *ui;

    float mix(const float &a, const float &b, const float &mix);

    Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere> &spheres, const int &depth);

    void render(const std::vector<Sphere> &spheres);

private slots:

    void comboBoxActive();
    void comboBoxChange();

};

#endif // SRAY_H
