/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    QApplication app(argc, argv);
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
                         i18n("Copyright © 2013-%1 contactthemeeditor authors", QStringLiteral("2022")));
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

    auto mw = new ContactEditorMainWindow();
    mw->show();
    const int ret = app.exec();
    return ret;
}
