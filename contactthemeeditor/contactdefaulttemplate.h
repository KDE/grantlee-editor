/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONTACTDEFAULTTEMPLATE_H
#define CONTACTDEFAULTTEMPLATE_H

#include <PimCommon/TemplateListWidget>

namespace ContactDefaultTemplate
{
Q_REQUIRED_RESULT QVector<PimCommon::defaultTemplate> contactTemplates();
}

#endif // CONTACTDEFAULTTEMPLATE_H
