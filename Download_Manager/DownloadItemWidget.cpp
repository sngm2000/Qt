#include "DownloadItemWidget.h"

DownloadItemWidget::DownloadItemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    ui.progressBar->setValue(0);

    ui.lblPercent->setText("0 %");

    ui.lblDownloaded->setText("0 B / 0 B");

    ui.lblSpeed->setText("0 KB/s");

    ui.lblStatus->setText("Waiting");
}

DownloadItemWidget::~DownloadItemWidget()
{}

void DownloadItemWidget::setFileName(const QString & fileName)
{
    ui.lblFileName->setText(fileName);
}


void DownloadItemWidget::updateProgress(qint64 received, qint64 total)
{
    if (total <= 0)
        return;

    int percent =
        static_cast<int>((received * 100) / total);

    ui.progressBar->setValue(percent);

    ui.lblPercent->setText(
        QString("%1 %").arg(percent));

    ui.lblDownloaded->setText(
        QString("%1 / %2")
        .arg(received)
        .arg(total));

    ui.lblStatus->setText("Downloading");
}

void DownloadItemWidget::downloadFinished()
{
    ui.progressBar->setValue(100);

    ui.lblPercent->setText("100 %");

    ui.lblStatus->setText("Completed");
}

void DownloadItemWidget::downloadFailed(const QString& error)
{
    ui.lblStatus->setText(error);
}
