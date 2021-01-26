/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef EDITORPAGE_H
#define EDITORPAGE_H

#include "grantleethemeeditor/editorpage.h"

class ThemeTemplateWidget;
class EditorWidget;
class QSplitter;
namespace GrantleeThemeEditor
{
class EditorWidget;
class PreviewWidget;
}

class EditorPage : public GrantleeThemeEditor::EditorPage
{
    Q_OBJECT
public:
    explicit EditorPage(GrantleeThemeEditor::EditorPage::PageType type, const QString &projectDirectory, QWidget *parent = nullptr);
    ~EditorPage();

    GrantleeThemeEditor::PreviewWidget *preview() const;

private:
    ThemeTemplateWidget *mThemeTemplate = nullptr;
    QSplitter *mMainSplitter = nullptr;
    QSplitter *mWidgetSplitter = nullptr;
};

#endif // EDITORPAGE_H
