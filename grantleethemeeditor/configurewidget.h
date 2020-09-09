/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIGUREWIDGET_H
#define CONFIGUREWIDGET_H

#include "grantleethemeeditor_export.h"
#include <QWidget>

namespace Ui {
class ConfigureWidget;
}

namespace GrantleeThemeEditor {
class GRANTLEETHEMEEDITOR_EXPORT ConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigureWidget(QWidget *parent = nullptr);
    ~ConfigureWidget();

    void readConfig();
    void writeConfig();
    void setDefault();

private:
    Ui::ConfigureWidget *const ui;
};
}

#endif // CONFIGUREWIDGET_H
