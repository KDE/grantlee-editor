/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "defaultcompletion.h"
using namespace Qt::Literals::StringLiterals;

QStringList DefaultCompletion::defaultCompetion()
{
    // TODO add to highlighter
    QStringList lst;

    lst << u"<div>"_s << u"contact.birthday"_s << QStringLiteral("contact.birthdayi18n") << QStringLiteral("contact.phoneNumbers") << u"phoneNumber.smsLink"_s
        << u"phoneNumber.type"_s << QStringLiteral("contact.emailsi18n") << u"contact.websitei18n"_s << u"contact.website"_s
        << QStringLiteral("contact.blogUrl") << u"contact.addresses"_s << u"contact.imAddressi18n"_s << QStringLiteral("contact.imAddress")
        << u"contact.Professioni18n"_s << u"contact.profession"_s << QStringLiteral("contact.hasqrcode") << u"contact.note"_s << u"contact.notei18n"_s
        << QStringLiteral("contact.addressBookName") << u"contact.addressBookNamei18n"_s << u"customField.title"_s << QStringLiteral("contact.customFields")
        << u"customField.value"_s << u"contact.customFieldsUrl"_s << QStringLiteral("contact.anniversaryi18n") << u"contact.anniversary"_s
        << u"contact.spousei18n"_s << QStringLiteral("contact.spouse") << u"contact.assistant"_s << u"contact.assistanti18n"_s
        << QStringLiteral("contact.manager") << u"contact.manageri18n"_s << u"contact.officei18n"_s << QStringLiteral("contact.office")
        << u"contact.department"_s << u"contact.departmenti18n"_s << QStringLiteral("contact.imAddresses") << u"phoneNumber.numberLink"_s
        << u"contact.imAddresses"_s << QStringLiteral("imAddress.type") << u"address.formattedAddressLink"_s << u"address.formattedAddressIcon"_s
        << QStringLiteral("member.emailLink") << u"member.name"_s << u"field.title"_s << QStringLiteral("field.value") << QStringLiteral("imAddress.imIcon");
    return lst;
}

QStringList DefaultCompletion::defaultOptions()
{
    const QStringList lst{u"Safe"_s};
    return lst;
}
