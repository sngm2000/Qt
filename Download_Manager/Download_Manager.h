#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_Download_Manager.h"
#include "DownloadManager.h"

class Download_Manager : public QMainWindow
{
    Q_OBJECT

public:
    Download_Manager(QWidget *parent = nullptr);
    ~Download_Manager();

private:
    Ui::Download_ManagerClass ui;

    DownloadManager* m_downloadManager;

private slots:
    void on_btnDownload_clicked();
};

