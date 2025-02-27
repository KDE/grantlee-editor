/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

namespace TextCustomEditor
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
    TextCustomEditor::PlainTextEditorWidget *mDefaultTemplate = nullptr;
    TextCustomEditor::PlainTextEditorWidget *mDefaultEmail = nullptr;
};
