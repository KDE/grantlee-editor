/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "previewwidget.h"
#include "contactpreviewwidget.h"

#include <QHBoxLayout>

PreviewWidget::PreviewWidget(const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::PreviewWidget(parent)
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    mPreview = new ContactPreviewWidget(projectDirectory);
    lay->addWidget(mPreview);
}

PreviewWidget::~PreviewWidget()
{
}

void PreviewWidget::loadConfig()
{
    mPreview->loadConfig();
    updateViewer();
}

void PreviewWidget::updateViewer()
{
    mPreview->updateViewer();
}

void PreviewWidget::createScreenShot(const QStringList &fileList)
{
    mPreview->createScreenShot(fileList);
}

void PreviewWidget::setThemePath(const QString &projectDirectory, const QString &mainPageFileName)
{
    Q_UNUSED(mainPageFileName)
    mPreview->setThemePath(projectDirectory);
    updateViewer();
}
