#include "test/test_helpers.h"

#include "media_centers/kodi/v18/TvShowXmlWriterV18.h"
#include "tv_shows/TvShow.h"

#include <QDateTime>
#include <QDomDocument>
#include <chrono>

using namespace std::chrono_literals;

TEST_CASE("TV show XML writer for Kodi v18", "[data][tvshow][kodi][nfo]")
{
    SECTION("Empty tvshow")
    {
        TvShow tvShow;
        mediaelch::kodi::TvShowXmlWriterV18 writer(tvShow);

        const QByteArray expectedNfo = R"(<?xml version="1.0" encoding="UTF-8" standalone='yes'?>
<tvshow>
   <title></title>
   <showtitle></showtitle>
   <uniqueid type="unknown" default="true"></uniqueid>
   <ratings></ratings>
   <top250>0</top250>
   <episode>0</episode>
   <plot></plot>
   <outline></outline>
   <mpaa></mpaa>
   <premiered></premiered>
   <studio></studio>
   <tvdbid></tvdbid>
   <imdbid></imdbid>
   <genre></genre>
</tvshow>)";

        checkSameXml(expectedNfo, writer.getTvShowXml().trimmed());
    }

    SECTION("Full movie details")
    {
        // Taken from https://kodi.wiki/view/NFO_files/TV_shows

        /*
         *
Currently not yet supported:

  <originaltitle>TtvshowC09</originaltitle>
  <userrating>3</userrating>

  These are listed on the Kodi wiki but seem to be wrong:
  <season>5</season>
  <displayseason>-1</displayseason>
  <displayepisode>-1</displayepisode>
  <playcount>0</playcount>
  <tagline>A tagline</tagline>
  <lastplayed></lastplayed>
  <year>1999</year>
  <aired></aired>
  <trailer></trailer>
  <dateadded>2017-05-10 08:44:24</dateadded>
  <path>E:\TV Shows-Test - Copy\Angel\</path>
  <filenameandpath></filenameandpath>
  <basepath>E:\TV Shows-Test - Copy\Angel\</basepath>
  <art>
    <banner>E:\TV Shows-Test - Copy\Angel\banner.jpg</banner>
    <fanart>E:\TV Shows-Test - Copy\Angel\fanart.jpg</fanart>
    <poster>E:\TV Shows-Test - Copy\Angel\poster.jpg</poster>
    <season num="-1">
      <poster>E:\TV Shows-Test - Copy\Angel\season-all-poster.jpg</poster>
    </season>
    <season num="0">
      <poster>http://thetvdb.com/banners/seasons/71035-0-2.jpg</poster>
    </season>
    <season num="1">
      <banner>http://thetvdb.com/banners/seasonswide/71035-1.jpg</banner>
      <poster>E:\TV Shows-Test - Copy\Angel\season01-poster.jpg</poster>
    </season>
    <season num="2">
      <banner>http://thetvdb.com/banners/seasonswide/71035-2.jpg</banner>
      <poster>E:\TV Shows-Test - Copy\Angel\season02-poster.jpg</poster>
    </season>
    <season num="3">
      <banner>http://thetvdb.com/banners/seasonswide/71035-3.jpg</banner>
      <poster>E:\TV Shows-Test - Copy\Angel\season03-poster.jpg</poster>
    </season>
    <season num="4">
      <banner>http://thetvdb.com/banners/seasonswide/71035-4.jpg</banner>
      <poster>E:\TV Shows-Test - Copy\Angel\season04-poster.jpg</poster>
    </season>
    <season num="5">
      <banner>http://thetvdb.com/banners/seasonswide/71035-5.jpg</banner>
      <poster>E:\TV Shows-Test - Copy\Angel\season05-poster.jpg</poster>
    </season>
  </art>
  <thumb aspect="banner">http://thetvdb.com/banners/graphical/71035-g7.jpg</thumb>
  <thumb aspect="poster" type="season" season="5">http://thetvdb.com/banners/seasons/71035-5-2.jpg</thumb>
  <fanart url="http://thetvdb.com/banners/">
    <thumb dim="1920x1080" colors="" preview="_cache/fanart/original/71035-6.jpg">fanart/original/71035-6.jpg</thumb>
    <thumb dim="1920x1080" colors="" preview="_cache/fanart/original/71035-18.jpg">fanart/original/71035-18.jpg</thumb>
  </fanart>
  <file></file>
  <episodeguide>
    <url cache="71035-en.xml">http://thetvdb.com/api/439DFEBA9D3059C6/series/71035/all/en.zip</url>
  </episodeguide>
  <resume>
    <position>0.000000</position>
    <total>0.000000</total>
  </resume>

  Todo:
  - one node for each genre instead of one
      <genre>Action</genre>
      <genre>Comedy</genre>
      <genre>Drama</genre>
  - both id and uniqueid?
      <id>71035</id>
  - distinguish between plot and overview
  - remove following tags:
      <tvdbid/>
      <imdbid/>
  - add <order>1</order> to <actor>

         */

        TvShow show;
        show.setName("Angels");
        show.setShowTitle("Angels");
        show.setSortTitle("TtvshowC15");
        show.setId(TvDbId(71035));
        {
            Rating rating;
            rating.rating = 8.6;
            rating.voteCount = 88;
            rating.maxRating = 10;
            show.ratings().push_back(rating);
        }
        show.setCertification(Certification("TV-PG"));
        show.setRuntime(45min);
        show.setTop250(4);
        show.setFirstAired(QDate::fromString("1999-10-05", "yyyy-MM-dd"));
        show.setOverview("Angel is an American television series, a spin-off from the television series Buffy the "
                         "Vampire Slayer. Angel (David Boreanaz), a 240-year old vampire cursed with a conscience, "
                         "haunts the dark streets of Los Angeles alone");
        show.addGenre("Action");
        show.addGenre("Comedy");
        show.addGenre("Drama");
        show.addTag("BestTag");
        show.setStatus("Ended");
        show.setNetwork("The WB");
        {
            Poster banner;
            banner.thumbUrl = "http://thetvdb.com/banners/graphical/71035-g7.jpg";
            show.addBanner(banner);
        }
        {
            Poster poster;
            poster.season = SeasonNumber(5);
            poster.thumbUrl = "http://thetvdb.com/banners/seasons/71035-5-2.jpg";
            show.addSeasonPoster(SeasonNumber(5), poster);
        }
        {
            Actor actor;
            actor.name = "David Boreanaz";
            actor.role = "Angel";
            actor.thumb = "http://thetvdb.com/banners/actors/6309.jpg";
            show.addActor(actor);
        }
        {
            Actor actor;
            actor.name = "Stephanie Romanov";
            actor.role = "Lilah Morgan";
            show.addActor(actor);
        }

        mediaelch::kodi::TvShowXmlWriterV18 writer(show);

        const QByteArray expectedNfo = R"(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<tvshow>
  <title>Angels</title>
  <showtitle>Angels</showtitle>
  <sorttitle clear="true">TtvshowC15</sorttitle>
  <uniqueid type="unknown" default="true">71035</uniqueid>
  <ratings>
    <rating max="10" name="default" default="true">
      <value>8.6</value>
      <votes>88</votes>
    </rating>
  </ratings>
  <top250>4</top250>
  <episode>0</episode>
  <plot>Angel is an American television series, a spin-off from the television series Buffy the Vampire Slayer. Angel (David Boreanaz), a 240-year old vampire cursed with a conscience, haunts the dark streets of Los Angeles alone</plot>
  <outline>Angel is an American television series, a spin-off from the television series Buffy the Vampire Slayer. Angel (David Boreanaz), a 240-year old vampire cursed with a conscience, haunts the dark streets of Los Angeles alone</outline>
  <mpaa>TV-PG</mpaa>
  <premiered>1999-10-05</premiered>
  <studio>The WB</studio>
  <tvdbid/>
  <imdbid/>
  <status>Ended</status>
  <runtime>45</runtime>
  <genre>Action / Comedy / Drama</genre>
  <tag>BestTag</tag>
  <actor>
    <name>David Boreanaz</name>
    <role>Angel</role>
    <thumb>http://thetvdb.com/banners/actors/6309.jpg</thumb>
  </actor>
  <actor>
    <name>Stephanie Romanov</name>
    <role>Lilah Morgan</role>
  </actor>
</tvshow>
)";

        QString actual = writer.getTvShowXml().trimmed();
        checkSameXml(expectedNfo, actual);
    }
}