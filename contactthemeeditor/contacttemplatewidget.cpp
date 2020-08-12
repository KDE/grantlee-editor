/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacttemplatewidget.h"
#include "contactdefaulttemplate.h"

#include <KLocalizedString>

#include <QVBoxLayout>
#include <QLabel>

ContactTemplateListWidget::ContactTemplateListWidget(const QString &configName, QWidget *parent)
    : PimCommon::TemplateListWidget(configName, parent)
{
    loadTemplates();
}

ContactTemplateListWidget::~ContactTemplateListWidget()
{
}

QVector<PimCommon::defaultTemplate> ContactTemplateListWidget::defaultTemplates()
{
    return ContactDefaultTemplate::contactTemplates();
}

ContactTemplateWidget::ContactTemplateWidget(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    QLabel *lab = new QLabel(title);
    lay->addWidget(lab);
    mListTemplate = new ContactTemplateListWidget(QStringLiteral("contactthemeeditorrc"));
    mListTemplate->setWhatsThis(i18n("You can drag and drop element on editor to import template"));
    connect(mListTemplate, &ContactTemplateListWidget::insertTemplate, this, &ContactTemplateWidget::insertTemplate);
    lay->addWidget(mListTemplate);
}

ContactTemplateWidget::~ContactTemplateWidget()
{
}
