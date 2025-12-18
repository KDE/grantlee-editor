/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "previewwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "themeeditorutil.h"
#include <MessageViewer/GrantleeHeaderTestStyle>
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/Viewer>

#include <KConfigGroup>
#include <KLocalizedString>
#include <QPushButton>

#include <KSharedConfig>
#include <QVBoxLayout>

PreviewWidget::PreviewWidget(const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::PreviewWidget(parent)
{
    auto lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    mViewer = new MessageViewer::Viewer(this);
    mGrantleeHeaderStyle = new MessageViewer::GrantleeHeaderTestStyle;
    mGrantleeHeaderStyle->setAbsolutePath(projectDirectory);
    // Default
    mGrantleeHeaderStyle->setMainFilename(u"header.html"_s);
#if 0 // TODO_PORT_PLUGIN
    mViewer->setHeaderStyleAndStrategy(mGrantleeHeaderStyle,
                                       MessageViewer::HeaderStrategy::create(QString()));
#endif
    lay->addWidget(mViewer);
    auto update = new QPushButton(i18nc("@action:button", "Update view"));
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
    if (config->hasGroup(u"Global"_s)) {
        KConfigGroup group = config->group(u"Global"_s);
        mDefaultEmail = group.readEntry("defaultEmail", themeutil.defaultMail()).toLatin1();
    } else {
        mDefaultEmail = themeutil.defaultMail().toLatin1();
    }
    updateViewer();
}

void PreviewWidget::updateViewer()
{
    auto msg = new KMime::Message;
    msg->setContent(mDefaultEmail);
    msg->parse();
    mViewer->setPrinting(mPrinting);
    mViewer->setMessage(std::shared_ptr<KMime::Message>(msg));
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

#include "moc_previewwidget.cpp"
