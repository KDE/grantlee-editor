/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONTACTPRINTTHEMECONFIGUREDIALOG_H
#define CONTACTPRINTTHEMECONFIGUREDIALOG_H

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
class ContactPrintThemeConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContactPrintThemeConfigureDialog(QWidget *parent = nullptr);
    ~ContactPrintThemeConfigureDialog();

    void readConfig();
    void writeConfig();

private:
    void slotOkClicked();
    void slotDefaultClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    Akonadi::AkonadiContactEditor *mDefaultContact = nullptr;
};

#endif
