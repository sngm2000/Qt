#include "Download_Manager.h"
#include "DownloadItemWidget.h"


#include <QFileDialog>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QDir>
#include <QMessageBox>

Download_Manager::Download_Manager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    m_downloadManager = new DownloadManager(this);

    connect(ui.pushButton_Download, &QPushButton::clicked, this, &Download_Manager::on_btnDownload_clicked);
}

Download_Manager::~Download_Manager()
{}

void Download_Manager::on_btnDownload_clicked()
{
    // Read URL
    QString urlString = ui.lineEdit_URL->text().trimmed();

    if (urlString.isEmpty())
    {
        QMessageBox::warning(this,
            "Download Manager",
            "Please enter a download URL.");
        return;
    }

    QUrl url(urlString);

    if (!url.isValid())
    {
        QMessageBox::warning(this,
            "Download Manager",
            "Invalid URL.");
        return;
    }

    QString fileName = QFileInfo(url.path()).fileName();

    if (fileName.isEmpty())
    {
        fileName = "download";
    }

    // Ask user where to save
    QString defaultPath = QDir::homePath() + "/" + fileName;

    QString savePath =
        QFileDialog::getSaveFileName(
            this,
            "Save File",
            defaultPath,
            "All Files (*.*)");

    if (savePath.isEmpty())
    {
        return;
    }

    // Create DownloadTask
    DownloadTask* task = m_downloadManager->addDownload(url, savePath);

    // Create Download Widget
    DownloadItemWidget* widget =
        new DownloadItemWidget(this);

    widget->setFileName(fileName);

    // Add widget to QListWidget
    QListWidgetItem* item =
        new QListWidgetItem(ui.listWidget);

    item->setSizeHint(widget->sizeHint());

    ui.listWidget->addItem(item);

    ui.listWidget->setItemWidget(item, widget);

    // Connect task with widget
    connect(task,
        &DownloadTask::progressChanged,
        widget,
        &DownloadItemWidget::updateProgress);

    connect(task,
        &DownloadTask::finished,
        widget,
        &DownloadItemWidget::downloadFinished);

    connect(task,
        &DownloadTask::errorOccurred,
        widget,
        &DownloadItemWidget::downloadFailed);

    // Start Download
    task->start();
}