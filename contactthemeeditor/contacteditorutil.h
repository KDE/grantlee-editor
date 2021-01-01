/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONTACTEDITORUTIL_H
#define CONTACTEDITORUTIL_H

#include <QString>

class ContactEditorUtil
{
public:
    ContactEditorUtil();
    Q_REQUIRED_RESULT QString defaultContact() const;
};

#endif
