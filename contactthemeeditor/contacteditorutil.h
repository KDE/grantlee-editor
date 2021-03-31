/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QString>

class ContactEditorUtil
{
public:
    ContactEditorUtil();
    Q_REQUIRED_RESULT QString defaultContact() const;
};

