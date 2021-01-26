/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "defaultcompletion.h"

QStringList DefaultCompletion::defaultCompetion()
{
    // TODO add to highlighter
    QStringList lst;
    lst << QStringLiteral("<div>") << QStringLiteral("class=\"fancy header\"") << QStringLiteral("header.absoluteThemePath")
        << QStringLiteral("header.subjecti18n") << QStringLiteral("header.subject") << QStringLiteral("header.replyToi18n") << QStringLiteral("header.replyTo")
        << QStringLiteral("header.replyToStr") << QStringLiteral("header.toi18n") << QStringLiteral("header.to") << QStringLiteral("header.toStr")
        << QStringLiteral("header.toExpandable") << QStringLiteral("header.cci18n") << QStringLiteral("header.cc") << QStringLiteral("header.ccStr")
        << QStringLiteral("header.ccExpandable") << QStringLiteral("header.bcci18n") << QStringLiteral("header.bcc") << QStringLiteral("header.bccStr")
        << QStringLiteral("header.bccExpandable") << QStringLiteral("header.fromi18n") << QStringLiteral("header.from") << QStringLiteral("header.fromStr")
        << QStringLiteral("header.spamHTML") << QStringLiteral("header.spamstatusi18n") << QStringLiteral("header.datei18n")
        << QStringLiteral("header.dateshort") << QStringLiteral("header.date") << QStringLiteral("header.datelong") << QStringLiteral("header.datefancylong")
        << QStringLiteral("header.datefancyshort") << QStringLiteral("header.datelocalelong") << QStringLiteral("header.useragent")
        << QStringLiteral("header.xmailer") << QStringLiteral("header.resentFrom") << QStringLiteral("header.resentFromi18n")
        << QStringLiteral("header.organization") << QStringLiteral("header.vcardname") << QStringLiteral("header.activecolordark")
        << QStringLiteral("header.fontcolor") << QStringLiteral("header.linkcolor") << QStringLiteral("header.photowidth")
        << QStringLiteral("header.photoheight") << QStringLiteral("header.applicationDir") << QStringLiteral("header.subjectDir")
        << QStringLiteral("header.photourl") << QStringLiteral("header.isprinting") << QStringLiteral("header.vcardi18n") << QStringLiteral("header.resentTo")
        << QStringLiteral("header.resentToi18n") << QStringLiteral("header.trashaction") << QStringLiteral("header.replyaction")
        << QStringLiteral("header.replyallaction") << QStringLiteral("header.forwardaction") << QStringLiteral("header.newmessageaction")
        << QStringLiteral("header.printmessageaction") << QStringLiteral("header.printpreviewmessageaction") << QStringLiteral("header.collectionname")
        << QStringLiteral("header.replyToNameOnly") << QStringLiteral("header.ccNameOnly") << QStringLiteral("header.bccNameOnly")
        << QStringLiteral("header.toNameOnly") << QStringLiteral("header.senderi18n") << QStringLiteral("header.sender") << QStringLiteral("header.listidi18n")
        << QStringLiteral("header.listid");

    return lst;
}

QStringList DefaultCompletion::defaultOptions()
{
    const QStringList lst = {QStringLiteral("showlink"), QStringLiteral("nameonly"), QStringLiteral("safe"), QStringLiteral("expandable")};
    return lst;
}
