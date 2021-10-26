/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor_export.h"
#include <KPIMTextEdit/PlainTextEditorWidget>

namespace GrantleeThemeEditor
{
class GRANTLEETHEMEEDITOR_EXPORT EditorWidget : public KPIMTextEdit::PlainTextEditorWidget
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = nullptr);
    ~EditorWidget() override;

    void insertFile(const QString &filename);

    virtual void createCompleterList(const QStringList &extraCompletion = QStringList());

    Q_REQUIRED_RESULT QString toPlainText() const;
    void setPlainText(const QString &str);
    void clear();
};
}

