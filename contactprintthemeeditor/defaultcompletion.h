/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef DEFAULTCOMPLETION_H
#define DEFAULTCOMPLETION_H

#include <QStringList>

namespace DefaultCompletion {
Q_REQUIRED_RESULT QStringList defaultCompetion();
Q_REQUIRED_RESULT QStringList defaultOptions();
}

#endif // DEFAULTCOMPLETION_H
