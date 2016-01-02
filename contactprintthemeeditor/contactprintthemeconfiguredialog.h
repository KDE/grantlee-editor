/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CONTACTPRINTTHEMECONFIGUREDIALOG_H
#define CONTACTPRINTTHEMECONFIGUREDIALOG_H

#include <QDialog>

namespace GrantleeThemeEditor
{
class ConfigureWidget;
}

namespace Akonadi
{
class ContactEditor;
}

namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}
class ContactPrintThemeConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContactPrintThemeConfigureDialog(QWidget *parent = Q_NULLPTR);
    ~ContactPrintThemeConfigureDialog();

    void readConfig();
    void writeConfig();

private Q_SLOTS:
    void slotOkClicked();
    void slotDefaultClicked();

private:
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultTemplate;
    Akonadi::ContactEditor *mDefaultContact;
};

#endif
