////////////////////////////////////////////////////////////////////////////
// Program Name: titleInfo.h
// Created     : January 18, 2014
//
// Copyright (c) 2013 Martin Thwaites
//
// Licensed under the GPL v2 or later, see COPYING for details
//
////////////////////////////////////////////////////////////////////////////

#ifndef SEASONINFO_H_
#define SEASONINFO_H_

#include <QString>
#include <QDateTime>
#include <QUrl>

#include "serviceexp.h" 
#include "datacontracthelper.h"
#include "artworkInfo.h"

namespace DTC
{

/////////////////////////////////////////////////////////////////////////////

class SERVICE_PUBLIC SeasonInfo : public QObject
{
    Q_OBJECT
    Q_CLASSINFO( "version" , "1.0" )

    Q_PROPERTY( int             Number           READ Number            WRITE setNumber           )
    Q_PROPERTY( int             TotalEpisodes    READ TotalEpisodes     WRITE setTotalEpisodes    )
    Q_PROPERTY( QDateTime       LastEpisodeAdded READ LastEpisodeAdded  WRITE setLastEpisodeAdded )
    Q_PROPERTY( QObject*        Banner           READ Banner       )
    Q_PROPERTY( QObject*        Coverart         READ Coverart     )
    Q_PROPERTY( QObject*        Fanart           READ Fanart       )

    PROPERTYIMP    ( int         , Number           )
    PROPERTYIMP    ( int         , TotalEpisodes    )
    PROPERTYIMP    ( QDateTime   , LastEpisodeAdded )
    PROPERTYIMP_PTR( ArtworkInfo , Banner           )
    PROPERTYIMP_PTR( ArtworkInfo , Coverart         )
    PROPERTYIMP_PTR( ArtworkInfo , Fanart           )

    public:

        static inline void InitializeCustomTypes();

        SeasonInfo(QObject *parent = 0)
            : QObject            ( parent )
        { 
        }
        
        SeasonInfo( const SeasonInfo &src )
        {
            Copy( src );
        }

        void Copy( const SeasonInfo &src )
        {
            m_Number           = src.m_Number           ;
            m_TotalEpisodes    = src.m_TotalEpisodes    ;
            m_LastEpisodeAdded = src.m_LastEpisodeAdded ;
            m_Banner           = src.m_Banner           ;
            m_Coverart         = src.m_Coverart         ;
            m_Fanart           = src.m_Fanart           ;
        }

        void AddNewArtworkInfo(const QString &type,
                               const QString &filename)
        {
            if (type.toLower() == "fanart")
            {
                m_Fanart = new ArtworkInfo();
                m_Fanart->setStorageGroup("Fanart");
                m_Fanart->setType("fanart");
                m_Fanart->setURL(QString("/Content/GetImageFile?StorageGroup=%1"
                                         "&FileName=%2").arg("Fanart")
                              .arg(QUrl::toPercentEncoding(filename).constData()));
            }
            else if (type.toLower() == "coverart")
            {
                m_Coverart = new ArtworkInfo();
                m_Coverart->setStorageGroup("Coverart");
                m_Coverart->setType("coverart");
                m_Coverart->setURL(QString("/Content/GetImageFile?StorageGroup=%1"
                                           "&FileName=%2").arg("Coverart")
                              .arg(QUrl::toPercentEncoding(filename).constData()));
            }
            else if (type.toLower() == "banner")
            {
                m_Banner = new ArtworkInfo();
                m_Banner->setStorageGroup("Banners");
                m_Banner->setType("banner");
                m_Banner->setURL(QString("/Content/GetImageFile?StorageGroup=%1"
                                         "&FileName=%2").arg("Banners")
                              .arg(QUrl::toPercentEncoding(filename).constData()));
            }

        }
};

} // namespace DTC

Q_DECLARE_METATYPE( DTC::SeasonInfo  )
Q_DECLARE_METATYPE( DTC::SeasonInfo* )

namespace DTC
{
inline void SeasonInfo::InitializeCustomTypes()
{
    qRegisterMetaType< SeasonInfo   >();
    qRegisterMetaType< SeasonInfo*  >();

    ArtworkInfo::InitializeCustomTypes();
}
}

#endif
