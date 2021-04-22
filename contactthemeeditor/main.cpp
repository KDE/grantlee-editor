/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditormainwindow.h"
#include "grantleeeditor-version.h"
#include <KAboutData>
#include <KCrash>
#include <KDBusService>
#include <KLocalizedString>
#include <kcoreaddons_version.h>
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <Kdelibs4ConfigMigrator>
#endif
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    app.setDesktopFileName(QStringLiteral("org.kde.contactthemeeditor"));

    KCrash::initialize();
#if KCOREADDONS_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Kdelibs4ConfigMigrator migrate(QStringLiteral("contactthemeeditor"));
    migrate.setConfigFiles(QStringList() << QStringLiteral("contactthemeeditorrc"));
    migrate.setUiFiles(QStringList() << QStringLiteral("contactthemeeditorui.rc"));
    migrate.migrate();
#endif
    KLocalizedString::setApplicationDomain("contactthemeeditor");
    KAboutData aboutData(QStringLiteral("contactthemeeditor"),
                         i18n("Contact Theme Editor"),
                         QStringLiteral(GRANTLEEEDITOR_VERSION),
                         i18n("Contact Theme Editor"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2013-2021 contactthemeeditor authors"));
    aboutData.addAuthor(i18n("Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kaddressbook")));
    aboutData.setOrganizationDomain(QByteArray("kde.org"));
    aboutData.setProductName(QByteArray("contactthemeeditor"));

    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    KDBusService service;

    ContactEditorMainWindow *mw = new ContactEditorMainWindow();
    mw->show();
    const int ret = app.exec();
    return ret;
}
