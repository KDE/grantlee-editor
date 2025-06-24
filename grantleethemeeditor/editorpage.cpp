/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "editorpage.h"
using namespace Qt::Literals::StringLiterals;

#include "editorwidget.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KZip>
#include <QTemporaryFile>

#include <QFile>
#include <QTextStream>

using namespace GrantleeThemeEditor;

EditorPage::EditorPage(PageType type, QWidget *parent)
    : QWidget(parent)
    , mType(type)
{
}

EditorPage::~EditorPage() = default;

EditorPage::PageType EditorPage::pageType() const
{
    return mType;
}

void EditorPage::setPageFileName(const QString &filename)
{
    mPageFileName = filename;
}

QString EditorPage::pageFileName() const
{
    return mPageFileName;
}

GrantleeThemeEditor::EditorWidget *EditorPage::editor() const
{
    return mEditor;
}

void EditorPage::insertFile(const QString &filename)
{
    if (mEditor) {
        mEditor->insertFile(filename);
    }
}

void EditorPage::loadTheme(const QString &path)
{
    if (!mEditor) {
        return;
    }

    mEditor->clear();
    QFile file(path);
    if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        const QByteArray data = file.readAll();
        const QString str = QString::fromUtf8(data);
        file.close();
        mEditor->setPlainText(str);
    }
}

void EditorPage::saveTheme(const QString &path)
{
    if (!mEditor) {
        return;
    }

    const QString filename = path + u'/' + mPageFileName;
    saveAsFilename(filename);
}

void EditorPage::saveAsFilename(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << mEditor->toPlainText();
        file.close();
    } else {
        KMessageBox::error(this, i18n("Failed to open file \"%1\".", filename));
    }
}

void EditorPage::createZip(const QString &themeName, KZip *zip)
{
    QTemporaryFile tmp;
    tmp.open();
    saveAsFilename(tmp.fileName());
    const bool fileAdded = zip->addLocalFile(tmp.fileName(), themeName + u'/' + mPageFileName);
    if (!fileAdded) {
        KMessageBox::error(this, i18n("Failed to add file into ZIP archive."), i18nc("@title:window", "Failed to add file"));
    }
}

void EditorPage::installTheme(const QString &themePath)
{
    const QString filename = themePath + u'/' + mPageFileName;
    saveAsFilename(filename);
}

#include "moc_editorpage.cpp"
