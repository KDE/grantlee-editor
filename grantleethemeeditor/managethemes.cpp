/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "managethemes.h"

#include <KLocalizedString>
#include <QPushButton>
#include <KMessageBox>
#include <KSharedConfig>

#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QDialogButtonBox>
#include <KConfigGroup>

using namespace GrantleeThemeEditor;
class GrantleeThemeEditor::ManageThemesPrivate
{
public:
    ManageThemesPrivate()
    {
    }

    QString mLocalDirectory;
    QListWidget *mListThemes = nullptr;
    QPushButton *mDeleteTheme = nullptr;
};

ManageThemes::ManageThemes(const QString &relativeThemePath, QWidget *parent)
    : QDialog(parent)
    , d(new GrantleeThemeEditor::ManageThemesPrivate)
{
    d->mLocalDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + relativeThemePath;
    setWindowTitle(i18nc("@title:window", "Manage Theme"));
    QWidget *w = new QWidget;

    QVBoxLayout *lay = new QVBoxLayout(w);
    lay->setContentsMargins(0, 0, 0, 0);

    QLabel *lab = new QLabel(i18n("Local themes:"));
    lay->addWidget(lab);

    d->mListThemes = new QListWidget;
    connect(d->mListThemes, &QListWidget::itemSelectionChanged, this, &ManageThemes::slotItemSelectionChanged);
    d->mListThemes->setSelectionMode(QAbstractItemView::ExtendedSelection);
    lay->addWidget(d->mListThemes);

    d->mDeleteTheme = new QPushButton(i18n("Delete theme"));
    connect(d->mDeleteTheme, &QPushButton::clicked, this, &ManageThemes::slotDeleteTheme);
    d->mDeleteTheme->setEnabled(false);
    lay->addWidget(d->mDeleteTheme);

    initialize();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(w);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ManageThemes::reject);
    mainLayout->addWidget(buttonBox);

    readConfig();
}

ManageThemes::~ManageThemes()
{
    writeConfig();
    delete d;
}

void ManageThemes::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ManageThemesDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 150));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ManageThemes::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ManageThemesDialog");
    group.writeEntry("Size", size());
}

void ManageThemes::slotDeleteTheme()
{
    const QList<QListWidgetItem *> selectItems = d->mListThemes->selectedItems();
    if (!selectItems.isEmpty()) {
        QString msg;
        const int selectedThemeCount(selectItems.count());
        if (selectedThemeCount == 1) {
            msg = i18n("Do you want to remove the selected theme \"%1\" ?", selectItems.first()->text());
        } else {
            msg = i18n("Do you want to remove %1 selected themes?", selectedThemeCount);
        }
        if (KMessageBox::questionYesNo(this, msg, i18n("Remove theme")) == KMessageBox::Yes) {
            for (QListWidgetItem *item : selectItems) {
                if (QDir((d->mLocalDirectory + QLatin1Char('/') + item->text())).removeRecursively()) {
                    delete item;
                } else {
                    KMessageBox::error(this, i18n("Theme \"%1\" cannot be deleted. Please contact your administrator.", item->text()), i18n("Delete theme failed"));
                }
            }
        }
    }
}

void ManageThemes::initialize()
{
    QDir dir(d->mLocalDirectory);
    if (dir.exists()) {
        QDirIterator dirIt(d->mLocalDirectory, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot);
        while (dirIt.hasNext()) {
            dirIt.next();
            const QString dirName = dirIt.fileName();
            new QListWidgetItem(dirName, d->mListThemes);
        }
    }
}

void ManageThemes::slotItemSelectionChanged()
{
    d->mDeleteTheme->setEnabled(!d->mListThemes->selectedItems().isEmpty());
}
