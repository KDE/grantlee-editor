/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/TemplateListWidget>
#include <QWidget>

class ThemeTemplateListWidget : public PimCommon::TemplateListWidget
{
    Q_OBJECT
public:
    explicit ThemeTemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    ~ThemeTemplateListWidget() override;

    Q_REQUIRED_RESULT QVector<PimCommon::defaultTemplate> defaultTemplates() override;
};

class ThemeTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeTemplateWidget(const QString &title, QWidget *parent = nullptr);
    ~ThemeTemplateWidget() override;

Q_SIGNALS:
    void insertTemplate(const QString &);

private:
    ThemeTemplateListWidget *mListTemplate = nullptr;
};
