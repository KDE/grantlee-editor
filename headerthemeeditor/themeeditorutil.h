/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef THEMEEDITORUTIL_H
#define THEMEEDITORUTIL_H

#include <QString>

class ThemeEditorUtil
{
public:
    ThemeEditorUtil();
    Q_REQUIRED_RESULT QString defaultMail() const;
};

#endif // THEMEEDITORUTIL_H
