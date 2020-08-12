/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef MANAGETHEMES_H
#define MANAGETHEMES_H

#include "grantleethemeeditor_export.h"
#include <QDialog>

namespace GrantleeThemeEditor {
class ManageThemesPrivate;
class GRANTLEETHEMEEDITOR_EXPORT ManageThemes : public QDialog
{
    Q_OBJECT
public:
    explicit ManageThemes(const QString &relativeThemePath, QWidget *parent = nullptr);
    ~ManageThemes();

private:
    void slotItemSelectionChanged();
    void slotDeleteTheme();

private:
    void readConfig();
    void writeConfig();
    void initialize();
    ManageThemesPrivate *const d;
};
}
#endif // MANAGETHEMES_H
