/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themeeditorutil.h"

ThemeEditorUtil::ThemeEditorUtil() = default;

QString ThemeEditorUtil::defaultMail() const
{
    const QString mail = QStringLiteral(
        "From: montel@example.com\n"
        "To: kde@example.com\n"
        "Sender: montel@example.com\n"
        "MIME-Version: 1.0\n"
        "Date: 28 Apr 2013 23:58:21 -0000\n"
        "Subject: Test message\n"
        "Content-Type: text/plain\n"
        "X-Length: 0\n"
        "X-UID: 6161\n"
        "\n"
        "Hello this is a test mail\n");
    return mail;
}
