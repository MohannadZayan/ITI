#include "RadioStations.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

RadioStations::RadioStations(QObject *parent)
    : QObject{parent}
{
    const QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    m_configFilePath = configDir + "/radio_stations.json";

    ensureConfigFileExists();
    reload();
}

// * ================= ENSURE CONFIG FILE EXISTS =================
// ? Seeds a default station list on first run, so the app works out of the
// ? box while still giving the user a real file to edit afterwards

void RadioStations::ensureConfigFileExists() const
{
    QFile file(m_configFilePath);

    if (file.exists())
        return;

    QDir().mkpath(QFileInfo(m_configFilePath).absolutePath());

    QJsonArray defaultStations{
        QJsonObject{
            {"name", "Quran Radio — Makkah (Saudi Arabia)"},
            {"url", "http://stream.radiojar.com/0tpy1h0kxtzuv"}
        },
        QJsonObject{
            {"name", "Quran Radio — Cairo (Egypt)"},
            {"url", "https://stream.radiojar.com/8s5u5tpdtwzuv"}
        },
        QJsonObject{
            {"name", "Quran Radio — Sharjah (UAE)"},
            {"url", "https://l3.itworkscdn.net/smcquranlive/quranradiolive/icecast.audio"}
        }
    };

    if (file.open(QIODevice::WriteOnly))
        file.write(QJsonDocument(defaultStations).toJson());
}

// * ================= RELOAD =================
// ? Reads the config file from disk and rebuilds the in-memory station list

void RadioStations::reload()
{
    m_stations.clear();

    QFile file(m_configFilePath);

    if (!file.open(QIODevice::ReadOnly))
        return;

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    if (!document.isArray())
        return;

    for (const QJsonValue &value : document.array()) {
        const QJsonObject station = value.toObject();
        m_stations.append(QVariantMap{
            {"name", station.value("name").toString()},
            {"url", station.value("url").toString()}
        });
    }
}

QVariantList RadioStations::stations() const
{
    return m_stations;
}

QString RadioStations::configFilePath() const
{
    return m_configFilePath;
}
