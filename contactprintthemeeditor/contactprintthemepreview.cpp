/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactprintthemepreview.h"
#include "contactprintthemeeditor_debug.h"
#include "contactprintthemeeditorutil.h"
#include <Akonadi/GrantleePrint>
#include <KConfigGroup>
#include <KContacts/VCardConverter>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QWebEngineView>

ContactPrintThemePreview::ContactPrintThemePreview(const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::PreviewWidget(parent)
    , mThemePath(projectDirectory)
{
    auto hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);
    mViewer = new QWebEngineView(this);
    mViewer->setContextMenuPolicy(Qt::NoContextMenu);
    hbox->addWidget(mViewer);
    loadConfig();
}

ContactPrintThemePreview::~ContactPrintThemePreview() = default;

void ContactPrintThemePreview::updateViewer()
{
    KContacts::AddresseeList lst;
    lst << mContact;
    KAddressBookGrantlee::GrantleePrint grantleePrint(mThemePath);
    grantleePrint.setApplicationDomain("kaddressbook");
    const QString html = grantleePrint.contactsToHtml(lst);
    mViewer->setHtml(html);
}

void ContactPrintThemePreview::createScreenShot(const QStringList &fileName)
{
    Q_UNUSED(fileName)
    qCWarning(CONTACTPRINTTHEMEEDITOR_LOG) << "Create screenshot not implemented yet";
}

void ContactPrintThemePreview::setThemePath(const QString &projectDirectory, const QString &mainPageFileName)
{
    Q_UNUSED(mainPageFileName)
    mThemePath = projectDirectory;
}

void ContactPrintThemePreview::loadConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    if (config->hasGroup(QStringLiteral("Global"))) {
        KConfigGroup group = config->group(QStringLiteral("Global"));
        ContactPrintThemeEditorutil contactEditorUtil;
        const QString defaultContact = group.readEntry("defaultContact", contactEditorUtil.defaultContact());
        if (!defaultContact.isEmpty()) {
            KContacts::VCardConverter converter;
            mContact = converter.parseVCard(defaultContact.toUtf8());
        } else {
            mContact = KContacts::Addressee();
        }
    } else {
        ContactPrintThemeEditorutil contactEditorUtil;
        if (!contactEditorUtil.defaultContact().isEmpty()) {
            KContacts::VCardConverter converter;
            mContact = converter.parseVCard(contactEditorUtil.defaultContact().toUtf8());
        } else {
            mContact = KContacts::Addressee();
        }
    }
}
