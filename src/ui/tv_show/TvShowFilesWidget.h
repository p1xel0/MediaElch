#pragma once

#include "data/TvShow.h"
#include "data/TvShowEpisode.h"
#include "data/TvShowProxyModel.h"
#include "globals/Filter.h"
#include "globals/Globals.h"

#include <QAction>
#include <QMenu>
#include <QModelIndex>
#include <QWidget>

namespace Ui {
class TvShowFilesWidget;
}

/// @brief UI widget for showing TV shows in a table/list view.
class TvShowFilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TvShowFilesWidget(QWidget* parent = nullptr);
    ~TvShowFilesWidget() override;

    void setFilter(const QVector<Filter*>& filters, QString text);
    static TvShowFilesWidget& instance();
    QVector<TvShowEpisode*> selectedEpisodes(bool includeFromSeasonOrShow = true);
    QVector<TvShow*> selectedShows();
    QVector<TvShow*> selectedSeasons();

public slots:
    void renewModel(bool force = false);
    void emitLastSelection();
    void multiScrape();
    void updateProxy();

signals:
    void sigEpisodeSelected(TvShowEpisode* episode);
    void sigTvShowSelected(TvShow* show);
    void sigSeasonSelected(TvShow* show, SeasonNumber season);
    void sigNothingSelected();
    void sigStartSearch();

private slots:
    void onItemSelected(QModelIndex index);
    void showContextMenu(QPoint point);
    void scanForEpisodes();
    void markAsWatched();
    void markAsUnwatched();
    void loadStreamDetails();
    void markForSync(bool markForSync = true);
    void unmarkForSync();
    void openFolder();
    void openNfo();
    void showMissingEpisodes();
    void hideSpecialsInMissingEpisodes();
    void onViewUpdated();
    void playEpisode(QModelIndex idx);

private:
    void setupContextMenu();
    void emitSelected(QModelIndex proxyIndex);
    void forEachSelectedItem(std::function<void(TvShowModelItem&)> callback);

    static TvShowFilesWidget* m_instance;

    Ui::TvShowFilesWidget* ui = nullptr;
    TvShowProxyModel* m_tvShowProxyModel = nullptr;
    QMenu* m_contextMenu = nullptr;

    // last selected show/episode/season
    TvShow* m_lastTvShow = nullptr;
    TvShowEpisode* m_lastEpisode = nullptr;
    SeasonNumber m_lastSeason = SeasonNumber::NoSeason;

    QAction* m_actionShowMissingEpisodes = nullptr;
    QAction* m_actionHideSpecialsInMissingEpisodes = nullptr;
};