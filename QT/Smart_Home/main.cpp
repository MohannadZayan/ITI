#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QTranslator>

class TranslationController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentLanguage READ currentLanguage WRITE setLanguage NOTIFY languageChanged)

public:
    explicit TranslationController(QObject *parent = nullptr)
        : QObject(parent)
    {
        QSettings settings(QSettings::UserScope, "SmartHome", "SmartHome");
        QString storedLanguage = settings.value("language", "en").toString();
        if (storedLanguage != "en" && storedLanguage != "ar" && storedLanguage != "fr") {
            storedLanguage = "en";
        }
        setLanguage(storedLanguage, false);
    }

    QString currentLanguage() const
    {
        return m_currentLanguage;
    }

    Q_INVOKABLE void setLanguage(const QString &language, bool persist = true)
    {
        QString normalizedLanguage = language.toLower();
        if (normalizedLanguage != "en" && normalizedLanguage != "ar" && normalizedLanguage != "fr") {
            normalizedLanguage = "en";
        }

        if (m_currentLanguage == normalizedLanguage && m_translator != nullptr) {
            return;
        }

        if (m_translator != nullptr) {
            QCoreApplication::removeTranslator(m_translator);
            m_translator->deleteLater();
            m_translator = nullptr;
        }

        m_translator = new QTranslator(this);
        const QString translationPath = resolveTranslationPath(normalizedLanguage);
        qDebug() << "Attempting to load translation" << normalizedLanguage << translationPath;
        if (!translationPath.isEmpty() && m_translator->load(translationPath)) {
            qDebug() << "Translation loaded" << translationPath;
            QCoreApplication::installTranslator(m_translator);
        } else {
            qDebug() << "Failed to load translation" << translationPath;
            m_translator->deleteLater();
            m_translator = nullptr;
        }

        QLocale::setDefault(QLocale(normalizedLanguage == "ar" ? QStringLiteral("ar")
                                                           : normalizedLanguage == "fr" ? QStringLiteral("fr")
                                                                                          : QStringLiteral("en")));
        m_currentLanguage = normalizedLanguage;

        if (persist) {
            QSettings settings(QSettings::UserScope, "SmartHome", "SmartHome");
            settings.setValue("language", normalizedLanguage);
        }

        emit languageChanged();
    }

signals:
    void languageChanged();

private:
    QString resolveTranslationPath(const QString &language) const
    {
        const QStringList candidates = {
            QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("translations/smart_home_%1.qm").arg(language)),
            QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("../translations/smart_home_%1.qm").arg(language)),
            QDir::currentPath() + "/translations/smart_home_" + language + ".qm",
            QStringLiteral(":/qt/qml/Smart_Home/translations/smart_home_%1.qm").arg(language),
            QStringLiteral(":/translations/smart_home_%1.qm").arg(language),
        };

        for (const QString &candidate : candidates) {
            if (candidate.startsWith(QLatin1String(":/"))) {
                // Allow loading Qt resource paths directly.
                return candidate;
            }
            if (QFileInfo::exists(candidate)) {
                return candidate;
            }
        }

        return {};
    }

    QString m_currentLanguage = QStringLiteral("en");
    QTranslator *m_translator = nullptr;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TranslationController controller;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("translationController"), &controller);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QObject::connect(&controller, &TranslationController::languageChanged, &engine, [&engine]() {
        engine.retranslate();
    });

    engine.loadFromModule("Smart_Home", "Main");

    return QGuiApplication::exec();
}

#include "main.moc"
