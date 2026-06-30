#pragma once

#include <QObject>
#include <QUrl>
#include <QString>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class DownloadTask : public QObject
{
    Q_OBJECT

public:
    explicit DownloadTask(QNetworkAccessManager* networkManager,
        const QUrl& url,
        const QString& savePath,
        QObject* parent = nullptr);

    ~DownloadTask();

    // Operations
    void start();
    void cancel();

    // Getters
    QString fileName() const;
    QString savePath() const;
    QUrl url() const;

    qint64 bytesReceived() const;
    qint64 bytesTotal() const;

signals:
    void progressChanged(qint64 bytesReceived, qint64 bytesTotal);
    void finished();
    void errorOccurred(const QString& errorString);

private slots:
    void onReadyRead();
    void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);
    void onFinished();
    void onErrorOccurred(QNetworkReply::NetworkError error);

private:
    // Shared (owned by DownloadManager)
    QNetworkAccessManager* m_networkManager = nullptr;

    // Owned by this DownloadTask
    QNetworkReply* m_reply = nullptr;
    QFile m_file;

    // Download information
    QUrl m_url;
    QString m_savePath;

    // Progress
    qint64 m_bytesReceived = 0;
    qint64 m_bytesTotal = 0;
};

