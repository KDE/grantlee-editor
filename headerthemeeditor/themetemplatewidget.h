/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef THEMETEMPLATEWIDGET_H
#define THEMETEMPLATEWIDGET_H

#include <QWidget>
#include <PimCommon/TemplateListWidget>

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
    ~ThemeTemplateWidget();

Q_SIGNALS:
    void insertTemplate(const QString &);

private:
    ThemeTemplateListWidget *mListTemplate = nullptr;
};

#endif // THEMETEMPLATEWIDGET_H
