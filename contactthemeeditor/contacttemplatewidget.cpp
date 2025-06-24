/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contacttemplatewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "contactdefaulttemplate.h"

#include <KLocalizedString>

#include <QLabel>
#include <QVBoxLayout>

ContactTemplateListWidget::ContactTemplateListWidget(const QString &configName, QWidget *parent)
    : PimCommon::TemplateListWidget(configName, parent)
{
    loadTemplates();
}

ContactTemplateListWidget::~ContactTemplateListWidget() = default;

QList<PimCommon::defaultTemplate> ContactTemplateListWidget::defaultTemplates()
{
    return ContactDefaultTemplate::contactTemplates();
}

ContactTemplateWidget::ContactTemplateWidget(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QVBoxLayout(this);
    auto lab = new QLabel(title);
    lay->addWidget(lab);
    mListTemplate = new ContactTemplateListWidget(u"contactthemeeditorrc"_s);
    mListTemplate->setWhatsThis(i18n("You can drag and drop element on editor to import template"));
    connect(mListTemplate, &ContactTemplateListWidget::insertTemplate, this, &ContactTemplateWidget::insertTemplate);
    lay->addWidget(mListTemplate);
}

ContactTemplateWidget::~ContactTemplateWidget() = default;

#include "moc_contacttemplatewidget.cpp"
