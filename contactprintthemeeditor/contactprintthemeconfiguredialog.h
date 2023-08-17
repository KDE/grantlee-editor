/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

namespace GrantleeThemeEditor
{
class ConfigureWidget;
}

namespace Akonadi
{
class AkonadiContactEditor;
}

namespace TextCustomEditor
{
class PlainTextEditorWidget;
}
class ContactPrintThemeConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContactPrintThemeConfigureDialog(QWidget *parent = nullptr);
    ~ContactPrintThemeConfigureDialog() override;

    void readConfig();
    void writeConfig();

private:
    void slotOkClicked();
    void slotDefaultClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    TextCustomEditor::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    Akonadi::AkonadiContactEditor *mDefaultContact = nullptr;
};
