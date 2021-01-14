/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "previewwidget.h"

using namespace GrantleeThemeEditor;

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
{
}

PreviewWidget::~PreviewWidget()
{
}

void PreviewWidget::updateViewer()
{
}

void PreviewWidget::setPrinting(bool printMode)
{
    if (mPrinting != printMode) {
        mPrinting = printMode;
        updateViewer();
    }
}

bool PreviewWidget::printing() const
{
    return mPrinting;
}

void PreviewWidget::loadConfig()
{
}

void PreviewWidget::createScreenShot(const QStringList &lstFileName)
{
    Q_UNUSED(lstFileName)
}

void PreviewWidget::setThemePath(const QString &projectDirectory, const QString &mainPageFileName)
{
    Q_UNUSED(projectDirectory)
    Q_UNUSED(mainPageFileName)
}

void PreviewWidget::slotMainFileNameChanged(const QString &)
{
}

void PreviewWidget::slotExtraHeaderDisplayChanged(const QStringList &headers)
{
    Q_UNUSED(headers)
}
