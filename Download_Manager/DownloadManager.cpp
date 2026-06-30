#include "DownloadManager.h"

DownloadManager::DownloadManager(QObject* parent)
    : QObject(parent)
{
}

DownloadManager::~DownloadManager()
{
    for (DownloadTask* task : m_downloadTasks)
    {
        delete task;
    }

    m_downloadTasks.clear();
}

DownloadTask* DownloadManager::addDownload(const QUrl& url,const QString& savePath)
{
    DownloadTask* task = new DownloadTask(
        &m_networkManager,
        url,
        savePath,
        this);

    m_downloadTasks.push_back(task);

    return task;
}

