/**********************************************************************
Weathergrib: meteorological GRIB file viewer
Copyright (C) 2008-2012 - Jacques Zaninetti - http://www.zygrib.org

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

/*************************

Download GRIB File on zygrib server

*************************/

#ifndef FILELOADER_GRIB_H
#define FILELOADER_GRIB_H

#include <QObject>
#include <QtNetwork>
#include <QBuffer>
#include <QJsonDocument>

#include "FileLoader.h"
#include "Util.h"

class FileLoaderGRIB : public QObject, FileLoader
{ Q_OBJECT
    public:
        FileLoaderGRIB (QNetworkAccessManager *manager, QWidget *parent);
        ~FileLoaderGRIB();
        
        void getGribFile( const QString& atmModel,
				float x0, float y0, float x1, float y1,
				float resolution, int interval, int days,
                const QString& cycle,
				bool wind, bool pressure, bool rain,
				bool cloud, bool temp, bool humid, bool isotherm0,
                bool snowDepth,
				bool snowCateg, bool frzRainCateg,
                bool CAPEsfc, bool CINsfc, bool reflectivity,
				bool altitudeData200,
				bool altitudeData300,
				bool altitudeData400,
				bool altitudeData500,
				bool altitudeData600,
				bool altitudeData700,
				bool altitudeData850,
				bool altitudeData925,
				bool skewTData,
				bool GUSTsfc,
                const QString& wvModel,
                bool sgwh,
                bool swell,
                bool wwav
            );
        void stop();
        void abort();
        
    private:
		QString scriptpath;
		QString scriptname;
//		QString scriptstock;
        QByteArray arrayContent;
        QWidget *parent;
        
        QString fileName;
        QString checkSumSHA1;
        int     step;
        int     fileSize;
        //QStrinq strbuf;
        //QByteArray xserv;
		
//        QString zygriblog;
//        QString zygribpwd;

		QNetworkReply *reply_step1;
		QNetworkReply *reply_step2;
		bool downloadError;

    public slots:
        void downloadProgress (qint64 done, qint64 total);
		void slotNetworkError (QNetworkReply::NetworkError);
		void slotFinished_step1 ();
		void slotFinished_step2 ();

    signals:
        void signalGribDataReceived (QByteArray *content, QString);
        void signalGribReadProgress (int step, int done, int total);
        void signalGribSendMessage (QString msg);
        void signalGribStartLoadData ();
        void signalGribLoadError (QString msg);
};


#endif
