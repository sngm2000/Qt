#include "EmployeeDialog.h"

EmployeeDialog::EmployeeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    connect(ui.buttonBox,
        &QDialogButtonBox::accepted,
        this,
        &QDialog::accept);

    connect(ui.buttonBox,
        &QDialogButtonBox::rejected,
        this,
        &QDialog::reject);
}

EmployeeDialog::~EmployeeDialog()
{}

QString EmployeeDialog::getId() const
{
    return ui.txtId->text();
}

QString EmployeeDialog::getName() const
{
    return ui.txtName->text();
}

QString EmployeeDialog::getDepartment() const
{
    return ui.txtDepartment->text();
}

QString EmployeeDialog::getSalary() const
{
    return ui.txtSalary->text();
}

void EmployeeDialog::setEmployeeData(const QString& id, const QString& name, const QString& dept, const QString& salary)
{
    ui.txtId->setText(id);
    ui.txtName->setText(name);
    ui.txtDepartment->setText(dept);
    ui.txtSalary->setText(salary);

    ui.txtId->setReadOnly(true);
}
