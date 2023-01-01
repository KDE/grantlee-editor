/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor_export.h"
#include <QTabWidget>
namespace GrantleeThemeEditor
{
class GRANTLEETHEMEEDITOR_EXPORT ThemeEditorTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit ThemeEditorTabWidget(QWidget *parent = nullptr);
    ~ThemeEditorTabWidget() override;

public Q_SLOTS:
    void slotMainFileNameChanged(const QString &fileName);

private:
    void slotTabContextMenuRequest(const QPoint &pos);
};
}
