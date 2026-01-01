/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactprintthemeconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "contactprintthemeeditorutil.h"
#include <TextCustomEditor/PlainTextEditorWidget>

#include "configurewidget.h"

#include <Akonadi/ContactEditor>

#include <KContacts/VCardConverter>

#include <KConfig>
#include <KLocalizedString>

#include <KConfigGroup>

#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

ContactPrintThemeConfigureDialog::ContactPrintThemeConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure"));

    auto tab = new QTabWidget;

    auto w = new QWidget;
    auto lay = new QVBoxLayout();
    w->setLayout(lay);

    mConfigureWidget = new GrantleeThemeEditor::ConfigureWidget;
    lay->addWidget(mConfigureWidget);

    auto lab = new QLabel(i18nc("@label:textbox", "Default contact:"));
    lay->addWidget(lab);

    mDefaultContact = new Akonadi::AkonadiContactEditor(Akonadi::AkonadiContactEditor::CreateMode, Akonadi::AkonadiContactEditor::VCardMode);
    lay->addWidget(mDefaultContact);

    tab->addTab(w, i18n("General"));

    mDefaultTemplate = new TextCustomEditor::PlainTextEditorWidget;
    tab->addTab(mDefaultTemplate, i18n("Default Template"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tab);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ContactPrintThemeConfigureDialog::reject);
    mainLayout->addWidget(buttonBox);
    okButton->setFocus();

    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &ContactPrintThemeConfigureDialog::slotDefaultClicked);
    connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &ContactPrintThemeConfigureDialog::slotOkClicked);
    readConfig();
}

ContactPrintThemeConfigureDialog::~ContactPrintThemeConfigureDialog()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    KConfigGroup group = config->group(u"ContactPrintThemeConfigureDialog"_s);
    group.writeEntry("Size", size());
}

void ContactPrintThemeConfigureDialog::slotDefaultClicked()
{
    mConfigureWidget->setDefault();

    ContactPrintThemeEditorutil contactUtil;
    if (!contactUtil.defaultContact().isEmpty()) {
        KContacts::VCardConverter converter;
        KContacts::Addressee addr = converter.parseVCard(contactUtil.defaultContact().toUtf8());
        mDefaultContact->setContactTemplate(addr);
    } else {
        mDefaultContact->setContactTemplate(KContacts::Addressee());
    }
    mDefaultTemplate->setPlainText(contactUtil.defaultTemplate());
}

void ContactPrintThemeConfigureDialog::slotOkClicked()
{
    writeConfig();
    accept();
}

void ContactPrintThemeConfigureDialog::readConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    ContactPrintThemeEditorutil contactUtil;
    if (config->hasGroup(u"Global"_s)) {
        KConfigGroup group = config->group(u"Global"_s);

        const QString defaultContact = group.readEntry("defaultContact", contactUtil.defaultContact());
        if (!defaultContact.isEmpty()) {
            KContacts::VCardConverter converter;
            KContacts::Addressee addr = converter.parseVCard(defaultContact.toUtf8());
            mDefaultContact->setContactTemplate(addr);
        } else {
            mDefaultContact->setContactTemplate(KContacts::Addressee());
        }
        mDefaultTemplate->setPlainText(group.readEntry("defaultTemplate", contactUtil.defaultTemplate()));
    } else {
        if (!contactUtil.defaultContact().isEmpty()) {
            KContacts::VCardConverter converter;
            KContacts::Addressee addr = converter.parseVCard(contactUtil.defaultContact().toUtf8());
            mDefaultContact->setContactTemplate(addr);
        } else {
            mDefaultContact->setContactTemplate(KContacts::Addressee());
        }
        mDefaultTemplate->setPlainText(contactUtil.defaultTemplate());
    }

    mConfigureWidget->readConfig();

    KConfigGroup group = KConfigGroup(config, u"ContactPrintThemeConfigureDialog"_s);
    const QSize sizeDialog = group.readEntry("Size", QSize(600, 400));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ContactPrintThemeConfigureDialog::writeConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(u"Global"_s);
    const KContacts::Addressee addr = mDefaultContact->contact();
    KContacts::VCardConverter converter;
    const QByteArray data = converter.exportVCard(addr, KContacts::VCardConverter::v3_0);
    group.writeEntry("defaultContact", data);

    group.writeEntry("defaultTemplate", mDefaultTemplate->toPlainText());
    mConfigureWidget->writeConfig();
}

#include "moc_contactprintthemeconfiguredialog.cpp"
