/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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

#include "contactprintthemepreview.h"
#include "contactprintthemeeditorutil.h"
#include <KSharedConfig>
#include <KConfigGroup>
#include <QHBoxLayout>
#include <QWebEngineView>
#include <KContacts/VCardConverter>
#include <kaddressbookgrantlee/grantleeprint.h>
#include "contactprintthemeeditor_debug.h"

ContactPrintThemePreview::ContactPrintThemePreview(const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::PreviewWidget(parent)
    , mThemePath(projectDirectory)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);
    mViewer = new QWebEngineView(this);
    mViewer->setContextMenuPolicy(Qt::NoContextMenu);
    hbox->addWidget(mViewer);
    loadConfig();
}

ContactPrintThemePreview::~ContactPrintThemePreview()
{
}

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
    Q_UNUSED(fileName);
    qCWarning(CONTACTPRINTTHEMEEDITOR_LOG) << "Create screenshot not implemented yet";
}

void ContactPrintThemePreview::setThemePath(const QString &projectDirectory, const QString &mainPageFileName)
{
    Q_UNUSED(mainPageFileName);
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
