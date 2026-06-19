#include "EmployeeForm.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>

EmployeeForm::EmployeeForm(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_3, &QPushButton::clicked, this, &QWidget::close);
    connect(ui.pushButton, &QPushButton::clicked, this, &EmployeeForm::saveData);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &EmployeeForm::clearForm);

    ui.tableWidget->setColumnCount(4);
    QStringList headers;

    headers << "ID"<< "Name"<< "Department"<< "Salary";
    ui.tableWidget->setHorizontalHeaderLabels(headers);
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



}

EmployeeForm::~EmployeeForm()
{

}

void EmployeeForm::addEmployee(QString id, QString name, QString dept, QString salary)
{
    int row = 
        ui.tableWidget->rowCount();

    ui.tableWidget->insertRow(row);

    ui.tableWidget->setItem(
        row, 0,
        new QTableWidgetItem(id));

    ui.tableWidget->setItem(
        row, 1,
        new QTableWidgetItem(name));

    ui.tableWidget->setItem(
        row, 2,
        new QTableWidgetItem(dept));

    ui.tableWidget->setItem(
        row, 3,
        new QTableWidgetItem(salary));
}

void EmployeeForm::clearForm()
{
    ui.lineEdit->clear();
    ui.lineEdit_2->clear();
    ui.lineEdit_3->clear();
    ui.lineEdit_4->clear();
}

void EmployeeForm::saveData()
{
    QString id = ui.lineEdit->text();
    QString name = ui.lineEdit_2->text();
    QString dept = ui.lineEdit_3->text();
    QString salary = ui.lineEdit_4->text();

    //QMessageBox::information(
    //    this,
    //    "Employee",
    //    QString("ID: %1\nName: %2")
    //    .arg(id)
    //    .arg(name));

    addEmployee(id, name, dept, salary);
}
