/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRANTLEEPLAINTEXTEDITOR_H
#define GRANTLEEPLAINTEXTEDITOR_H

#include <KPIMTextEdit/PlainTextEditor>
#include <KSyntaxHighlighting/Repository>

namespace KPIMTextEdit {
class TextEditorCompleter;
}
namespace GrantleeThemeEditor {
class GrantleePlainTextEditor : public KPIMTextEdit::PlainTextEditor
{
    Q_OBJECT
public:
    explicit GrantleePlainTextEditor(QWidget *parent = nullptr);
    ~GrantleePlainTextEditor() override;

    void createCompleterList(const QStringList &extraCompletion);

protected:
    void keyPressEvent(QKeyEvent *e) override;

protected:
    KPIMTextEdit::TextEditorCompleter *mTextEditorCompleter = nullptr;
private:
    void initCompleter();
    KSyntaxHighlighting::Repository mRepo;
};
}

#endif // GRANTLEEPLAINTEXTEDITOR_H
