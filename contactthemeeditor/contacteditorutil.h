/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QString>

class ContactEditorUtil
{
public:
    ContactEditorUtil();
    [[nodiscard]] QString defaultContact() const;
};
