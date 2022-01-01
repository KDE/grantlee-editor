/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeeditor-version.h"
#include "themeeditormainwindow.h"
#include <KAboutData>
#include <KCrash>
#include <KDBusService>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    QApplication app(argc, argv);
    app.setDesktopFileName(QStringLiteral("org.kde.contactprintthemeeditor"));
    KLocalizedString::setApplicationDomain("contactprintthemeeditor");
    KAboutData aboutData(QStringLiteral("contactprintthemeeditor"),
                         i18n("Contact Print Theme Editor"),
                         QStringLiteral(GRANTLEEEDITOR_VERSION),
                         i18n("Contact Print Theme Editor"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2015-%1 contactprintthemeeditor authors", QStringLiteral("2022")));
    aboutData.addAuthor(i18n("Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kaddressbook")));
    aboutData.setOrganizationDomain(QByteArray("kde.org"));
    aboutData.setProductName(QByteArray("contactprintthemeeditor"));

    KAboutData::setApplicationData(aboutData);
    KCrash::initialize();

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    KDBusService service;

    auto mw = new ThemeEditorMainWindow;
    mw->show();
    const int ret = app.exec();
    return ret;
}
