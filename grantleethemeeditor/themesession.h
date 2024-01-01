/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "grantleethemeeditor_export.h"
#include <QString>
#include <QStringList>

namespace GrantleeThemeEditor
{
class GRANTLEETHEMEEDITOR_EXPORT ThemeSession
{
public:
    ThemeSession(const QString &projectDirectory, const QString &themeTypeName);
    ~ThemeSession();
    [[nodiscard]] bool loadSession(const QString &session);
    void writeSession(const QString &directory = QString());

    [[nodiscard]] QString projectDirectory() const;

    void addExtraPage(const QString &filename);
    [[nodiscard]] QStringList extraPages() const;

    void setMainPageFileName(const QString &filename);
    [[nodiscard]] QString mainPageFileName() const;

private:
    QString mProjectDirectory;
    QString mMainPageFileName;
    QStringList mExtraPage;
    const QString mThemeTypeName;
    const int mVersion = 1;
};
}
