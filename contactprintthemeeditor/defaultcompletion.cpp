/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "defaultcompletion.h"
using namespace Qt::Literals::StringLiterals;

QStringList DefaultCompletion::defaultCompetion()
{
    // TODO add to highlighter
    QStringList lst;
    lst << u"<div>"_s << u"contact.birthdayi18n"_s << QStringLiteral("contact.anniversaryi18n") << u"contact.emailsi18n"_s << u"contact.websitei18n"_s
        << QStringLiteral("contact.blogUrli18n") << u"contact.addressBookNamei18n"_s << u"contact.notei18n"_s << QStringLiteral("contact.departmenti18n")
        << u"contact.Professioni18n"_s << u"contact.officei18n"_s << QStringLiteral("contact.manageri18n") << u"contact.assistanti18n"_s
        << u"contact.spousei18n"_s << QStringLiteral("contact.imAddressi18n") << u"contact.latitudei18n"_s << u"contact.longitudei18n"_s
        << QStringLiteral("contact.organizationi18n") << u"contact.titlei18n"_s << u"contact.nextcontacti18n"_s << QStringLiteral("contact.name")
        << u"contact.realName"_s << u"contact.formattedName"_s << QStringLiteral("contact.prefix") << u"contact.givenName"_s << u"contact.additionalName"_s
        << QStringLiteral("contact.familyName") << u"contact.suffix"_s << u"contact.nickName"_s << QStringLiteral("contact.emails")
        << QStringLiteral("contact.organization") << u"contact.note"_s << u"contact.webSite"_s << QStringLiteral("contact.title")
        << QStringLiteral("contact.preferredEmail") << u"contact.role"_s << u"contact.birthday"_s << QStringLiteral("contact.department")
        << QStringLiteral("contact.addresses") << u"contact.phones"_s << u"contact.addressBookName"_s << QStringLiteral("contact.instantManging")
        << u"contact.geo"_s << u"contact.photo"_s << QStringLiteral("contact.logo") << QStringLiteral("contact.crypto") << u"contact.anniversary"_s
        << u"contact.profession"_s << QStringLiteral("contact.office") << u"contact.manager"_s << u"contact.assistant"_s << QStringLiteral("contact.spouse")
        << QStringLiteral("contact.languages");

    return lst;
}

QStringList DefaultCompletion::defaultOptions()
{
    QStringList lst;
    lst << u"Safe"_s;
    return lst;
}
