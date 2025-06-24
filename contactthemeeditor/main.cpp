/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditormainwindow.h"
using namespace Qt::Literals::StringLiterals;

#include "grantleeeditor-version.h"
#include <KAboutData>
#include <KCrash>
#include <KDBusService>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setDesktopFileName(u"org.kde.contactthemeeditor"_s);

    KCrash::initialize();
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("contactthemeeditor"));
    KAboutData aboutData(u"contactthemeeditor"_s,
                         i18n("Contact Theme Editor"),
                         QStringLiteral(GRANTLEEEDITOR_VERSION),
                         i18n("Contact Theme Editor"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2013-%1 contactthemeeditor authors", u"2025"_s));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);
    QApplication::setWindowIcon(QIcon::fromTheme(u"kaddressbook"_s));
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
