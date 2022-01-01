/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor/editorpage.h"

class ContactTemplateWidget;
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
    ~EditorPage() override;

    GrantleeThemeEditor::PreviewWidget *preview() const;

private:
    ContactTemplateWidget *mContactTemplate = nullptr;
    QSplitter *mMainSplitter = nullptr;
    QSplitter *mWidgetSplitter = nullptr;
};

