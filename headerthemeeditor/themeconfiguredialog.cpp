/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themeconfiguredialog.h"
#include "themeeditorutil.h"
#include <KPIMTextEdit/PlainTextEditorWidget>

#include "configurewidget.h"

#include <KLocalizedString>
#include <KConfig>

#include <KConfigGroup>

#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>

ThemeConfigureDialog::ThemeConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure"));
    QTabWidget *tab = new QTabWidget;

    QWidget *w = new QWidget;

    QVBoxLayout *lay = new QVBoxLayout(w);

    mConfigureWidget = new GrantleeThemeEditor::ConfigureWidget;
    lay->addWidget(mConfigureWidget);

    QLabel *lab = new QLabel(i18n("Default email:"));
    lay->addWidget(lab);

    mDefaultEmail = new KPIMTextEdit::PlainTextEditorWidget;
    lay->addWidget(mDefaultEmail);
    tab->addTab(w, i18n("General"));

    mDefaultTemplate = new KPIMTextEdit::PlainTextEditorWidget;
    tab->addTab(mDefaultTemplate, i18n("Default Template"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tab);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ThemeConfigureDialog::reject);
    mainLayout->addWidget(buttonBox);
    buttonBox->button(QDialogButtonBox::Ok)->setFocus();

    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &ThemeConfigureDialog::slotDefaultClicked);
    connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &ThemeConfigureDialog::slotOkClicked);
    readConfig();
}

ThemeConfigureDialog::~ThemeConfigureDialog()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();

    KConfigGroup group = config->group(QStringLiteral("ThemeConfigureDialog"));
    group.writeEntry("Size", size());
}

void ThemeConfigureDialog::slotDefaultClicked()
{
    mConfigureWidget->setDefault();
    ThemeEditorUtil themeutil;
    mDefaultEmail->setPlainText(themeutil.defaultMail());
    mDefaultTemplate->clear();
}

void ThemeConfigureDialog::slotOkClicked()
{
    writeConfig();
    accept();
}

void ThemeConfigureDialog::readConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    ThemeEditorUtil themeutil;
    if (config->hasGroup(QStringLiteral("Global"))) {
        KConfigGroup group = config->group(QStringLiteral("Global"));
        mConfigureWidget->readConfig();
        mDefaultEmail->setPlainText(group.readEntry("defaultEmail", themeutil.defaultMail()));
        mDefaultTemplate->setPlainText(group.readEntry("defaultTemplate", QString()));
    } else {
        mDefaultEmail->setPlainText(themeutil.defaultMail());
    }

    KConfigGroup group = KConfigGroup(config, "ThemeConfigureDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(600, 400));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ThemeConfigureDialog::writeConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(QStringLiteral("Global"));
    group.writeEntry("defaultEmail", mDefaultEmail->toPlainText());
    group.writeEntry("defaultTemplate", mDefaultTemplate->toPlainText());
    mConfigureWidget->writeConfig();
}
