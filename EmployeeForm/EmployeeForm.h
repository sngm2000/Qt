#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EmployeeForm.h"

class EmployeeForm : public QMainWindow
{
    Q_OBJECT

public:
    EmployeeForm(QWidget *parent = nullptr);
    ~EmployeeForm();

private:
    Ui::EmployeeFormClass ui;

    void addEmployee(QString id, QString name, QString dept, QString salary);

private slots:
    void saveData();
    void clearForm();
};

