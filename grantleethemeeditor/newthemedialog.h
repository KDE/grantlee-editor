/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QString themeName() const;
    [[nodiscard]] QString directory() const;

private:
    void slotUpdateOkButton();
    void readConfig();
    NewThemeDialogPrivate *const d;
};
}
