/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "grantleethemeeditor/previewwidget.h"
class ContactPreviewWidget;
class PreviewWidget : public GrantleeThemeEditor::PreviewWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(const QString &projectDirectory, QWidget *parent = nullptr);
    ~PreviewWidget() override;

    void createScreenShot(const QStringList &fileList) override;
    void loadConfig() override;
    void setThemePath(const QString &projectDirectory, const QString &mainPageFileName) override;
    void updateViewer() override;

private:
    ContactPreviewWidget *mPreview = nullptr;
};
