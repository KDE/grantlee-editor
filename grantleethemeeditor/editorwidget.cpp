/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "editorwidget.h"
#include "grantleeplaintexteditor.h"

using namespace GrantleeThemeEditor;

EditorWidget::EditorWidget(QWidget *parent)
    : KPIMTextEdit::PlainTextEditorWidget(new GrantleeThemeEditor::GrantleePlainTextEditor(), parent)
{
}

EditorWidget::~EditorWidget()
{
}

void EditorWidget::insertFile(const QString &filename)
{
    if (!filename.isEmpty()) {
        QFile file(filename);

        if (file.open(QIODevice::ReadOnly)) {
            const QByteArray data = file.readAll();
            const QString str = QString::fromUtf8(data);
            editor()->insertPlainText(str);
        }
    }
}

void EditorWidget::createCompleterList(const QStringList &extraCompletion)
{
    (static_cast<GrantleeThemeEditor::GrantleePlainTextEditor *>(editor()))->createCompleterList(extraCompletion);
}

QString EditorWidget::toPlainText() const
{
    return editor()->toPlainText();
}

void EditorWidget::setPlainText(const QString &str)
{
    editor()->setPlainText(str);
}

void EditorWidget::clear()
{
    editor()->clear();
}
