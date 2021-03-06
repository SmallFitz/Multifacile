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

#include "spinBox.h"

SpinBox::SpinBox(QWidget *parent) : QLineEdit(parent), numero(0)
{
    QIntValidator tempValidator(0, 100, this);
    this->setValidator(&tempValidator);
}
void SpinBox::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
    QKeyEvent key = *event;
    if(key.key() == Qt::Key_Enter || key.key() == Qt::Key_Return)
        emit enterKeyPressed(numero);
    else
        return;
}
void SpinBox::setNumero(const int num){ numero = num; }
