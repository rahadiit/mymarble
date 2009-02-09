//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009 Patrick Spendrin  <ps_ml@gmx.de>
//

#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointF>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include "MarbleDirs.h"
#include "GeoDataParser.h"

// Feature:
#include "GeoDataFolder.h"
#include "GeoDataDocument.h"
#include "GeoDataPlacemark.h"

// Geometry:
#include "GeoDataPolygon.h"
#include "GeoDataMultiGeometry.h"
#include "GeoDataLineString.h"
#include "GeoDataLinearRing.h"
#include "GeoDataPoint.h"

// StyleSelector:
#include "GeoDataColorStyle.h"
#include "GeoDataIconStyle.h"
#include "GeoDataLabelStyle.h"
#include "GeoDataLineStyle.h"
#include "GeoDataPolyStyle.h"
#include "GeoDataStyleMap.h"

// misc:
#include "GeoDataHotSpot.h"
#include "GeoDataLatLonBox.h"
#include "GeoDataLatLonAltBox.h"
#include "GeoDataCoordinates.h"

namespace Marble
{

class CopyTest : public QObject {
    Q_OBJECT
    private slots:
        void initTestCase();
        // misc.:
        void copyCoordinates();
        void copyHotSpot();
        void copyLatLonBox();
        void copyLatLonAltBox();

        // GeoDataGeometry:
        void copyLineString();
        void copyLinearRing();
        void copyPoint();
        void copyPolygon();
        void copyMultiGeometry();

        // GeoDataFeature:
        void copyDocument();
        void copyFolder();
        void copyPlacemark();

        // StyleSelector:
        void copyStyle();
        void copyIconStyle();
        void copyLabelStyle();
        void copyLineStyle();
        void copyPolyStyle();
        void copyStyleMap();
    private:
        QStringList coordString;
        GeoDataCoordinates coord1;
        GeoDataCoordinates coord2;
        GeoDataCoordinates coord3;
};

void CopyTest::initTestCase() {
    MarbleDirs::setMarbleDataPath( DATA_PATH );
    MarbleDirs::setMarblePluginPath( PLUGIN_PATH );

    coordString << QString(" 13� 42' 38\"E,  51� 01' 24\"N" );
    coordString << QString(" 14� 42' 38\"E,  52� 01' 24\"N" );
    coordString << QString(" 15� 42' 38\"E,  53� 01' 24\"N" );

    coord1.set(13.7107,51.0235, 123.4, GeoDataCoordinates::Degree);
    coord1.setDetail(2);
    QCOMPARE(coord1.altitude(), 123.4);
    QCOMPARE(coord1.detail(), 2);
    QCOMPARE(coord1.toString(), coordString[0]);
    
    coord2.set(14.7107,52.0235, 133.4, GeoDataCoordinates::Degree);
    coord2.setDetail(3);
    QCOMPARE(coord2.altitude(), 133.4);
    QCOMPARE(coord2.detail(), 3);
    QCOMPARE(coord2.toString(), coordString[1]);

    coord3.set(15.7107,53.0235, 143.4, GeoDataCoordinates::Degree);
    coord3.setDetail(4);
    QCOMPARE(coord3.altitude(), 143.4);
    QCOMPARE(coord3.detail(), 4);
    QCOMPARE(coord3.toString(), coordString[2]);
}

void CopyTest::copyCoordinates() {
    GeoDataCoordinates other = coord1;
    
    // make sure that the coordinate contains the right values
    QCOMPARE(other.altitude(), 123.4);
    QCOMPARE(other.detail(), 2);
    QCOMPARE(other.toString(), coordString[0]);
    
    QVERIFY(coord1 == other);
}

void CopyTest::copyPoint() {
    GeoDataPoint point;

    point.set(13.7107,51.0235, 123.4, GeoDataCoordinates::Degree);
    point.setDetail(2);
    point.setExtrude( true );

    // make sure that the coordinate contains the right values
    QCOMPARE(point.altitude(), 123.4);
    QCOMPARE(point.detail(), 2);
    QCOMPARE(point.toString(), coordString[0]);
    QCOMPARE(point.extrude(), true);

    GeoDataPoint other = point;
    
    // make sure that the coordinate contains the right values
    QCOMPARE(other.altitude(), 123.4);
    QCOMPARE(other.detail(), 2);
    QCOMPARE(other.toString(), coordString[0]);
    QCOMPARE(other.extrude(), true);
    
    QVERIFY(point == other);
    
    point.setDetail(17);
    point.setExtrude(false);
    QCOMPARE(other.detail(), 2);
    QCOMPARE(point.detail(), 17);
    QCOMPARE(other.extrude(), true);
    QCOMPARE(point.extrude(), false);
}

void CopyTest::copyLineString() {
    GeoDataLineString lineString;
    lineString.setTessellate(true);
    

    lineString.append(coord1);
    lineString.append(coord2);
    lineString.append(coord3);
    QVERIFY(lineString.size() == 3);

    GeoDataLineString other = lineString;
    QVERIFY(other.size() == 3);

    QCOMPARE(lineString.at(0).altitude(), 123.4);
    QCOMPARE(lineString.at(0).detail(), 2);
    QCOMPARE(lineString.at(0).toString(), coordString[0]);
    
    QCOMPARE(other.at(2).altitude(), 143.4);
    QCOMPARE(other.at(2).detail(), 4);
    QCOMPARE(other.at(2).toString(), coordString[2]);
    
    QVERIFY(other.at(2) == coord3);
    QVERIFY(other.tessellate());
}

void CopyTest::copyLinearRing() {
    GeoDataLinearRing linearRing;

    linearRing.setTessellate(true);


    linearRing.append(coord1);
    linearRing.append(coord2);
    linearRing.append(coord3);
    QVERIFY(linearRing.size() == 3);

    GeoDataLinearRing other = linearRing;
    QVERIFY(other.size() == 3);

    QCOMPARE(linearRing.at(0).altitude(), 123.4);
    QCOMPARE(linearRing.at(0).detail(), 2);
    QCOMPARE(linearRing.at(0).toString(), coordString[0]);
    
    QCOMPARE(other.at(2).altitude(), 143.4);
    QCOMPARE(other.at(2).detail(), 4);
    QCOMPARE(other.at(2).toString(), coordString[2]);
    
    QVERIFY(other.at(2) == coord3);
    QVERIFY(other.tessellate());
}

void CopyTest::copyPolygon() {
    GeoDataLinearRing linearRing1;
    GeoDataLinearRing linearRing2;
    GeoDataLinearRing linearRing3;
    GeoDataLinearRing linearRing4;
    
    linearRing1.append(coord1); linearRing1.append(coord2); linearRing1.append(coord3);
    linearRing2.append(coord3); linearRing2.append(coord2); linearRing2.append(coord1);
    linearRing3.append(coord1); linearRing3.append(coord2); linearRing3.append(coord3);
    linearRing3.append(coord3); linearRing3.append(coord2); linearRing3.append(coord1);
    linearRing4.append(coord3); linearRing4.append(coord2); linearRing4.append(coord1);
    linearRing4.append(coord1); linearRing4.append(coord2); linearRing4.append(coord3);
    
    GeoDataPolygon polygon;
    polygon.appendInnerBoundary(linearRing1);
    polygon.appendInnerBoundary(linearRing2);
    polygon.appendInnerBoundary(linearRing3);
    polygon.setOuterBoundary(linearRing4);
    polygon.setTessellate(true);
    
    QCOMPARE(polygon.innerBoundaries().size(), 3);
    
    GeoDataPolygon other = polygon;
    QCOMPARE(other.innerBoundaries().size(), 3);
    QVERIFY(other.innerBoundaries()[0][0] == coord1);
    QVERIFY(other.innerBoundaries()[0][1] == coord2);
    QVERIFY(other.innerBoundaries()[0][2] == coord3);
    QVERIFY(other.innerBoundaries()[1][0] == coord3);
    QVERIFY(other.innerBoundaries()[1][1] == coord2);
    QVERIFY(other.innerBoundaries()[1][2] == coord1);
    QVERIFY(other.innerBoundaries()[2][0] == coord1);
    QVERIFY(other.innerBoundaries()[2][1] == coord2);
    QVERIFY(other.innerBoundaries()[2][2] == coord3);
    QVERIFY(other.innerBoundaries()[2][3] == coord3);
    QVERIFY(other.innerBoundaries()[2][4] == coord2);
    QVERIFY(other.innerBoundaries()[2][5] == coord1);
    
    QCOMPARE(other.outerBoundary().size(), 6);

    QVERIFY(other.outerBoundary()[0] == coord3);
    QVERIFY(other.outerBoundary()[1] == coord2);
    QVERIFY(other.outerBoundary()[2] == coord1);
    QVERIFY(other.outerBoundary()[3] == coord1);
    QVERIFY(other.outerBoundary()[4] == coord2);
    QVERIFY(other.outerBoundary()[5] == coord3);
    
    QVERIFY(other.tessellate());
}

void CopyTest::copyMultiGeometry() {
    GeoDataMultiGeometry multiGeometry;
    GeoDataLinearRing linearRing1;
    GeoDataLinearRing linearRing2;
    GeoDataLinearRing linearRing3;
    GeoDataLinearRing linearRing4;
    
    linearRing1.append(coord1); linearRing1.append(coord2); linearRing1.append(coord3);
    linearRing2.append(coord3); linearRing2.append(coord2); linearRing2.append(coord1);
    linearRing3.append(coord1); linearRing3.append(coord2); linearRing3.append(coord3);
    linearRing3.append(coord3); linearRing3.append(coord2); linearRing3.append(coord1);
    linearRing4.append(coord3); linearRing4.append(coord2); linearRing4.append(coord1);
    linearRing4.append(coord1); linearRing4.append(coord2); linearRing4.append(coord3);
    
    GeoDataPolygon polygon;
    polygon.appendInnerBoundary(linearRing1);
    polygon.appendInnerBoundary(linearRing2);
    polygon.appendInnerBoundary(linearRing3);
    polygon.setOuterBoundary(linearRing4);
    polygon.setTessellate(true);
    
    multiGeometry.append(polygon);
    multiGeometry.append(linearRing1);
    multiGeometry.append(linearRing2);
    multiGeometry.append(linearRing3);
    multiGeometry.append(linearRing4);

    GeoDataMultiGeometry other = multiGeometry;

    QCOMPARE(other.size(), 5);
/*    QCOMPARE(reinterpret_cast<GeoDataPolygon>(other[0]).innerBoundaries().size(), 3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[0][0] == coord1);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[0][1] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[0][2] == coord3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[1][0] == coord3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[1][1] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[1][2] == coord1);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][0] == coord1);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][1] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][2] == coord3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][3] == coord3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][4] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).innerBoundaries()[2][5] == coord1);
    
    QCOMPARE(static_cast<GeoDataPolygon>(other[0]).outerBoundary().size(), 6);

    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[0] == coord3);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[1] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[2] == coord1);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[3] == coord1);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[4] == coord2);
    QVERIFY(static_cast<GeoDataPolygon>(other[0]).outerBoundary()[5] == coord3);
    
    QVERIFY(other[1][0] == coord1);
    QVERIFY(other[1][1] == coord2);
    QVERIFY(other[1][2] == coord3);
    QVERIFY(other[2][0] == coord3);
    QVERIFY(other[2][1] == coord2);
    QVERIFY(other[2][2] == coord1);
    QVERIFY(other[3][0] == coord1);
    QVERIFY(other[3][1] == coord2);
    QVERIFY(other[3][2] == coord3);
    QVERIFY(other[3][3] == coord3);
    QVERIFY(other[3][4] == coord2);
    QVERIFY(other[3][5] == coord1);
    QVERIFY(other[4][0] == coord3);
    QVERIFY(other[4][1] == coord2);
    QVERIFY(other[4][2] == coord1);
    QVERIFY(other[4][3] == coord1);
    QVERIFY(other[4][4] == coord2);
    QVERIFY(other[4][5] == coord3);*/
    QSKIP("Test not implemented",SkipSingle);
}

void CopyTest::copyDocument() {
    QSKIP("Test not implemented",SkipSingle);
}

void CopyTest::copyFolder() {
    QSKIP("Test not implemented",SkipSingle);
}

void CopyTest::copyPlacemark() {
    QSKIP("Test not implemented",SkipSingle);
}

void CopyTest::copyHotSpot() {
    QPointF point(0.25, 0.75);
    

    GeoDataHotSpot first(point);
    GeoDataHotSpot::Units xunits;
    GeoDataHotSpot::Units yunits;
    GeoDataHotSpot second = first;

    QVERIFY(first.hotSpot(xunits, yunits) == QPointF(0.25, 0.75));
    QVERIFY(second.hotSpot(xunits, yunits) == QPointF(0.25, 0.75));

    first.setHotSpot(QPointF(0.3333333, 0.666666));
    
    QVERIFY(first.hotSpot(xunits, yunits) == QPointF(0.3333333, 0.666666));
    QVERIFY(second.hotSpot(xunits, yunits) == QPointF(0.25, 0.75));
}

void CopyTest::copyLatLonBox() {
    // north south east west
    GeoDataLatLonBox llbox(30.1, 12.2, 110.0, 44.9, GeoDataCoordinates::Degree);
    QCOMPARE(llbox.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(llbox.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(llbox.east(GeoDataCoordinates::Degree), 110.0);
    QCOMPARE(llbox.west(GeoDataCoordinates::Degree), 44.9);

    GeoDataLatLonBox other = llbox;

    QCOMPARE(other.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(other.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(other.east(GeoDataCoordinates::Degree), 110.0);
    QCOMPARE(other.west(GeoDataCoordinates::Degree), 44.9);
    
    llbox.setNorth(0.1);
    other.setSouth(1.4);
    
    QCOMPARE(llbox.north(), 0.1);
    QCOMPARE(llbox.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(other.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(other.south(), 1.4);
}

void CopyTest::copyLatLonAltBox() {
    GeoDataLatLonAltBox llabox(GeoDataLatLonBox(30.1, 12.2, 110.0, 44.9, GeoDataCoordinates::Degree));
    QCOMPARE(llabox.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(llabox.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(llabox.east(GeoDataCoordinates::Degree), 110.0);
    QCOMPARE(llabox.west(GeoDataCoordinates::Degree), 44.9);

    GeoDataLatLonAltBox other = llabox;

    QCOMPARE(other.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(other.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(other.east(GeoDataCoordinates::Degree), 110.0);
    QCOMPARE(other.west(GeoDataCoordinates::Degree), 44.9);
    
    llabox.setNorth(0.1);
    other.setSouth(1.4);
    
    QCOMPARE(llabox.north(), 0.1);
    QCOMPARE(llabox.south(GeoDataCoordinates::Degree), 12.2);
    QCOMPARE(other.north(GeoDataCoordinates::Degree), 30.1);
    QCOMPARE(other.south(), 1.4);
}

void CopyTest::copyStyle() {
    QSKIP("Test not implemented",SkipSingle);
}

void CopyTest::copyIconStyle() {
    // hotspot is not implemented as I am not sure how it should work
    GeoDataIconStyle icon;
    icon.setScale(2.0);

    QCOMPARE(icon.scale(), (float)2.0);

    GeoDataIconStyle other = icon;

    QCOMPARE(other.scale(), (float)2.0);

    icon.setScale(5.0);

    QCOMPARE(icon.scale(), (float)5.0);
    QCOMPARE(other.scale(), (float)2.0);
}

void CopyTest::copyLabelStyle() {
    QFont testFont(QFont("Sans Serif").family(), 12, 10, false);
    GeoDataLabelStyle label(testFont, Qt::red);
    label.setScale(2.0);

    QCOMPARE(label.scale(), (float)2.0);
    QVERIFY(label.color() == Qt::red);
    QVERIFY(label.font() == testFont);

    GeoDataLabelStyle other = label;

    QCOMPARE(other.scale(), (float)2.0);
    QVERIFY(other.color() == Qt::red);
    QVERIFY(other.font() == testFont);

    other.setColor(Qt::darkRed);
    label.setScale(5.0);

    QCOMPARE(label.scale(), (float)5.0);
    QCOMPARE(other.scale(), (float)2.0);
    QVERIFY(label.color() == Qt::red);
    QVERIFY(other.color() == Qt::darkRed);
}

void CopyTest::copyLineStyle() {
    GeoDataLineStyle line(Qt::green);
    line.setWidth(2.0);

    QCOMPARE(line.width(), (float)2.0);
    QVERIFY(line.color() == Qt::green);

    GeoDataLineStyle other = line;

    QCOMPARE(other.width(), (float)2.0);
    QVERIFY(other.color() == Qt::green);

    other.setColor(Qt::darkGreen);
    line.setWidth(5.0);

    QCOMPARE(line.width(), (float)5.0);
    QCOMPARE(other.width(), (float)2.0);
    QVERIFY(line.color() == Qt::green);
    QVERIFY(other.color() == Qt::darkGreen);
}

void CopyTest::copyPolyStyle() {
    GeoDataPolyStyle poly(Qt::blue);
    poly.setFill(true);
    poly.setOutline(false);

    QCOMPARE(poly.fill(), true);
    QCOMPARE(poly.outline(), false);
    QVERIFY(poly.color() == Qt::blue);

    GeoDataPolyStyle other = poly;

    QCOMPARE(other.fill(), true);
    QCOMPARE(other.outline(), false);
    QVERIFY(other.color() == Qt::blue);

    other.setOutline(true);
    poly.setColor( Qt::cyan );

    QCOMPARE(poly.outline(), false);
    QCOMPARE(other.outline(), true);
    QVERIFY(poly.color() == Qt::cyan);
    QVERIFY(other.color() == Qt::blue);
}

void CopyTest::copyStyleMap() {
    GeoDataStyleMap styleMap;
    QMap<QString,QString> testMap;
    styleMap["germany"] = "gst1";
    styleMap["germany"] = "gst2";
    styleMap["germany"] = "gst3";
    styleMap["poland"] = "pst1";
    styleMap["poland"] = "pst2";
    styleMap["poland"] = "pst3";
    testMap["germany"] = "gst1";
    testMap["germany"] = "gst2";
    testMap["germany"] = "gst3";
    testMap["poland"] = "pst1";
    testMap["poland"] = "pst2";
    testMap["poland"] = "pst3";
    styleMap.setLastKey("poland");

    QVERIFY(styleMap == testMap);
    QVERIFY(styleMap.lastKey() == QString("poland"));
}

}

QTEST_MAIN( Marble::CopyTest )

#include "CopyTest.moc"
