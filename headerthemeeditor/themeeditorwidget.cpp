/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themeeditorwidget.h"
#include "defaultcompletion.h"

ThemeEditorWidget::ThemeEditorWidget(QWidget *parent)
    : GrantleeThemeEditor::EditorWidget(parent)
{
    createCompleterList();
}

ThemeEditorWidget::~ThemeEditorWidget() = default;

void ThemeEditorWidget::createCompleterList(const QStringList &extraCompletion)
{
    QStringList listWord;
    listWord << DefaultCompletion::defaultCompetion();
    listWord << DefaultCompletion::defaultOptions();
    listWord << extraCompletion;
    GrantleeThemeEditor::EditorWidget::createCompleterList(listWord);
}
