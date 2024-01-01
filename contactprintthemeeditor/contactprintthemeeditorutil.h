/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

class ContactPrintThemeEditorutil
{
public:
    ContactPrintThemeEditorutil();
    [[nodiscard]] QString defaultContact() const;
    [[nodiscard]] QString defaultTemplate() const;
};
