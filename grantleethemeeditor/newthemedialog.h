/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef NEWTHEMEDIALOG_H
#define NEWTHEMEDIALOG_H

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
    ~NewThemeDialog();

    Q_REQUIRED_RESULT QString themeName() const;
    Q_REQUIRED_RESULT QString directory() const;

private:
    void slotUpdateOkButton();
    void readConfig();
    NewThemeDialogPrivate *const d;
};
}
#endif // NEWTHEMEDIALOG_H
