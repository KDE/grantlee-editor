/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grantleethemeeditor/editorpage.h"

class ThemeTemplateWidget;
class EditorWidget;
class QSplitter;
class ContactPrintThemePreview;
namespace GrantleeThemeEditor
{
class EditorWidget;
}

class EditorPage : public GrantleeThemeEditor::EditorPage
{
    Q_OBJECT
public:
    explicit EditorPage(GrantleeThemeEditor::EditorPage::PageType type, const QString &projectDirectory, QWidget *parent = nullptr);
    ~EditorPage() override;

    ContactPrintThemePreview *preview() const;

private:
    ContactPrintThemePreview *mPreview = nullptr;
    ThemeTemplateWidget *mThemeTemplate = nullptr;
    QSplitter *mMainSplitter = nullptr;
    QSplitter *mWidgetSplitter = nullptr;
};
