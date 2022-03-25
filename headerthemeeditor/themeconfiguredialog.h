/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}
namespace GrantleeThemeEditor
{
class ConfigureWidget;
}

class ThemeConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThemeConfigureDialog(QWidget *parent = nullptr);
    ~ThemeConfigureDialog() override;

    void readConfig();
    void writeConfig();

private:
    void slotOkClicked();
    void slotDefaultClicked();
    GrantleeThemeEditor::ConfigureWidget *mConfigureWidget = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDefaultEmail = nullptr;
};
