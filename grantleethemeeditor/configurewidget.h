/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grantleethemeeditor_export.h"
#include <QWidget>

namespace Ui
{
class ConfigureWidget;
}

namespace GrantleeThemeEditor
{
class GRANTLEETHEMEEDITOR_EXPORT ConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigureWidget(QWidget *parent = nullptr);
    ~ConfigureWidget() override;

    void readConfig();
    void writeConfig();
    void setDefault();

private:
    Ui::ConfigureWidget *const ui;
};
}

