/*Copyright (C) <2013> <Plestan> <K�vin>

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

#include "fen_correction.h"

Fen_correction::Fen_correction(const int multiple, SpinBox *reponses[], int *order, const int time, Mode mode)
{
    timeElapsed = time;

    this->setWindowTitle(tr("Correction"));

    tab = order;

    for(int i = 0; i < 4; i++)
        timeTab[i] = 0;

    for(int i = 0; i < 10; i++)
        reponse[i] = reponses[i]->value();
    for(int i = 0; i < 10; i++)
    {
        correction[0][i] = new QLabel;
        correction[1][i] = new QLabel;
    }

    correct = new Correction(mode, multiple, tab, reponse, timeElapsed);

    connect(correct, SIGNAL(newRecord(RecordState,int)), this, SLOT(openMessageBox(RecordState,int)));

    note = correct->getCorrection(correction);

    setWindowLayout(multiple);

    this->setLayout(vlayout);

    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}
Fen_correction::Fen_correction(SpinBox *reponses[], int *multipleOrder, int *order, const int time)
{
    if(time != 0)
        timeElapsed = time;

    this->setWindowTitle(tr("Correction"));

    tab = order;

    orderTab = multipleOrder;

    for(int i = 0; i < 10; i++)
        reponse[i] = reponses[i]->value();
    for(int i = 0; i < 10; i++)
    {
        correction[0][i] = new QLabel;
        correction[1][i] = new QLabel;
    }
    correct = new Correction(multipleOrder, order, reponse, time);

    connect(correct, SIGNAL(newRecord(RecordState,int)), this, SLOT(openMessageBox(RecordState,int)));

    note = correct->getCorrection(correction);

    setWindowLayout(orderTab);

    this->setLayout(vlayout);

    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

}
void Fen_correction::setWindowLayout(int multiple)
{
    for(int i = 0; i < 10; i++)
    {
        multiplication[i] = new QLabel();
        multiplication[i]->setText(QString::number(multiple)+ " x " + QString::number(tab[i]) + " = "+QString::number(reponse[i]));
    }

    texte = new QLabel(tr("<h3><strong>Voici la correction : </strong></h3>"));
    if(note >= 7)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: rgb(0, 200, 0);\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        if(note == 10)
            pngTotal->setPixmap(QPixmap("excellent.png"));
        else
            pngTotal->setPixmap(QPixmap("bien.png"));
    }
    else if(note <= 2)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: rgb(128, 0, 0);\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        pngTotal->setPixmap(QPixmap("mauvais.png"));
    }
    else
    {
        total = new QLabel(tr("Ta as eu <strong><span style=\"color: orange;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal =  new QLabel();
        pngTotal->setPixmap(QPixmap("moyen.png"));
    }

    layout = new QGridLayout();

    vlayout = new QVBoxLayout(this);

    hlayout[0] = new QHBoxLayout();
    hlayout[1] = new QHBoxLayout();
    hlayout[2] = new QHBoxLayout();

    quit = new QPushButton(tr("Fermer"));

    layout->addWidget(multiplication[0], 1, 0);
    layout->addWidget(correction[0][0], 1, 1);
    layout->addWidget(correction[1][0], 1, 2);

    layout->addWidget(multiplication[1], 2, 0);
    layout->addWidget(correction[0][1], 2, 1);
    layout->addWidget(correction[1][1], 2, 2);


    layout->addWidget(multiplication[2], 3, 0);
    layout->addWidget(correction[0][2], 3, 1);
    layout->addWidget(correction[1][2], 3, 2);


    layout->addWidget(multiplication[3], 4, 0);
    layout->addWidget(correction[0][3], 4, 1);
    layout->addWidget(correction[1][3], 4, 2);


    layout->addWidget(multiplication[4], 5, 0);
    layout->addWidget(correction[0][4], 5, 1);
    layout->addWidget(correction[1][4], 5, 2);


    layout->addWidget(multiplication[5], 6, 0);
    layout->addWidget(correction[0][5], 6, 1);
    layout->addWidget(correction[1][5], 6, 2);


    layout->addWidget(multiplication[6], 7, 0);
    layout->addWidget(correction[0][6], 7, 1);
    layout->addWidget(correction[1][6], 7, 2);


    layout->addWidget(multiplication[7], 8, 0);
    layout->addWidget(correction[0][7], 8, 1);
    layout->addWidget(correction[1][7], 8, 2);


    layout->addWidget(multiplication[8], 9, 0);
    layout->addWidget(correction[0][8], 9, 1);
    layout->addWidget(correction[1][8], 9, 2);


    layout->addWidget(multiplication[9], 10, 0);
    layout->addWidget(correction[0][9], 10, 1);
    layout->addWidget(correction[1][9], 10, 2);


    hlayout[0]->setAlignment(Qt::AlignCenter);
    hlayout[0]->addWidget(texte);

    hlayout[1]->setAlignment(Qt::AlignCenter);
    hlayout[1]->addWidget(total);
    hlayout[1]->addWidget(pngTotal);

    hlayout[2]->setAlignment(Qt::AlignRight);
    hlayout[2]->addWidget(quit);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

}
void Fen_correction::setWindowLayout(int tabOrder[])
{
    for(int i = 0; i < 10; i++)
    {
        multiplication[i] = new QLabel();
        multiplication[i]->setText(QString::number(tabOrder[i])+ " x " + QString::number(tab[i]) + " = "+QString::number(reponse[i]));
    }

    texte = new QLabel(tr("<h3><strong>Voici la correction : </strong></h3>"));
    if(note >= 7)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: rgb(0, 200, 0);\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        if(note == 10)
            pngTotal->setPixmap(QPixmap("excellent.png"));
        else
            pngTotal->setPixmap(QPixmap("bien.png"));
    }
    else if(note <= 2)
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: rgb(128, 0, 0);\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal = new QLabel();
        pngTotal->setPixmap(QPixmap("mauvais.png"));
    }
    else
    {
        total = new QLabel(tr("Tu as eu <strong><span style=\"color: orange;\">")+QString::number(note)+tr("/10</span></strong>"));
        pngTotal =  new QLabel();
        pngTotal->setPixmap(QPixmap("moyen.png"));
    }

    layout = new QGridLayout();

    vlayout = new QVBoxLayout(this);

    hlayout[0] = new QHBoxLayout();
    hlayout[1] = new QHBoxLayout();
    hlayout[2] = new QHBoxLayout();

    quit = new QPushButton("Fermer");

    layout->addWidget(multiplication[0], 1, 0);
    layout->addWidget(correction[0][0], 1, 1);
    layout->addWidget(correction[1][0], 1, 2);

    layout->addWidget(multiplication[1], 2, 0);
    layout->addWidget(correction[0][1], 2, 1);
    layout->addWidget(correction[1][1], 2, 2);


    layout->addWidget(multiplication[2], 3, 0);
    layout->addWidget(correction[0][2], 3, 1);
    layout->addWidget(correction[1][2], 3, 2);


    layout->addWidget(multiplication[3], 4, 0);
    layout->addWidget(correction[0][3], 4, 1);
    layout->addWidget(correction[1][3], 4, 2);


    layout->addWidget(multiplication[4], 5, 0);
    layout->addWidget(correction[0][4], 5, 1);
    layout->addWidget(correction[1][4], 5, 2);


    layout->addWidget(multiplication[5], 6, 0);
    layout->addWidget(correction[0][5], 6, 1);
    layout->addWidget(correction[1][5], 6, 2);


    layout->addWidget(multiplication[6], 7, 0);
    layout->addWidget(correction[0][6], 7, 1);
    layout->addWidget(correction[1][6], 7, 2);


    layout->addWidget(multiplication[7], 8, 0);
    layout->addWidget(correction[0][7], 8, 1);
    layout->addWidget(correction[1][7], 8, 2);


    layout->addWidget(multiplication[8], 9, 0);
    layout->addWidget(correction[0][8], 9, 1);
    layout->addWidget(correction[1][8], 9, 2);


    layout->addWidget(multiplication[9], 10, 0);
    layout->addWidget(correction[0][9], 10, 1);
    layout->addWidget(correction[1][9], 10, 2);


    hlayout[0]->setAlignment(Qt::AlignCenter);
    hlayout[0]->addWidget(texte);

    hlayout[1]->setAlignment(Qt::AlignCenter);
    hlayout[1]->addWidget(total);
    hlayout[1]->addWidget(pngTotal);

    hlayout[2]->setAlignment(Qt::AlignRight);
    hlayout[2]->addWidget(quit);

    vlayout->addLayout(hlayout[0]);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout[1]);
    vlayout->addLayout(hlayout[2]);

}

void Fen_correction::openMessageBox(RecordState state, const int lastRecordTime)
{
    timeTab[0] = timeElapsed;
    timeTab[2] = lastRecordTime;

    TimeRecordMgr::returnTime(timeTab);

    if(state == RECORD)
    {
        QMessageBox::information(this, tr("Temps de r�ponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br /><strong>C'est un nouveau record ! F�licitation !</strong><br />L'ancien record �tait de ")+QString::number(timeTab[3])+tr(" minute(s) et ")+QString::number(timeTab[2])+tr(" secondes."));
        correct->saveTime();
    }
    else if(state == UNVALIDRECORD)
        QMessageBox::information(this, tr("Temps de r�ponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes.<br />Ce temps ne compte pas pour les records car tu as fait des fautes !"));
    else if(state == NORECORD)
        QMessageBox::information(this, tr("Temps de r�ponses"), tr("Tu as mis ")+QString::number(timeTab[1])+tr(" minute(s) et ")+QString::number(timeTab[0])+tr(" secondes."));
}

Fen_correction::~Fen_correction()
{
    delete total;
    delete layout;
    delete vlayout;
    delete quit;
    delete texte;
    delete pngTotal;
    delete correct;

    total = 0;
    layout = 0;
    vlayout = 0;
    quit = 0;
    texte = 0;
    pngTotal = 0;
    correct = 0;

    for (int i = 0; i < 10; i++)
    {
        delete multiplication[i];
        multiplication[i] = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        delete hlayout[i];
        hlayout[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        for ( int j = 0; j < 10; j++)
        {
            delete correction[i][j];
            correction[i][j] = 0;
        }
    }
}
