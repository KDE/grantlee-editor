/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "desktopfilepage.h"
#include "globalsettings_base.h"

#include <KDesktopFile>
#include <KEditListWidget>
#include <KLocalizedString>
#include <KMessageBox>
#include <KZip>
#include <QLineEdit>
#include <QTemporaryFile>

#include <QGridLayout>
#include <QLabel>

#include <TextCustomEditor/PlainTextEditor>
#include <TextCustomEditor/PlainTextEditorWidget>

using namespace GrantleeThemeEditor;

DesktopFilePage::DesktopFilePage(const QString &defaultFileName, DesktopFilePage::DesktopFileOptions options, QWidget *parent)
    : QWidget(parent)
{
    auto gridLayout = new QGridLayout(this);
    auto lab = new QLabel(i18nc("@label:textbox", "Name:"), this);
    mName = new QLineEdit(this);
    mName->setReadOnly(true);
    int row = 0;
    gridLayout->addWidget(lab, row, 0);
    gridLayout->addWidget(mName, row, 1);

    ++row;
    lab = new QLabel(i18nc("@label:textbox", "Author:"), this);
    mAuthor = new QLineEdit(this);
    mAuthor->setClearButtonEnabled(true);
    gridLayout->addWidget(lab, row, 0);
    gridLayout->addWidget(mAuthor, row, 1);

    ++row;
    lab = new QLabel(i18nc("@label:textbox", "Email:"), this);
    mEmail = new QLineEdit(this);
    mEmail->setClearButtonEnabled(true);
    gridLayout->addWidget(lab, row, 0);
    gridLayout->addWidget(mEmail, row, 1);

    ++row;
    lab = new QLabel(i18nc("@label:textbox", "Description:"));
    mDescription = new TextCustomEditor::PlainTextEditorWidget(this);
    mDescription->editor()->setSearchSupport(false);
    gridLayout->addWidget(lab, row, 0);
    gridLayout->addWidget(mDescription, row, 1);

    if (options & SpecifyFileName) {
        ++row;
        lab = new QLabel(i18nc("@label:textbox", "Filename:"), this);
        mFilename = new QLineEdit(this);
        mFilename->setText(defaultFileName);
        connect(mFilename, &QLineEdit::textChanged, this, &DesktopFilePage::slotFileNameChanged);
        gridLayout->addWidget(lab, row, 0);
        gridLayout->addWidget(mFilename, row, 1);
    }

    ++row;
    lab = new QLabel(i18nc("@label:textbox", "Version:"));
    mVersion = new QLineEdit(this);
    mVersion->setClearButtonEnabled(true);
    mVersion->setText(QStringLiteral("0.1"));
    gridLayout->addWidget(lab, row, 0);
    gridLayout->addWidget(mVersion, row, 1);

    ++row;
    if (options & ExtraDisplayVariables) {
        lab = new QLabel(i18nc("@label:textbox", "Extract Headers:"), this);
        gridLayout->addWidget(lab, row, 0);

        ++row;
        lab = new QLabel(QStringLiteral("<qt><b>")
                             + i18n("Be careful, Grantlee does not support '-' in variable name. So when you want to add extra header as \"X-Original-To\" add "
                                    "\"X-Original-To\" in list, but use \"XOriginalTo\" as variable in Grantlee (remove '-' in name).")
                             + QStringLiteral("</b></qt>"),
                         this);
        lab->setWordWrap(true);
        gridLayout->addWidget(lab, row, 0, 1, 2);

        ++row;
        mExtraDisplayHeaders = new KEditListWidget(this);
        gridLayout->addWidget(mExtraDisplayHeaders, row, 0, 1, 2);
        connect(mExtraDisplayHeaders, &KEditListWidget::changed, this, &DesktopFilePage::slotExtraDisplayHeadersChanged);
    } else {
        gridLayout->setRowStretch(row, 1);
    }

    mEmail->setText(GrantleeThemeEditor::GrantleeThemeEditorSettings::authorEmail());
    mAuthor->setText(GrantleeThemeEditor::GrantleeThemeEditorSettings::author());

    connect(mDescription->editor(), &QPlainTextEdit::textChanged, this, &DesktopFilePage::changed);
    connect(mEmail, &QLineEdit::textChanged, this, &DesktopFilePage::changed);
    connect(mAuthor, &QLineEdit::textChanged, this, &DesktopFilePage::changed);
    connect(mVersion, &QLineEdit::textChanged, this, &DesktopFilePage::changed);
}

DesktopFilePage::~DesktopFilePage() = default;

void DesktopFilePage::slotExtraDisplayHeadersChanged()
{
    Q_EMIT extraDisplayHeaderChanged(mExtraDisplayHeaders->items());
    Q_EMIT changed();
}

void DesktopFilePage::slotFileNameChanged(const QString &filename)
{
    Q_EMIT mainFileNameChanged(filename);
    Q_EMIT changed();
}

void DesktopFilePage::createZip(const QString &themeName, KZip *zip)
{
    QTemporaryFile tmp;
    tmp.open();
    saveAsFilename(tmp.fileName());
    const bool fileAdded = zip->addLocalFile(tmp.fileName(), themeName + QLatin1Char('/') + mDefaultDesktopName);
    if (!fileAdded) {
        KMessageBox::error(this, i18n("Failed to add file into ZIP archive."), i18nc("@title:window", "Failed to add file"));
    }
}

void DesktopFilePage::setThemeName(const QString &themeName)
{
    mName->setText(themeName);
}

QString DesktopFilePage::filename() const
{
    if (mFilename) {
        return mFilename->text();
    }
    return {};
}

QString DesktopFilePage::themeName() const
{
    return mName->text();
}

void DesktopFilePage::loadTheme(const QString &path)
{
    const QString filename = path + QLatin1Char('/') + mDefaultDesktopName;
    KDesktopFile desktopFile(filename);
    mName->setText(desktopFile.desktopGroup().readEntry(QStringLiteral("Name")));
    mDescription->setPlainText(desktopFile.desktopGroup().readEntry(QStringLiteral("Description")));
    if (mFilename) {
        mFilename->setText(desktopFile.desktopGroup().readEntry(QStringLiteral("FileName")));
    }
    mAuthor->setText(desktopFile.desktopGroup().readEntry(QStringLiteral("Author")));
    mEmail->setText(desktopFile.desktopGroup().readEntry(QStringLiteral("AuthorEmail")));
    mVersion->setText(desktopFile.desktopGroup().readEntry(QStringLiteral("ThemeVersion")));
    if (mExtraDisplayHeaders) {
        const QStringList displayExtraHeaders = desktopFile.desktopGroup().readEntry(QStringLiteral("DisplayExtraVariables"), QStringList());
        mExtraDisplayHeaders->setItems(displayExtraHeaders);
    }
}

void DesktopFilePage::saveTheme(const QString &path)
{
    const QString filename = path + QLatin1Char('/') + mDefaultDesktopName;
    saveAsFilename(filename);
}

void DesktopFilePage::saveAsFilename(const QString &filename)
{
    KDesktopFile desktopFile(filename);
    desktopFile.desktopGroup().writeEntry(QStringLiteral("Name"), mName->text());
    desktopFile.desktopGroup().writeEntry(QStringLiteral("Description"), mDescription->toPlainText());
    if (mFilename) {
        desktopFile.desktopGroup().writeEntry(QStringLiteral("FileName"), mFilename->text());
    }
    if (mExtraDisplayHeaders) {
        const QStringList displayExtraHeaders = mExtraDisplayHeaders->items();
        if (!displayExtraHeaders.isEmpty()) {
            desktopFile.desktopGroup().writeEntry(QStringLiteral("DisplayExtraVariables"), displayExtraHeaders);
        }
    }

    desktopFile.desktopGroup().writeEntry(QStringLiteral("Author"), mAuthor->text());
    desktopFile.desktopGroup().writeEntry(QStringLiteral("AuthorEmail"), mEmail->text());
    desktopFile.desktopGroup().writeEntry(QStringLiteral("ThemeVersion"), mVersion->text());
    desktopFile.desktopGroup().sync();
}

void DesktopFilePage::installTheme(const QString &themePath)
{
    const QString filename = themePath + QLatin1Char('/') + mDefaultDesktopName;
    saveAsFilename(filename);
}

void DesktopFilePage::setDefaultDesktopName(const QString &name)
{
    mDefaultDesktopName = name;
}

QString DesktopFilePage::description() const
{
    return mDescription->toPlainText();
}

#include "moc_desktopfilepage.cpp"
