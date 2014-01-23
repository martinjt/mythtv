////////////////////////////////////////////////////////////////////////////
// Program Name: seriesInfo.h
// Created     : January 18, 2014
//
// Copyright (c) 2013 Martin Thwaites
//
// Licensed under the GPL v2 or later, see COPYING for details
//
////////////////////////////////////////////////////////////////////////////

#ifndef SERIESINFO_H_
#define SERIESINFO_H_

#include <QString>
#include <QUrl>

#include "serviceexp.h" 
#include "datacontracthelper.h"
#include "seasonInfo.h"

namespace DTC
{

/////////////////////////////////////////////////////////////////////////////

class SERVICE_PUBLIC SeriesInfo : public QObject
{
    Q_OBJECT
    Q_CLASSINFO( "version" , "1.0" )
    Q_CLASSINFO( "Seasons", "type=DTC::SeasonInfo" )

    Q_PROPERTY( QString         Title            READ Title             WRITE setTitle      )
    Q_PROPERTY( QString         Inetref          READ Inetref           WRITE setInetref    )
    Q_PROPERTY( QObject*        Banner           READ Banner                                )
    Q_PROPERTY( QObject*        Coverart         READ Coverart                              )
    Q_PROPERTY( QObject*        Fanart           READ Fanart                                )
    Q_PROPERTY( QVariantList    Seasons          READ Seasons           DESIGNABLE true     )

    PROPERTYIMP        ( QString     , Title    )
    PROPERTYIMP        ( QString     , Inetref  )
    PROPERTYIMP_PTR    ( ArtworkInfo , Banner   )
    PROPERTYIMP_PTR    ( ArtworkInfo , Coverart )
    PROPERTYIMP_PTR    ( ArtworkInfo , Fanart   )
    PROPERTYIMP_RO_REF ( QVariantList, Seasons  )

    public:

        static inline void InitializeCustomTypes();

        SeriesInfo(QObject *parent = 0)
            : QObject            ( parent )
        { 
        }
        
        SeriesInfo( const SeriesInfo &src )
        {
            Copy( src );
        }

        void Copy( const SeriesInfo &src )
        {
            m_Title     = src.m_Title    ;
            m_Inetref   = src.m_Inetref  ;
            m_Banner    = src.m_Banner   ;
            m_Coverart  = src.m_Coverart ;
            m_Fanart    = src.m_Fanart   ;
            CopyListContents< SeasonInfo >( this, m_Seasons, src.m_Seasons );
        }

        SeasonInfo *AddNewSeasonInfo()
        {
            // We must make sure the object added to the QVariantList has
            // a parent of 'this'

            SeasonInfo *pObject = new SeasonInfo( this );
            m_Seasons.append( QVariant::fromValue<QObject *>( pObject ));

            return pObject;
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

Q_DECLARE_METATYPE( DTC::SeriesInfo  )
Q_DECLARE_METATYPE( DTC::SeriesInfo* )

namespace DTC
{
inline void SeriesInfo::InitializeCustomTypes()
{
    qRegisterMetaType< SeriesInfo   >();
    qRegisterMetaType< SeriesInfo*  >();

    SeasonInfo::InitializeCustomTypes();
    ArtworkInfo::InitializeCustomTypes();
}
}

#endif
