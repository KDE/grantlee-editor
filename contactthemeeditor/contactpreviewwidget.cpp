/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactpreviewwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "contacteditorutil.h"

#include <KContacts/VCardConverter>

#include <Akonadi/ContactGroupViewer>
#include <Akonadi/ContactViewer>
#include <Akonadi/GrantleeContactFormatter>
#include <Akonadi/GrantleeContactGroupFormatter>
#include <Akonadi/Item>
#include <KLocalizedString>

#include <KConfigGroup>
#include <KSharedConfig>

#include <QHBoxLayout>
#include <QPainter>
#include <QTabWidget>

ContactPreviewWidget::ContactPreviewWidget(const QString &projectDirectory, QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QHBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    mTabWidget = new QTabWidget;

    mContactViewer = new Akonadi::ContactViewer;
    mTabWidget->addTab(mContactViewer, i18n("Contact"));

    mGroupViewer = new Akonadi::ContactGroupViewer;
    mTabWidget->addTab(mGroupViewer, i18n("Group"));

    lay->addWidget(mTabWidget);

    mFormatter = new KAddressBookGrantlee::GrantleeContactFormatter;

    mContactViewer->setContactFormatter(mFormatter);

    mGroupFormatter = new KAddressBookGrantlee::GrantleeContactGroupFormatter;

    mGroupViewer->setContactGroupFormatter(mGroupFormatter);

    loadConfig();
    if (!projectDirectory.isEmpty()) {
        mGroupFormatter->setAbsoluteThemePath(projectDirectory);
        mFormatter->setAbsoluteThemePath(projectDirectory);
    }
}

ContactPreviewWidget::~ContactPreviewWidget()
{
    delete mFormatter;
    delete mGroupFormatter;
}

void ContactPreviewWidget::updateViewer()
{
    mContactViewer->setRawContact(mContact);
    // mGroupViewer->setContactGroup();
    // TODO
}

void ContactPreviewWidget::createScreenShot(const QStringList &fileName)
{
    for (int i = 0; i < fileName.count(); ++i) {
        if (i == 0) {
            QImage image(mContactViewer->size(), QImage::Format_ARGB32_Premultiplied);
            image.fill(Qt::transparent);

            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::TextAntialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            mContactViewer->render(&painter);
            painter.end();
            image.save(fileName.at(i));
        } else if (i == 1) {
            QImage image(mContactViewer->size(), QImage::Format_ARGB32_Premultiplied);
            image.fill(Qt::transparent);

            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::TextAntialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            mGroupViewer->render(&painter);
            painter.end();
            image.save(fileName.at(i));
        }
    }
}

void ContactPreviewWidget::loadConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    ContactEditorUtil contactUtil;
    if (config->hasGroup(u"Global"_s)) {
        KConfigGroup group = config->group(u"Global"_s);
        const QString defaultContact = group.readEntry("defaultContact", contactUtil.defaultContact());
        if (!defaultContact.isEmpty()) {
            KContacts::VCardConverter converter;
            mContact = converter.parseVCard(defaultContact.toUtf8());
        } else {
            mContact = KContacts::Addressee();
        }
    } else {
        if (!contactUtil.defaultContact().isEmpty()) {
            KContacts::VCardConverter converter;
            mContact = converter.parseVCard(contactUtil.defaultContact().toUtf8());
        } else {
            mContact = KContacts::Addressee();
        }
    }
}

void ContactPreviewWidget::setThemePath(const QString &projectDirectory)
{
    mGroupFormatter->setAbsoluteThemePath(projectDirectory);
    mFormatter->setAbsoluteThemePath(projectDirectory);
}

#include "moc_contactpreviewwidget.cpp"
