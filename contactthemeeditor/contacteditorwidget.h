/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "grantleethemeeditor/editorwidget.h"

class ContactEditorWidget : public GrantleeThemeEditor::EditorWidget
{
    Q_OBJECT
public:
    explicit ContactEditorWidget(QWidget *parent = nullptr);
    ~ContactEditorWidget() override;

public Q_SLOTS:
    void createCompleterList(const QStringList &extraCompletion = QStringList()) override;
};
