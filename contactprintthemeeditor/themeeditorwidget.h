/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef THEMEEDITORWIDGET_H
#define THEMEEDITORWIDGET_H
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

#endif // THEMEEDITORWIDGET_H
