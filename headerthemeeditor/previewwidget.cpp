/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "previewwidget.h"
#include "themeeditorutil.h"
#include <MessageViewer/Viewer>
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/GrantleeHeaderTestStyle>

#include <QPushButton>
#include <KLocalizedString>
#include <KConfigGroup>

#include <QVBoxLayout>
#include <KSharedConfig>

PreviewWidget::PreviewWidget(const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::PreviewWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    mViewer = new MessageViewer::Viewer(this);
    mGrantleeHeaderStyle = new MessageViewer::GrantleeHeaderTestStyle;
    mGrantleeHeaderStyle->setAbsolutePath(projectDirectory);
    //Default
    mGrantleeHeaderStyle->setMainFilename(QStringLiteral("header.html"));
#if 0 //TODO_PORT_PLUGIN
    mViewer->setHeaderStyleAndStrategy(mGrantleeHeaderStyle,
                                       MessageViewer::HeaderStrategy::create(QString()));
#endif
    lay->addWidget(mViewer);
    QPushButton *update = new QPushButton(i18n("Update view"));
    connect(update, &QPushButton::clicked, this, &PreviewWidget::needUpdateViewer);
    lay->addWidget(update);
}

PreviewWidget::~PreviewWidget()
{
    delete mGrantleeHeaderStyle;
}

void PreviewWidget::slotExtraHeaderDisplayChanged(const QStringList &headers)
{
    mGrantleeHeaderStyle->setExtraDisplayHeaders(headers);
    updateViewer();
}

void PreviewWidget::slotMainFileNameChanged(const QString &filename)
{
    mGrantleeHeaderStyle->setMainFilename(filename);
    updateViewer();
}

void PreviewWidget::loadConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    ThemeEditorUtil themeutil;
    if (config->hasGroup(QStringLiteral("Global"))) {
        KConfigGroup group = config->group(QStringLiteral("Global"));
        mDefaultEmail = group.readEntry("defaultEmail", themeutil.defaultMail()).toLatin1();
    } else {
        mDefaultEmail = themeutil.defaultMail().toLatin1();
    }
    updateViewer();
}

void PreviewWidget::updateViewer()
{
    KMime::Message *msg = new KMime::Message;
    msg->setContent(mDefaultEmail);
    msg->parse();
    mViewer->setPrinting(mPrinting);
    mViewer->setMessage(KMime::Message::Ptr(msg));
}

void PreviewWidget::createScreenShot(const QStringList &fileList)
{
    mViewer->saveMainFrameScreenshotInFile(fileList.at(0));
}

void PreviewWidget::setThemePath(const QString &projectDirectory, const QString &mainPageFileName)
{
    mGrantleeHeaderStyle->setAbsolutePath(projectDirectory);
    mGrantleeHeaderStyle->setMainFilename(mainPageFileName);
    updateViewer();
}
