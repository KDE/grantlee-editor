/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacteditorutil.h"

ContactEditorUtil::ContactEditorUtil()
{
}

QString ContactEditorUtil::defaultContact() const
{
    const QString contact = QStringLiteral("BEGIN:VCARD\n"
                                           "ADR;TYPE=home:;;10 street Eiffel Tower\n;Paris;;75016;France\n"
                                           "EMAIL:test@kde.org\n"
                                           "FN:Test\n"
                                           "N:Test;;;;\n"
                                           "ORG:kde\n"
                                           "TEL;TYPE=HOME:+33 12345678\n"
                                           "UID:{851e0b81-8f95-40d2-a6a6-a9dbee2be12d}\n"
                                           "URL:www.kde.org\n"
                                           "VERSION:3.0\n"
                                           "END:VCARD");
    return contact;
}
