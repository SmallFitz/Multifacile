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

#include "AstuceWindow.h"

AstuceWindow::AstuceWindow(const int table) : QMessageBox()
{
    astucesInit();
    this->addButton(QMessageBox::Ok);
    this->setIcon(QMessageBox::Information);
    if(astuces.contains(table))
        this->setText(astuces[table]);
    else
        this->setText(tr("Il n'y a pas encore d'astuces pour cette table."));
}
void AstuceWindow::astucesInit()
{
    astuces[1] = tr("Pour la table de 1, le r�sultat sera toujours �gal au nombre que multiplie 1.<br />Exemple :<br /><strong>1 x <span style=\"text-decoration: underline;\">7</span> = <span style=\"text-decoration: underline;\">7</span></strong>");
    astuces[2] = tr("Pour la table de 2, le r�sultat est toujours un nombre paire et les r�sultats vont de 2 en 2.<br />Exmple :<br /><strong>2 x 1 = <span style=\"text-decoration: underline;\">2</span><br />2 x 2 = <span style=\"text-decoration: underline;\">4</span></strong>");
    astuces[5] = tr("Pour la table de 5, le r�sultat termine soit par 0 soit par 5. Cela d�pend du nombre que multiplie 5 : si le nombre est paire, le r�sultat terminera par 0 sinon, si le nombre est impaire, le r�sultat terminera par 5. En plus, les r�sultats vont de 5 en 5 !<br />Exemple :<br /><strong>5 x 2 = <span style=\"text-decoration: underline;\">10</span><br />5 x 3 = <span style=\"text-decoration: underline;\">15</span></strong>");
    astuces[10] = tr("Pour la table de 10, on rajoute un 0 au chiffre que multiplie 10.<br />Exemple :<br /><strong><span style=\"text-decoration: underline;\">5</span> x 10 = <span style=\"text-decoration: underline;\">50</span></strong>");
}
