#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Employee_Managemen_System.h"

class Employee_Managemen_System : public QMainWindow
{
    Q_OBJECT

public:
    Employee_Managemen_System(QWidget *parent = nullptr);
    ~Employee_Managemen_System();

private:
    Ui::Employee_Managemen_SystemClass ui;

private slots:
    void addEmployee();
    void deleteEmployee();
    void editEmployee();
    void saveEmployee();
};

