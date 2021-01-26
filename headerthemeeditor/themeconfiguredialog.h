/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef THEMECONFIGUREDIALOG_H
#define THEMECONFIGUREDIALOG_H

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
