/*
   Copyright (C) 2013-2020 Laurent Montel <montel@kde.org>

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
#ifndef THEMECONFIGUREDIALOG_H
#define THEMECONFIGUREDIALOG_H

#include <QDialog>

namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
namespace GrantleeThemeEditor {
class ConfigureWidget;
}

class ThemeConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThemeConfigureDialog(QWidget *parent = nullptr);
    ~ThemeConfigureDialog();

    void readConfig();
    void writeConfig();

private:
    void slotOkClicked();
    void slotDefaultClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultEmail = nullptr;
};

#endif // THEMECONFIGUREDIALOG_H
