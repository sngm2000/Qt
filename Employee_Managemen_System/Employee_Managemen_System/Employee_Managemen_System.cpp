#include "Employee_Managemen_System.h"
#include "EmployeeDialog.h"


#include <QHeaderView>
#include <qmessagebox.h>

Employee_Managemen_System::Employee_Managemen_System(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btnAdd, &QPushButton::clicked, this, &Employee_Managemen_System::addEmployee);
    connect(ui.btnDelete, &QPushButton::clicked, this, &Employee_Managemen_System::deleteEmployee);
    connect(ui.btnEdit, &QPushButton::clicked, this, &Employee_Managemen_System::editEmployee);
    connect(ui.btnSave, &QPushButton::clicked, this, &Employee_Managemen_System::saveEmployee);

    ui.tblEmployee->setColumnCount(4);
    QStringList headers;
    headers << "ID"
        << "Name"
        << "Department"
        << "Salary";
    ui.tblEmployee->setHorizontalHeaderLabels(headers);
    ui.tblEmployee->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);
}

Employee_Managemen_System::~Employee_Managemen_System()
{}


void Employee_Managemen_System:: addEmployee()
{
    EmployeeDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        int row =
            ui.tblEmployee->rowCount();

        ui.tblEmployee->insertRow(row);

        ui.tblEmployee->setItem(
            row,
            0,
            new QTableWidgetItem(
                dlg.getId()));

        ui.tblEmployee->setItem(
            row,
            1,
            new QTableWidgetItem(
                dlg.getName()));

        ui.tblEmployee->setItem(
            row,
            2,
            new QTableWidgetItem(
                dlg.getDepartment()));

        ui.tblEmployee->setItem(
            row,
            3,
            new QTableWidgetItem(
                dlg.getSalary()));
    }
}

void Employee_Managemen_System::deleteEmployee()
{
    int row =
        ui.tblEmployee->currentRow();

    if (row >= 0)
    {
        ui.tblEmployee->removeRow(row);
    }
}

void Employee_Managemen_System::editEmployee()
{
    int row = ui.tblEmployee->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(
            this,
            "Edit Employee",
            "Please select an employee.");

        return;
    }

    EmployeeDialog dlg(this);

    dlg.setEmployeeData(
        ui.tblEmployee->item(row, 0)->text(),
        ui.tblEmployee->item(row, 1)->text(),
        ui.tblEmployee->item(row, 2)->text(),
        ui.tblEmployee->item(row, 3)->text());

    if (dlg.exec() == QDialog::Accepted)
    {
        ui.tblEmployee->item(row, 0)
            ->setText(dlg.getId());

        ui.tblEmployee->item(row, 1)
            ->setText(dlg.getName());

        ui.tblEmployee->item(row, 2)
            ->setText(dlg.getDepartment());

        ui.tblEmployee->item(row, 3)
            ->setText(dlg.getSalary());
    }
}

void Employee_Managemen_System::saveEmployee()
{

}
