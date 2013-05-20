/*Copyright (C) <2013> <Plestan> <Kévin>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#ifndef CORRECTION_H
#define CORRECTION_H

#include "spinBox.h"
#include "modeEnum.h"
#include "TimeRecordMgr.h"
#include "QLabel"

class Correction : public QObject
{
    Q_OBJECT

public:
    Correction(Mode mode, const int multiple, int* order, int *userAnswers, const int time = 0);
    Correction(int* multiple, int* order, int* userAnswers, const int time = 0);

    ~Correction();

    int getCorrection(QLabel *correction[][10]);

    void saveTime() const;
private:
    int seconds;
    int Multiple;
    int note;

    int* orderTab;
    int* multipleTab;
    int* answers;

    bool isHardMode;

    TimeRecordMgr *manager;

    Mode difficultyMode;

    void manageTime();
    void notation(int resultat[], bool isCorrect[]);
    void doCorrection(QLabel *correction[][10], int resultat[], bool isCorrect[]) const;

    QString getModeGroupName() const;
    QString getModeKeyName() const;
signals:
    void newRecord(RecordState, int);
public slots:
    void isRecordValid(RecordState, int);
};

#endif // CORRECTION_H
