/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

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
class ContactConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContactConfigureDialog(QWidget *parent = nullptr);
    ~ContactConfigureDialog() override;

    void readConfig();
    void writeConfig();

private:
    void slotDefaultClicked();
    void slotOkClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    TextCustomEditor::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    Akonadi::AkonadiContactEditor *mDefaultContact = nullptr;
};
