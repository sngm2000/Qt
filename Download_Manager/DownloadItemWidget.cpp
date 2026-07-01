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

    connect(ui.btnCancel,
        &QPushButton::clicked,
        this,
        &DownloadItemWidget::on_btnCancel_clicked);
}

DownloadItemWidget::~DownloadItemWidget()
{}

void DownloadItemWidget::setFileName(const QString & fileName)
{
    ui.lblFileName->setText(fileName);
}

QString DownloadItemWidget::formatBytes(qint64 bytes)
{
    const double KB = 1024.0;
    const double MB = KB * 1024.0;
    const double GB = MB * 1024.0;
    const double TB = GB * 1024.0;

    if (bytes >= TB)
        return QString("%1 TB").arg(bytes / TB, 0, 'f', 2);

    if (bytes >= GB)
        return QString("%1 GB").arg(bytes / GB, 0, 'f', 2);

    if (bytes >= MB)
        return QString("%1 MB").arg(bytes / MB, 0, 'f', 2);

    if (bytes >= KB)
        return QString("%1 KB").arg(bytes / KB, 0, 'f', 2);

    return QString("%1 Bytes").arg(bytes);
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
        .arg(formatBytes(received))
        .arg(formatBytes(total)));

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

void DownloadItemWidget::on_btnCancel_clicked()
{
    emit cancelRequested();
}

void DownloadItemWidget::downloadCancelled()
{
    ui.lblStatus->setText("Cancelled");
}

void DownloadItemWidget::updateSpeed(double bytesPerSecond)
{
    ui.lblSpeed->setText(
        formatBytes(
            static_cast<qint64>(bytesPerSecond))
        + "/s");
}
