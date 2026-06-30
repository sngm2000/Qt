#pragma once

#include <QObject>
#include <vector>

#include "DownloadTask.h"


class DownloadManager : public QObject
{
    Q_OBJECT

public:
    explicit DownloadManager(QObject* parent = nullptr);
    ~DownloadManager();

    DownloadTask* addDownload(const QUrl& url,
        const QString& savePath);

private:
    QNetworkAccessManager m_networkManager;
    std::vector<DownloadTask*> m_downloadTasks;
};

