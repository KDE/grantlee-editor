/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themesession.h"
using namespace Qt::Literals::StringLiterals;

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
    if (config.hasGroup(u"Global"_s)) {
        KConfigGroup global = config.group(u"Global"_s);
        const int version = global.readEntry(u"version"_s, 0);
        if (version >= mVersion) {
            if (global.readEntry(u"themeTypeName"_s) != mThemeTypeName) {
                KMessageBox::error(nullptr,
                                   i18n("Error during theme loading"),
                                   i18n("You are trying to load a theme which cannot be read by this application"));
                return false;
            }
        }
        mProjectDirectory = global.readEntry("path", QString());
        mMainPageFileName = global.readEntry(u"mainPageName"_s, QString());
        mExtraPage = global.readEntry(u"extraPagesName"_s, QStringList());
        return true;
    } else {
        qCDebug(GRANTLEETHEMEEDITOR_LOG) << u"\"%1\" is not a session file"_s.arg(session);
        return false;
    }
}

void ThemeSession::writeSession(const QString &directory)
{
    QString themeDirectory = (directory.isEmpty() ? mProjectDirectory : directory);
    KConfig config(themeDirectory + QLatin1StringView("/theme.themerc"));
    KConfigGroup global = config.group(u"Global"_s);
    global.writeEntry(u"path"_s, themeDirectory);
    global.writeEntry(u"mainPageName"_s, mMainPageFileName);
    global.writeEntry(u"extraPagesName"_s, mExtraPage);
    global.writeEntry(u"themeTypeName"_s, mThemeTypeName);
    global.writeEntry(u"version"_s, mVersion);
    config.sync();
}
