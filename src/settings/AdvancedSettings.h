#pragma once

#include "file/FileFilter.h"
#include "globals/Globals.h"
#include "image/ThumbnailDimensions.h"

#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>

class AdvancedSettings : public QObject
{
    Q_OBJECT
public:
    explicit AdvancedSettings(QObject* parent = nullptr);
    ~AdvancedSettings() override = default;

    bool debugLog() const;
    QString logFile() const;
    QLocale locale() const;
    QStringList sortTokens() const;
    QHash<QString, QString> genreMappings() const;

    const mediaelch::FileFilter& movieFilters() const;
    const mediaelch::FileFilter& concertFilters() const;
    const mediaelch::FileFilter& tvShowFilters() const;
    const mediaelch::FileFilter& subtitleFilters() const;

    QHash<QString, QString> audioCodecMappings() const;
    QHash<QString, QString> videoCodecMappings() const;
    QHash<QString, QString> certificationMappings() const;
    QHash<QString, QString> studioMappings() const;
    QHash<QString, QString> countryMappings() const;

    bool useFirstStudioOnly() const;
    bool forceCache() const;
    bool portableMode() const;
    int bookletCut() const;
    bool writeThumbUrlsToNfo() const;
    mediaelch::ThumbnailDimensions episodeThumbnailDimensions() const;

private:
    bool m_debugLog = 0;
    QString m_logFile;
    QLocale m_locale;
    QStringList m_sortTokens;
    QHash<QString, QString> m_genreMappings;
    mediaelch::FileFilter m_movieFilters;
    mediaelch::FileFilter m_concertFilters;
    mediaelch::FileFilter m_tvShowFilters;
    mediaelch::FileFilter m_subtitleFilters;
    QHash<QString, QString> m_audioCodecMappings;
    QHash<QString, QString> m_videoCodecMappings;
    QHash<QString, QString> m_certificationMappings;
    QHash<QString, QString> m_studioMappings;
    QHash<QString, QString> m_countryMappings;
    mediaelch::ThumbnailDimensions m_episodeThumbnailDimensions;
    bool m_forceCache = false;
    bool m_portableMode = false;
    int m_bookletCut = 0;
    bool m_writeThumbUrlsToNfo = false;
    bool m_useFirstStudioOnly = false;

    QByteArray getAdvancedSettingsXml() const;
    void loadSettings();
    void reset();
    void setLocale(QString locale);
    void loadLog(QXmlStreamReader& xml);
    void loadGui(QXmlStreamReader& xml);
    void loadSortTokens(QXmlStreamReader& xml);
    void loadFilters(QXmlStreamReader& xml);
    void loadMappings(QXmlStreamReader& xml, QHash<QString, QString>& map);
};
