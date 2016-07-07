
/*
 * Copyright (C) 2016 Bastian Gschrey & Markus Ippy
 *
 * Digital Gauges for Apexi Power FC for RX7 on Raspberry Pi
 *
 *
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 *
 * No warranty is made or implied. You use this program at your own risk.
 */

/*!
  \file serial.cpp
  \brief Raspexi Viewer Power FC related functions
  \author Bastian Gschrey
  \credits to Suriyan Laohaprapanon & Jacob Donley
 */


#include "serial.h"
#include <QDebug>
#include <QThread>

Serial::Serial(QObject *parent) : QObject(parent)
{
    serialport = new QSerialPort(this);
    connect(this->serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
}

//function for flushing all serial buffers
void Serial::clear() const
{
    serialport->clear();

}

//function to open serial port
void Serial::openConnection(SerialSetting::Settings p)
{
    qDebug() << "Enter openConnection function";
    serialport->setBaudRate(QSerialPort::Baud57600);
    qDebug() <<"set baud";
    serialport->setPortName(p.portName);
    serialport->setParity(serialport->NoParity);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setStopBits(QSerialPort::OneStop);
    serialport->setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "Try to open SerialPort:";

    if(serialport->open(QIODevice::ReadWrite) == false)
    {
        qDebug() << serialport->errorString();
    }
    qDebug() << "Portname: " << p.portName;

}

void Serial::closeConnection()
{
    serialport->close();
}


//Serial requests are send via Serial
void Serial::getAdvData()
{
    serialport->write(QByteArray::fromHex("F0020D"));
}

void Serial::getSensorData()
{
    serialport->write(QByteArray::fromHex("DE021F"));
}

void Serial::getAux()
{
    serialport->write(QByteArray::fromHex("0002FD"));
}

void Serial::getMapIndices()
{
    serialport->write(QByteArray::fromHex("DB0222"));

}
void Serial::getBasic()
{
    serialport->write(QByteArray::fromHex("DA0223"));
}

//Map Readout
void Serial::getRevIdle()
{
    serialport->write(QByteArray::fromHex("B80245"));
}
void Serial::getSensorStrings()
{
    serialport->write(QByteArray::fromHex("DD0220"));
}
void Serial::getPimStrInjA()
{
    serialport->write(QByteArray::fromHex("CB0232"));
}
void Serial::getVersion()
{
    serialport->write(QByteArray::fromHex("F50208"));
}
void Serial::getMapRef()
{
    serialport->write(QByteArray::fromHex("8A0273"));
}
void Serial::getLeadign1()
{
    serialport->write(QByteArray::fromHex("760287"));
}
void Serial::getLeadign2()
{
    serialport->write(QByteArray::fromHex("770286"));
}
void Serial::getLeadign3()
{
    serialport->write(QByteArray::fromHex("780285"));
}
void Serial::getLeadign4()
{
    serialport->write(QByteArray::fromHex("790284"));
}
void Serial::getTrailIgn1()
{
    serialport->write(QByteArray::fromHex("81027C"));
}
void Serial::getTrailIgn2()
{
    serialport->write(QByteArray::fromHex("82027B"));
}
void Serial::getTrailIgn3()
{
    serialport->write(QByteArray::fromHex("83027A"));
}
void Serial::getTrailIgn4()
{
    serialport->write(QByteArray::fromHex("840279"));
}
void Serial::getInitPlatform()
{
    serialport->write(QByteArray::fromHex("F3020A"));
}
void Serial::getInjOverlap()
{
    serialport->write(QByteArray::fromHex("7B0282"));
}
void Serial::getInjvsFuelT()
{
    serialport->write(QByteArray::fromHex("7C0281"));
}
void Serial::getTurboTrans()
{
    serialport->write(QByteArray::fromHex("7D0280"));
}
void Serial::getOilervsWaterT()
{
    serialport->write(QByteArray::fromHex("7E027F"));
}
void Serial::getFanvsWater()
{
    serialport->write(QByteArray::fromHex("7F027E"));
}
void Serial::getInjcorr1()
{
    serialport->write(QByteArray::fromHex("860277"));
}
void Serial::getInjcorr2()
{
    serialport->write(QByteArray::fromHex("870276"));
}
void Serial::getInjcorr3()
{
    serialport->write(QByteArray::fromHex("880275"));
}
void Serial::getInjcorr4()
{
    serialport->write(QByteArray::fromHex("890274"));
}
void Serial::getFuelInj()
{
    serialport->write(QByteArray::fromHex("8D0270"));
}
void Serial::getCranking()
{
    serialport->write(QByteArray::fromHex("8E026F"));
}
void Serial::getWaterTcorr()
{
    serialport->write(QByteArray::fromHex("8F026E"));
}
void Serial::getInjvsWaterBoost()
{
    serialport->write(QByteArray::fromHex("90026D"));
}
void Serial::getInjvsAirTBoost()
{
    serialport->write(QByteArray::fromHex("91026C"));
}
void Serial::getInjPrimaryLag()
{
    serialport->write(QByteArray::fromHex("92026B"));
}
void Serial::getAccInj()
{
    serialport->write(QByteArray::fromHex("93026A"));
}
void Serial::getInjvsAccel()
{
    serialport->write(QByteArray::fromHex("940269"));
}
void Serial::getIgnvsAircold()
{
    serialport->write(QByteArray::fromHex("960267"));
}
void Serial::getIgnvsWater()
{
    serialport->write(QByteArray::fromHex("980265"));
}
void Serial::getIgnvsAirwarm()
{
    serialport->write(QByteArray::fromHex("9A0263"));
}
void Serial::getLIgnvsRPM()
{
    serialport->write(QByteArray::fromHex("9B0262"));
}
void Serial::getIgnvsBatt()
{
    serialport->write(QByteArray::fromHex("9C0261"));
}
void Serial::getBoostvsIgn()
{
    serialport->write(QByteArray::fromHex("9D0260"));
}


//End of serial requests


void Serial::readyToRead()
{

    emit SIG_dataAvailable(serialport->readAll());
}


void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
         Serial::getRevIdle();
         requestIndex++;
         break;
    case 1:
         Serial::getSensorStrings();
         requestIndex++;
         break;
    case 2:
         Serial::getPimStrInjA();
         requestIndex++;
         break;
    case 3:
         Serial::getVersion();
         requestIndex++;
         break;
    case 4:
         Serial::getMapRef();
         requestIndex++;
         break;
    case 5:
         Serial::getRevIdle();
         requestIndex++;
         break;
    case 6:
         Serial::getLeadign1();
         requestIndex++;
         break;
    case 7:
         Serial::getLeadign2();
         requestIndex++;
         break;
    case 8:
         Serial::getLeadign3();
         requestIndex++;
         break;
    case 9:
         Serial::getLeadign4();
         requestIndex++;
         break;
    case 10:
         Serial::getTrailIgn1();
         requestIndex++;
         break;
    case 11:
         Serial::getTrailIgn2();
         requestIndex++;
         break;
    case 12:
         Serial::getTrailIgn3();
         requestIndex++;
         break;
    case 13:
         Serial::getTrailIgn4();
         requestIndex++;
         break;
    case 14:
         Serial::getInitPlatform();
         requestIndex++;
         break;
    case 15:
         Serial::getInjOverlap();
         requestIndex++;
         break;
    case 16:
         Serial::getInjvsFuelT();
         requestIndex++;
         break;
    case 17:
         Serial::getTurboTrans();
         requestIndex++;
         break;
    case 18:
         Serial::getOilervsWaterT();
         requestIndex++;
         break;
    case 19:
         Serial::getFanvsWater();
         requestIndex++;
         break;
    case 20:
         Serial::getInjcorr1();
         requestIndex++;
         break;
    case 21:
         Serial::getInjcorr2();
         requestIndex++;
         break;
    case 22:
         Serial::getInjcorr3();
         requestIndex++;
         break;
    case 23:
         Serial::getInjcorr4();
         requestIndex++;
         break;
    case 24:
         Serial::getFuelInj();
         requestIndex++;
         break;
    case 25:
         Serial::getCranking();
         requestIndex++;
         break;
    case 26:
         Serial::getWaterTcorr();
         requestIndex++;
         break;
    case 27:
         Serial::getInjvsWaterBoost();
         requestIndex++;
         break;
    case 28:
         Serial::getInjvsAirTBoost();
         requestIndex++;
         break;
    case 29:
         Serial::getInjPrimaryLag();
         requestIndex++;
         break;
    case 30:
         Serial::getAccInj();
         requestIndex++;
         break;
    case 31:
         Serial::getInjvsAccel();
         requestIndex++;
         break;
    case 32:
         Serial::getIgnvsAircold();
         requestIndex++;
         break;
    case 33:
         Serial::getIgnvsWater();
         requestIndex++;
         break;
    case 34:
         Serial::getIgnvsAirwarm();
         requestIndex++;
         break;
    case 35:
         Serial::getLIgnvsRPM();
         requestIndex++;
         break;
    case 36:
         Serial::getIgnvsBatt();
         requestIndex++;
         break;
    case 37:
         Serial::getBoostvsIgn();
         requestIndex++;
         break;
// Live Data
    case 38:
        Serial::getAdvData();
        requestIndex++;
        break;
    case 39:
        Serial::getAux();
        requestIndex++;
        break;
    case 40:
        Serial::getMapIndices();
        requestIndex++;
        break;
    case 41:
        Serial::getSensorData();
        requestIndex++;
        break;
    case 42:
        Serial::getBasic();
        requestIndex = 38;
        break;
    }


}


