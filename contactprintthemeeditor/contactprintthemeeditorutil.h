/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef THEMEEDITORUTIL_H
#define THEMEEDITORUTIL_H

#include <QString>

class ContactPrintThemeEditorutil
{
public:
    ContactPrintThemeEditorutil();
    Q_REQUIRED_RESULT QString defaultContact() const;
    Q_REQUIRED_RESULT QString defaultTemplate() const;
};

#endif // THEMEEDITORUTIL_H
