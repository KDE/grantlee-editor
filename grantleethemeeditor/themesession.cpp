/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themesession.h"
#include "grantleethemeeditor_debug.h"
#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>

using namespace GrantleeThemeEditor;

ThemeSession::ThemeSession(const QString &projectDirectory, const QString &themeTypeName)
    : mProjectDirectory(projectDirectory)
    , mThemeTypeName(themeTypeName)
{
}

ThemeSession::~ThemeSession() = default;

QString ThemeSession::projectDirectory() const
{
    return mProjectDirectory;
}

void ThemeSession::addExtraPage(const QString &filename)
{
    mExtraPage.append(filename);
}

QStringList ThemeSession::extraPages() const
{
    return mExtraPage;
}

void ThemeSession::setMainPageFileName(const QString &filename)
{
    mMainPageFileName = filename;
}

QString ThemeSession::mainPageFileName() const
{
    return mMainPageFileName;
}

bool ThemeSession::loadSession(const QString &session)
{
    KConfig config(session);
    if (config.hasGroup(QStringLiteral("Global"))) {
        KConfigGroup global = config.group(QStringLiteral("Global"));
        const int version = global.readEntry(QStringLiteral("version"), 0);
        if (version >= mVersion) {
            if (global.readEntry(QStringLiteral("themeTypeName")) != mThemeTypeName) {
                KMessageBox::error(nullptr,
                                   i18n("Error during theme loading"),
                                   i18n("You are trying to load a theme which cannot be read by this application"));
                return false;
            }
        }
        mProjectDirectory = global.readEntry("path", QString());
        mMainPageFileName = global.readEntry(QStringLiteral("mainPageName"), QString());
        mExtraPage = global.readEntry(QStringLiteral("extraPagesName"), QStringList());
        return true;
    } else {
        qCDebug(GRANTLEETHEMEEDITOR_LOG) << QStringLiteral("\"%1\" is not a session file").arg(session);
        return false;
    }
}

void ThemeSession::writeSession(const QString &directory)
{
    QString themeDirectory = (directory.isEmpty() ? mProjectDirectory : directory);
    KConfig config(themeDirectory + QLatin1StringView("/theme.themerc"));
    KConfigGroup global = config.group(QStringLiteral("Global"));
    global.writeEntry(QStringLiteral("path"), themeDirectory);
    global.writeEntry(QStringLiteral("mainPageName"), mMainPageFileName);
    global.writeEntry(QStringLiteral("extraPagesName"), mExtraPage);
    global.writeEntry(QStringLiteral("themeTypeName"), mThemeTypeName);
    global.writeEntry(QStringLiteral("version"), mVersion);
    config.sync();
}
