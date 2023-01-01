/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor_export.h"
#include <QDialog>

namespace GrantleeThemeEditor
{
class NewThemeDialogPrivate;
class GRANTLEETHEMEEDITOR_EXPORT NewThemeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewThemeDialog(QWidget *parent = nullptr);
    ~NewThemeDialog() override;

    Q_REQUIRED_RESULT QString themeName() const;
    Q_REQUIRED_RESULT QString directory() const;

private:
    void slotUpdateOkButton();
    void readConfig();
    NewThemeDialogPrivate *const d;
};
}
