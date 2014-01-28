////////////////////////////////////////////////////////////////////////////
// Program Name: titleInfoList.h
// Created     : January 18, 2014
//
// Copyright (c) 2013 Martin Thwaites
//                                          
// Licensed under the GPL v2 or later, see COPYING for details
//
////////////////////////////////////////////////////////////////////////////

#ifndef TVSHOWINFOLIST_H_
#define TVSHOWINFOLIST_H_

#include <QVariantList>

#include "serviceexp.h" 
#include "datacontracthelper.h"

#include "seriesInfo.h"

namespace DTC
{

    class SERVICE_PUBLIC SeriesInfoList : public QObject
    {
        Q_OBJECT
        Q_CLASSINFO( "version", "1.0" );

        // Q_CLASSINFO Used to augment Metadata for properties.
        // See datacontracthelper.h for details

        Q_CLASSINFO( "SeriesList", "type=DTC::SeriesInfo");

        Q_PROPERTY( QVariantList SeriesList READ SeriesList DESIGNABLE true )

        PROPERTYIMP_RO_REF( QVariantList, SeriesList )

        public:

            static inline void InitializeCustomTypes();

            SeriesInfoList(QObject *parent = 0)
                : QObject( parent )
            {
            }

            SeriesInfoList( const SeriesInfoList &src )
            {
                Copy( src );
            }

            void Copy( const SeriesInfoList &src )
            {
                CopyListContents< SeriesInfo >( this, m_SeriesList, src.m_SeriesList );
            }

            SeriesInfo *AddNewTVShowInfo()
            {
                // We must make sure the object added to the QVariantList has
                // a parent of 'this'

                SeriesInfo *pObject = new SeriesInfo( this );
                m_SeriesList.append( QVariant::fromValue<QObject *>( pObject ));

                return pObject;
            }

    };

} // namespace DTC

Q_DECLARE_METATYPE( DTC::SeriesInfoList  )
Q_DECLARE_METATYPE( DTC::SeriesInfoList* )

namespace DTC
{
    inline void SeriesInfoList::InitializeCustomTypes()
    {
        qRegisterMetaType< SeriesInfoList   >();
        qRegisterMetaType< SeriesInfoList*  >();

        SeriesInfo::InitializeCustomTypes();
    }
}

#endif
