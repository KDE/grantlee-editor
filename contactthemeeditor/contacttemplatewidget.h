/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <PimCommon/TemplateListWidget>
#include <QWidget>

class ContactTemplateListWidget : public PimCommon::TemplateListWidget
{
    Q_OBJECT
public:
    explicit ContactTemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    ~ContactTemplateListWidget() override;

    Q_REQUIRED_RESULT QVector<PimCommon::defaultTemplate> defaultTemplates() override;
};

class ContactTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContactTemplateWidget(const QString &title, QWidget *parent = nullptr);
    ~ContactTemplateWidget() override;

Q_SIGNALS:
    void insertTemplate(const QString &);

private:
    ContactTemplateListWidget *mListTemplate = nullptr;
};

