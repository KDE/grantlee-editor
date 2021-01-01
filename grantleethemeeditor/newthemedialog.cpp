/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "newthemedialog.h"
#include "globalsettings_base.h"

#include <KLineEdit>
#include <KLocalizedString>
#include <KUrlRequester>

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace GrantleeThemeEditor;
class GrantleeThemeEditor::NewThemeDialogPrivate
{
public:
    NewThemeDialogPrivate()
    {
    }

    KLineEdit *mThemeName = nullptr;
    KUrlRequester *mUrlRequester = nullptr;
    QPushButton *mOkButton = nullptr;
};
NewThemeDialog::NewThemeDialog(QWidget *parent)
    : QDialog(parent)
    , d(new GrantleeThemeEditor::NewThemeDialogPrivate)
{
    setWindowTitle(i18nc("@title:window", "New Theme"));

    QWidget *w = new QWidget;

    QVBoxLayout *lay = new QVBoxLayout(w);
    lay->setContentsMargins(0, 0, 0, 0);

    QLabel *lab = new QLabel(i18n("Theme name:"));
    lay->addWidget(lab);

    d->mThemeName = new KLineEdit;
    d->mThemeName->setClearButtonEnabled(true);
    d->mThemeName->setTrapReturnKey(true);
    connect(d->mThemeName, &KLineEdit::textChanged, this, &NewThemeDialog::slotUpdateOkButton);
    lay->addWidget(d->mThemeName);

    lab = new QLabel(i18n("Theme directory:"));
    lay->addWidget(lab);

    d->mUrlRequester = new KUrlRequester;
    d->mUrlRequester->setMode(KFile::Directory | KFile::LocalOnly);
    connect(d->mUrlRequester->lineEdit(), &KLineEdit::textChanged, this, &NewThemeDialog::slotUpdateOkButton);
    lay->addWidget(d->mUrlRequester);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(w);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    d->mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    d->mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &NewThemeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &NewThemeDialog::reject);
    mainLayout->addWidget(buttonBox);
    d->mOkButton->setDefault(true);
    d->mOkButton->setFocus();

    d->mOkButton->setEnabled(false);
    resize(300, 150);
    d->mThemeName->setFocus();
    readConfig();
}

NewThemeDialog::~NewThemeDialog()
{
    delete d;
}

void NewThemeDialog::readConfig()
{
    d->mUrlRequester->setUrl(QUrl::fromLocalFile(GrantleeThemeEditor::GrantleeThemeEditorSettings::path()));
}

QString NewThemeDialog::themeName() const
{
    return d->mThemeName->text();
}

QString NewThemeDialog::directory() const
{
    return d->mUrlRequester->lineEdit()->text();
}

void NewThemeDialog::slotUpdateOkButton()
{
    d->mOkButton->setEnabled(!d->mUrlRequester->lineEdit()->text().trimmed().isEmpty()
                             && !d->mThemeName->text().trimmed().isEmpty());
}
