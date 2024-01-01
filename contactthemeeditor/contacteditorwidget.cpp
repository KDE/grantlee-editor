/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditorwidget.h"
#include "defaultcompletion.h"

ContactEditorWidget::ContactEditorWidget(QWidget *parent)
    : GrantleeThemeEditor::EditorWidget(parent)
{
    createCompleterList();
}

ContactEditorWidget::~ContactEditorWidget() = default;

void ContactEditorWidget::createCompleterList(const QStringList &extraCompletion)
{
    const QStringList listWord = QStringList() << DefaultCompletion::defaultCompetion() << DefaultCompletion::defaultOptions() << extraCompletion;
    GrantleeThemeEditor::EditorWidget::createCompleterList(listWord);
}

#include "moc_contacteditorwidget.cpp"
