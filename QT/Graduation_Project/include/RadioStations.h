// ? ================= THIS CLASS IS RESPONSIBLE FOR LOADING RADIO STATIONS FROM AN EXTERNAL CONFIG FILE =================

// ! The station list is NOT hardcoded in source - it lives in an editable
// ! JSON file outside the compiled binary, so stations can be added/removed
// ! without rebuilding the app.

#ifndef RADIOSTATIONS_H
#define RADIOSTATIONS_H

#include <QObject>
#include <QString>
#include <QVariantList>

class RadioStations : public QObject
{
    Q_OBJECT

public:
    explicit RadioStations(QObject *parent = nullptr);

    // ? Re-reads the config file from disk, e.g. after it was edited externally
    Q_INVOKABLE void reload();

    // ? Returns the loaded stations as a list of {name, url} maps
    QVariantList stations() const;

    // ? Full path to the config file, useful for showing the user where to edit it
    QString configFilePath() const;

private:
    // ? Writes out a default station list if no config file exists yet
    void ensureConfigFileExists() const;

    QString m_configFilePath;
    QVariantList m_stations;
};

#endif // RADIOSTATIONS_H
