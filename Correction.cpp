﻿/*Copyright (C) <2012> <Plestan> <Kévin>

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

#include "Correction.h"

Correction::Correction(Mode mode, const int multiple, int *order, int* userAnswers, const int time) : Multiple(multiple), orderTab(order), answers(userAnswers), difficultyMode(mode), seconds(time), isHardMode(false)
{
}
Correction::Correction(int *multiple, int *order, int *userAnswers, const int time) : multipleTab(multiple), orderTab(order), answers(userAnswers), seconds(time), isHardMode(true)
{
}
int Correction::getCorrection(QLabel *correction[][10])
{
    int resultat[10];
    note = 10;

    bool isCorrect[10];
    for(int i = 0; i < 10; i++)
        isCorrect[i] = true;

    this->notation(resultat, isCorrect);
    this->doCorrection(correction, resultat, isCorrect);

    if(seconds != 0)
        this->manageTime();

    return note;
}
void Correction::notation(int resultat[], bool isCorrect[])
{
    if(!isHardMode)
    {
        for(int i = 0; i < 10; i++)
        {
            resultat[i] = Multiple*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isCorrect[i] = false;
                --note;
            }
        }
    }
    else
    {
        for(int i = 0; i < 10; i++)
        {
            resultat[i] = multipleTab[i]*orderTab[i];
            if(resultat[i] != answers[i])
            {
                isCorrect[i] = false;
                --note;
            }
        }
    }
}
void Correction::doCorrection(QLabel *correction[][10], int resultat[], bool isCorrect[]) const
{
    for(int i = 0; i < 10; i++)
    {
        if(isCorrect[i])
        {
            correction[0][i]->setPixmap(QPixmap("ok.png"));
            correction[1][i]->setText(tr("<span style=\"color: rgb(0, 200, 0);\">C'est correct !</span>"));
        }
        else
        {
            correction[0][i]->setPixmap(QPixmap("faux.png"));
            correction[1][i]->setText(tr("<span style=\"color: rgb(100, 0, 0);\">La bonne réponse était ")+QString::number(resultat[i])+"</span>");
        }
    }
}

inline void Correction::manageTime()
{
    manager = new TimeRecordMgr(QSettings::IniFormat, QSettings::UserScope, "Multifacile", seconds, this->getModeGroupName(), this->getModeKeyName());

    QObject::connect(manager, SIGNAL(isNewRecord(RecordState,int)), this, SLOT(isRecordValid(RecordState, int)));

    manager->CompareTime();
}
void Correction::isRecordValid(RecordState record, int lastRecordTime)
{
    if(record == RECORD && note == 10)
        emit newRecord(RECORD, lastRecordTime);
    else if(record == RECORD && note != 10)
        emit newRecord(UNVALIDRECORD, lastRecordTime);
    else
        emit newRecord(NORECORD, lastRecordTime);
}
void Correction::saveTime() const { manager->SaveRecordInFile(); }

QString Correction::getModeGroupName() const
{
    if(difficultyMode == EASY)
        return QString("EasyMode");
    else if(difficultyMode == MEDIUM)
        return QString("MediumMode");
    else
        return QString("HardMode");
}
QString Correction::getModeKeyName() const
{
    if(difficultyMode == EASY || difficultyMode == MEDIUM)
        return QString("TableDe"+QString::number(Multiple));
    else
        return QString();
}
Correction::~Correction()
{
    delete manager;

    manager = nullptr;
}
