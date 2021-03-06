/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditorwidget.h"
#include "defaultcompletion.h"

ContactEditorWidget::ContactEditorWidget(QWidget *parent)
    : GrantleeThemeEditor::EditorWidget(parent)
{
    createCompleterList();
}

ContactEditorWidget::~ContactEditorWidget()
{
}

void ContactEditorWidget::createCompleterList(const QStringList &extraCompletion)
{
    const QStringList listWord = QStringList() << DefaultCompletion::defaultCompetion() << DefaultCompletion::defaultOptions() << extraCompletion;
    GrantleeThemeEditor::EditorWidget::createCompleterList(listWord);
}
