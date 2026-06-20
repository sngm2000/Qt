#pragma once

#include <QDialog>
#include "ui_EmployeeDialog.h"

class EmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	EmployeeDialog(QWidget *parent = nullptr);
	~EmployeeDialog();


public:

	QString getId() const;
	QString getName() const;
	QString getDepartment() const;
	QString getSalary() const;
	void setEmployeeData(const QString& id,const QString& name,const QString& dept,const QString& salary);

private:
	Ui::EmployeeDialogClass ui;
};



