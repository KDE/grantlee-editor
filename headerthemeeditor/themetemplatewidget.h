/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef THEMETEMPLATEWIDGET_H
#define THEMETEMPLATEWIDGET_H

#include <QWidget>
#include "PimCommon/TemplateListWidget"

class ThemeTemplateListWidget : public PimCommon::TemplateListWidget
{
    Q_OBJECT
public:
    explicit ThemeTemplateListWidget(const QString &configName, QWidget *parent = nullptr);
    ~ThemeTemplateListWidget();

    QVector<PimCommon::defaultTemplate> defaultTemplates() override;
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
