/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themetemplatewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "themedefaulttemplate.h"

#include <KLocalizedString>

#include <QLabel>
#include <QVBoxLayout>

ThemeTemplateListWidget::ThemeTemplateListWidget(const QString &configName, QWidget *parent)
    : PimCommon::TemplateListWidget(configName, parent)
{
    loadTemplates();
}

ThemeTemplateListWidget::~ThemeTemplateListWidget() = default;

QList<PimCommon::defaultTemplate> ThemeTemplateListWidget::defaultTemplates()
{
    return ThemeDefaultTemplate::defaultTemplates();
}

ThemeTemplateWidget::ThemeTemplateWidget(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QVBoxLayout(this);
    auto lab = new QLabel(title);
    lay->addWidget(lab);
    mListTemplate = new ThemeTemplateListWidget(u"headerthemeeditorrc"_s);
    mListTemplate->setWhatsThis(i18n("You can drag and drop element on editor to import template"));
    connect(mListTemplate, &ThemeTemplateListWidget::insertTemplate, this, &ThemeTemplateWidget::insertTemplate);
    lay->addWidget(mListTemplate);
}

ThemeTemplateWidget::~ThemeTemplateWidget() = default;

#include "moc_themetemplatewidget.cpp"
