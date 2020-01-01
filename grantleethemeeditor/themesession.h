/*
   Copyright (C) 2013-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef THEMESESSION_H
#define THEMESESSION_H
#include "grantleethemeeditor_export.h"
#include <QString>
#include <QStringList>

namespace GrantleeThemeEditor {
class GRANTLEETHEMEEDITOR_EXPORT ThemeSession
{
public:
    ThemeSession(const QString &projectDirectory, const QString &themeTypeName);
    ~ThemeSession();
    Q_REQUIRED_RESULT bool loadSession(const QString &session);
    void writeSession(const QString &directory = QString());

    Q_REQUIRED_RESULT QString projectDirectory() const;

    void addExtraPage(const QString &filename);
    Q_REQUIRED_RESULT QStringList extraPages() const;

    void setMainPageFileName(const QString &filename);
    Q_REQUIRED_RESULT QString mainPageFileName() const;

private:
    QString mProjectDirectory;
    QString mMainPageFileName;
    QStringList mExtraPage;
    QString mThemeTypeName;
    int mVersion;
};
}

#endif // THEMESESSION_H
