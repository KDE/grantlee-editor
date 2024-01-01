/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KSyntaxHighlighting/Repository>
#include <TextCustomEditor/PlainTextEditor>

namespace TextCustomEditor
{
class TextEditorCompleter;
}
namespace GrantleeThemeEditor
{
class GrantleePlainTextEditor : public TextCustomEditor::PlainTextEditor
{
    Q_OBJECT
public:
    explicit GrantleePlainTextEditor(QWidget *parent = nullptr);
    ~GrantleePlainTextEditor() override;

    void createCompleterList(const QStringList &extraCompletion);

protected:
    void keyPressEvent(QKeyEvent *e) override;

protected:
    TextCustomEditor::TextEditorCompleter *mTextEditorCompleter = nullptr;

private:
    void initCompleter();
    KSyntaxHighlighting::Repository mRepo;
};
}
