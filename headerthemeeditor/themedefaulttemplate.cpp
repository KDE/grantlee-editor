/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themedefaulttemplate.h"

#include <KLocalizedString>

QList<PimCommon::defaultTemplate> ThemeDefaultTemplate::defaultTemplates()
{
    QList<PimCommon::defaultTemplate> lst;
    PimCommon::defaultTemplate tmp;
    tmp.name = i18n("Subject");
    tmp.text = QStringLiteral(
        "{% if header.subject %}\n"
        "   {{ header.subject|safe }}\n"
        "{% endif %}\n");
    lst << tmp;

    tmp.name = i18n("From");
    tmp.text = QStringLiteral(
        "{% if header.from %}\n"
        "   {{ header.from|safe }}\n"
        "{% endif %}\n");
    lst << tmp;

    tmp.name = i18n("To");
    tmp.text = QStringLiteral(
        "{% if header.to %}\n"
        "   {{ header.to|safe }}\n"
        "{% endif %}\n");
    lst << tmp;

    tmp.name = i18n("Cc");
    tmp.text = QStringLiteral(
        "{% if header.cc %}\n"
        "   {{ header.cc|safe }}\n"
        "{% endif %}\n");
    lst << tmp;

    return lst;
}
