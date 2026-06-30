#pragma once

#include <QWidget>
#include "ui_DownloadItemWidget.h"

class DownloadItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DownloadItemWidget(QWidget* parent = nullptr);
	~DownloadItemWidget();

	void setFileName(const QString& fileName);

private:
	Ui::DownloadItemWidgetClass ui;


public slots:
	void updateProgress(qint64 received,qint64 total);
	void downloadFinished();
	void downloadFailed(const QString& error);
};

