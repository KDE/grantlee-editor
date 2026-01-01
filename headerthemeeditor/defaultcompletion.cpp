/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "defaultcompletion.h"
using namespace Qt::Literals::StringLiterals;

QStringList DefaultCompletion::defaultCompetion()
{
    // TODO add to highlighter
    QStringList lst;
    lst << u"<div>"_s << u"class=\"fancy header\""_s << QStringLiteral("header.absoluteThemePath") << u"header.subjecti18n"_s << u"header.subject"_s
        << QStringLiteral("header.replyToi18n") << QStringLiteral("header.replyTo") << u"header.replyToStr"_s << u"header.toi18n"_s
        << QStringLiteral("header.to") << QStringLiteral("header.toStr") << u"header.toExpandable"_s << u"header.cci18n"_s << QStringLiteral("header.cc")
        << QStringLiteral("header.ccStr") << u"header.ccExpandable"_s << u"header.bcci18n"_s << QStringLiteral("header.bcc") << QStringLiteral("header.bccStr")
        << u"header.bccExpandable"_s << u"header.fromi18n"_s << QStringLiteral("header.from") << QStringLiteral("header.fromStr") << u"header.spamHTML"_s
        << u"header.spamstatusi18n"_s << QStringLiteral("header.datei18n") << u"header.dateshort"_s << u"header.date"_s << QStringLiteral("header.datelong")
        << QStringLiteral("header.datefancylong") << u"header.datefancyshort"_s << u"header.datelocalelong"_s << QStringLiteral("header.useragent")
        << u"header.xmailer"_s << u"header.resentFrom"_s << QStringLiteral("header.resentFromi18n") << u"header.organization"_s << u"header.vcardname"_s
        << QStringLiteral("header.activecolordark") << u"header.fontcolor"_s << u"header.linkcolor"_s << QStringLiteral("header.photowidth")
        << u"header.photoheight"_s << u"header.applicationDir"_s << QStringLiteral("header.subjectDir") << u"header.photourl"_s << u"header.isprinting"_s
        << QStringLiteral("header.vcardi18n") << QStringLiteral("header.resentTo") << u"header.resentToi18n"_s << u"header.trashaction"_s
        << QStringLiteral("header.replyaction") << u"header.replyallaction"_s << u"header.forwardaction"_s << QStringLiteral("header.newmessageaction")
        << u"header.printmessageaction"_s << u"header.printpreviewmessageaction"_s << QStringLiteral("header.collectionname") << u"header.replyToNameOnly"_s
        << u"header.ccNameOnly"_s << QStringLiteral("header.bccNameOnly") << u"header.toNameOnly"_s << u"header.senderi18n"_s << QStringLiteral("header.sender")
        << QStringLiteral("header.listidi18n") << u"header.listid"_s;

    return lst;
}

QStringList DefaultCompletion::defaultOptions()
{
    const QStringList lst = {u"showlink"_s, u"nameonly"_s, QStringLiteral("safe"), QStringLiteral("expandable")};
    return lst;
}
