/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

class ContactPrintThemeEditorutil
{
public:
    ContactPrintThemeEditorutil();
    Q_REQUIRED_RESULT QString defaultContact() const;
    Q_REQUIRED_RESULT QString defaultTemplate() const;
};

