/*
 * Copyright (C) 2021  Alfred Neumayer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * pvms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

class Machine: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
    Q_PROPERTY(QString arch MEMBER arch NOTIFY archChanged)
    Q_PROPERTY(QString hdd MEMBER hdd NOTIFY hddChanged)
    Q_PROPERTY(quint64 hddSize MEMBER hddSize NOTIFY hddSizeChanged)
    Q_PROPERTY(QString dvd MEMBER dvd NOTIFY dvdChanged)
    Q_PROPERTY(QString cpu MEMBER display NOTIFY cpuChanged)
    Q_PROPERTY(int cores MEMBER cores NOTIFY coresChanged)
    Q_PROPERTY(int mem MEMBER mem NOTIFY memChanged)
    Q_PROPERTY(QString display MEMBER display NOTIFY displayChanged)
    Q_PROPERTY(QString storage MEMBER storage NOTIFY storageChanged)
    Q_PROPERTY(bool enableFileSharing MEMBER enableFileSharing NOTIFY enableFileSharingChanged)

    Q_PROPERTY(bool running MEMBER running NOTIFY runningChanged)

public:
    Machine();
    ~Machine();

    QString name;
    QString arch;
    QString hdd;
    QString dvd;
    QString cpu;
    int cores;
    int mem; // MB
    QString display;
    bool enableFileSharing = false;

    bool running = false;

    // Storage path
    QString storage;

    // Only necessary during VM creation
    quint64 hddSize;

    // Only necessary for firmware
    QString flash1;
    QString flash2;

    Q_INVOKABLE bool start();
    Q_INVOKABLE void stop();

private:
    bool startQemu();
    QStringList getLaunchArguments();
    bool hasKvm();
    bool canVirtualize();
    QString getFileSharingDirectory();
    QString getFileSharingSocket();

    QProcess* m_process = nullptr;
    QProcess* m_fileSharingProcess = nullptr;

signals:
    void nameChanged();
    void archChanged();
    void cpuChanged();
    void hddChanged();
    void hddSizeChanged();
    void dvdChanged();
    void coresChanged();
    void memChanged();
    void displayChanged();
    void storageChanged();
    void enableFileSharingChanged();

    void runningChanged();

    void started();
    void stopped();
    void error(QString err);
    void fileSharingError(QString err);
};

#endif
