/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONTACTTEMPLATEWIDGET_H
#define CONTACTTEMPLATEWIDGET_H

#include <QWidget>
#include <PimCommon/TemplateListWidget>

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
    ~ContactTemplateWidget();

Q_SIGNALS:
    void insertTemplate(const QString &);

private:
    ContactTemplateListWidget *mListTemplate = nullptr;
};

#endif // CONTACTTEMPLATEWIDGET_H
