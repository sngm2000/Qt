#include "Employee_Managemen_System.h"
#include "EmployeeDialog.h"


#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

Employee_Managemen_System::Employee_Managemen_System(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btnAdd, &QPushButton::clicked, this, &Employee_Managemen_System::addEmployee);
    connect(ui.btnDelete, &QPushButton::clicked, this, &Employee_Managemen_System::deleteEmployee);
    connect(ui.btnEdit, &QPushButton::clicked, this, &Employee_Managemen_System::editEmployee);
    connect(ui.btnSave, &QPushButton::clicked, this, &Employee_Managemen_System::saveEmployee);
    connect(ui.lineEditSearch, &QLineEdit::textChanged, this, &Employee_Managemen_System::searchEmployee);
    connect(ui.tblEmployee,&QTableWidget::cellDoubleClicked,this,&Employee_Managemen_System::editEmployee);
    connect(ui.tblEmployee,&QTableWidget::customContextMenuRequested,this,&Employee_Managemen_System::showContextMenu);

    ui.tblEmployee->setColumnCount(4);
    QStringList headers;
    headers << "ID"
        << "Name"
        << "Department"
        << "Salary";
    ui.tblEmployee->setHorizontalHeaderLabels(headers);
    ui.tblEmployee->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);
    ui.tblEmployee->setContextMenuPolicy(Qt::CustomContextMenu);
    ui.tblEmployee->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadEmployees();
}

Employee_Managemen_System::~Employee_Managemen_System()
{}

void Employee_Managemen_System::loadEmployees()
{
    QString fileName =
        QCoreApplication::applicationDirPath()
        + "/employees.csv";

    QFile file(fileName);

    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    ui.tblEmployee->setRowCount(0);

    // Skip Header
    in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine();

        QStringList data = line.split(",");

        if (data.size() < 4)
            continue;

        int row = ui.tblEmployee->rowCount();

        ui.tblEmployee->insertRow(row);

        ui.tblEmployee->setItem(row, 0, new QTableWidgetItem(data[0]));
        ui.tblEmployee->setItem(row, 1, new QTableWidgetItem(data[1]));
        ui.tblEmployee->setItem(row, 2, new QTableWidgetItem(data[2]));
        ui.tblEmployee->setItem(row, 3, new QTableWidgetItem(data[3]));
    }

    file.close();
}


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
    QString fileName =
        QCoreApplication::applicationDirPath()
        + "/employees.csv";

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "Error",
            "Unable to save file.");

        return;
    }

    QTextStream out(&file);

    // Header
    out << "ID,Name,Department,Salary\n";

    for (int row = 0; row < ui.tblEmployee->rowCount(); row++)
    {
        for (int col = 0; col < ui.tblEmployee->columnCount(); col++)
        {
            QTableWidgetItem* item =
                ui.tblEmployee->item(row, col);

            if (item)
                out << item->text();

            if (col != ui.tblEmployee->columnCount() - 1)
                out << ",";
        }

        out << "\n";
    }

    file.close();

    QMessageBox::information(
        this,
        "Success",
        "Employee data saved.");
}

void Employee_Managemen_System::searchEmployee()
{
    QString searchText =
        ui.lineEditSearch->text().trimmed();

    for (int row = 0; row < ui.tblEmployee->rowCount(); row++)
    {
        bool found = false;

        for (int col = 0; col < ui.tblEmployee->columnCount(); col++)
        {
            QTableWidgetItem* item =
                ui.tblEmployee->item(row, col);

            if (item &&
                item->text().contains(searchText, Qt::CaseInsensitive))
            {
                found = true;
                break;
            }
        }

        ui.tblEmployee->setRowHidden(row, !found);
    }
}

void Employee_Managemen_System::showContextMenu(const QPoint& pos)
{
    QMenu menu(this);

    QAction* editAction =
        menu.addAction("Edit");

    QAction* deleteAction =
        menu.addAction("Delete");

    QAction* selectedAction =
        menu.exec(ui.tblEmployee->viewport()->mapToGlobal(pos));

    if (selectedAction == editAction)
    {
        editEmployee();
    }
    else if (selectedAction == deleteAction)
    {
        deleteEmployee();
    }
}
