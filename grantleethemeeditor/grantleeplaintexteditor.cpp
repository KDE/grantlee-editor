/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "grantleeplaintexteditor.h"
using namespace Qt::Literals::StringLiterals;

#include "grantleethemeeditor_debug.h"

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <KSyntaxHighlighting/Theme>

#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <TextCustomEditor/TextEditorCompleter>

using namespace GrantleeThemeEditor;

GrantleePlainTextEditor::GrantleePlainTextEditor(QWidget *parent)
    : TextCustomEditor::PlainTextEditor(parent)
{
    const KSyntaxHighlighting::Definition def = mRepo.definitionForName(u"HTML"_s);
    if (!def.isValid()) {
        qCWarning(GRANTLEETHEMEEDITOR_LOG) << "Invalid definition name";
    }

    auto hl = new KSyntaxHighlighting::SyntaxHighlighter(document());
    hl->setTheme((palette().color(QPalette::Base).lightness() < 128) ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                     : mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    hl->setDefinition(def);
    setSpellCheckingSupport(false);
    initCompleter();
}

GrantleePlainTextEditor::~GrantleePlainTextEditor() = default;

void GrantleePlainTextEditor::initCompleter()
{
    mTextEditorCompleter = new TextCustomEditor::TextEditorCompleter(this, this);
}

void GrantleePlainTextEditor::createCompleterList(const QStringList &extraCompletion)
{
    mTextEditorCompleter->setCompleterStringList(extraCompletion);
}

void GrantleePlainTextEditor::keyPressEvent(QKeyEvent *e)
{
    if (mTextEditorCompleter->completer()->popup()->isVisible()) {
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }
    TextCustomEditor::PlainTextEditor::keyPressEvent(e);
    mTextEditorCompleter->completeText();
}

#include "moc_grantleeplaintexteditor.cpp"
