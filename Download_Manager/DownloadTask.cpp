#include "DownloadTask.h"

#include <QNetworkRequest>
#include <QFileInfo>

DownloadTask::DownloadTask(QNetworkAccessManager* networkManager, const QUrl& url, const QString& savePath, QObject* parent)
	: QObject(parent),
    m_networkManager(networkManager),
    m_url(url),
    m_savePath(savePath),
    m_file(savePath)
{
}

DownloadTask::~DownloadTask()
{
    if (m_reply)
    {
        m_reply->deleteLater();
    }

    if (m_file.isOpen())
    {
        m_file.close();
    }
}

QString DownloadTask::fileName() const
{
    return QFileInfo(m_savePath).fileName();
}

QString DownloadTask::savePath() const
{
    return m_savePath;
}

QUrl DownloadTask::url() const
{
    return m_url;
}

qint64 DownloadTask::bytesReceived() const
{
    return m_bytesReceived;
}

qint64 DownloadTask::bytesTotal() const
{
    return m_bytesTotal;
}

void DownloadTask::start()
{
    if (!m_file.open(QIODevice::WriteOnly))
    {
        emit errorOccurred("Unable to open file.");
        return;
    }

    QNetworkRequest request(m_url);

    m_reply = m_networkManager->get(request);

    connect(m_reply,
        &QNetworkReply::readyRead,
        this,
        &DownloadTask::onReadyRead);

    connect(m_reply,
        &QNetworkReply::downloadProgress,
        this,
        &DownloadTask::onDownloadProgress);

    connect(m_reply,
        &QNetworkReply::finished,
        this,
        &DownloadTask::onFinished);

    connect(m_reply,
        &QNetworkReply::errorOccurred,
        this,
        &DownloadTask::onErrorOccurred);
}

void DownloadTask::cancel()
{
    if (m_reply)
    {
        m_reply->abort();
    }
}

void DownloadTask::onReadyRead()
{
    if (m_reply)
    {
        m_file.write(m_reply->readAll());
    }
}

void DownloadTask::onDownloadProgress(qint64 received,qint64 total)
{
    m_bytesReceived = received;
    m_bytesTotal = total;

    emit progressChanged(received, total);
}

void DownloadTask::onFinished()
{
    if (m_reply)
    {
        m_file.write(m_reply->readAll());

        m_file.close();

        m_reply->deleteLater();
        m_reply = nullptr;
    }

    emit finished();
}

void DownloadTask::onErrorOccurred(QNetworkReply::NetworkError)
{
    if (m_reply)
    {
        emit errorOccurred(m_reply->errorString());
    }
}