/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "grantleethemeeditor/editorwidget.h"

class ThemeEditorWidget : public GrantleeThemeEditor::EditorWidget
{
    Q_OBJECT
public:
    explicit ThemeEditorWidget(QWidget *parent = nullptr);
    ~ThemeEditorWidget() override;

public Q_SLOTS:
    void createCompleterList(const QStringList &extraCompletion = QStringList()) override;
};
