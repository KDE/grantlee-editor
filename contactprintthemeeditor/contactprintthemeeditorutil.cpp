/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactprintthemeeditorutil.h"

ContactPrintThemeEditorutil::ContactPrintThemeEditorutil() = default;

QString ContactPrintThemeEditorutil::defaultContact() const
{
    const QString contact = QStringLiteral(
        "BEGIN:VCARD\n"
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

QString ContactPrintThemeEditorutil::defaultTemplate() const
{
    const QString templateStr = QStringLiteral(
        "<html>\n"
        "{% if contacts %}\n"
        "{% for contact in contacts %}\n"
        "<h1>{{ contact.realName|safe }}</h1>\n"
        "<p>{{ contact.emails|safe }}</p>\n"
        "<p>{{ contact.note|safe }}</p>\n"
        "<br>\n"
        "<br>\n"
        "{% endfor %}\n"
        "{% endif %}\n"
        "</html>");

    return templateStr;
}
