/*
   Copyright (C) 2013-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef CONTACTCONFIGURATIONDIALOG_H
#define CONTACTCONFIGURATIONDIALOG_H

#include <QDialog>

namespace GrantleeThemeEditor {
class ConfigureWidget;
}

namespace Akonadi {
class AkonadiContactEditor;
}

namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
class ContactConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContactConfigureDialog(QWidget *parent = nullptr);
    ~ContactConfigureDialog();

    void readConfig();
    void writeConfig();

private:
    void slotDefaultClicked();
    void slotOkClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    Akonadi::AkonadiContactEditor *mDefaultContact = nullptr;
};

#endif // CONTACTCONFIGURATIONDIALOG_H
