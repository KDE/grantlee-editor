/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "managethemes.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <QPushButton>

#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QDir>
#include <QDirIterator>
#include <QLabel>
#include <QListWidget>
#include <QStandardPaths>
#include <QVBoxLayout>

using namespace GrantleeThemeEditor;
class GrantleeThemeEditor::ManageThemesPrivate
{
public:
    ManageThemesPrivate() = default;

    QString mLocalDirectory;
    QListWidget *mListThemes = nullptr;
    QPushButton *mDeleteTheme = nullptr;
};

ManageThemes::ManageThemes(const QString &relativeThemePath, QWidget *parent)
    : QDialog(parent)
    , d(new GrantleeThemeEditor::ManageThemesPrivate)
{
    d->mLocalDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + u'/' + relativeThemePath;
    setWindowTitle(i18nc("@title:window", "Manage Theme"));
    auto w = new QWidget;

    auto lay = new QVBoxLayout(w);
    lay->setContentsMargins(0, 0, 0, 0);

    auto lab = new QLabel(i18nc("@label:textbox", "Local themes:"));
    lay->addWidget(lab);

    d->mListThemes = new QListWidget;
    connect(d->mListThemes, &QListWidget::itemSelectionChanged, this, &ManageThemes::slotItemSelectionChanged);
    d->mListThemes->setSelectionMode(QAbstractItemView::ExtendedSelection);
    lay->addWidget(d->mListThemes);

    d->mDeleteTheme = new QPushButton(i18nc("@action:button", "Delete theme"));
    connect(d->mDeleteTheme, &QPushButton::clicked, this, &ManageThemes::slotDeleteTheme);
    d->mDeleteTheme->setEnabled(false);
    lay->addWidget(d->mDeleteTheme);

    initialize();

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(w);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
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
    KConfigGroup group(KSharedConfig::openConfig(), u"ManageThemesDialog"_s);
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 150));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void ManageThemes::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), u"ManageThemesDialog"_s);
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
        const int answer = KMessageBox::questionTwoActions(this, msg, i18n("Remove theme"), KStandardGuiItem::remove(), KStandardGuiItem::cancel());
        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
            for (QListWidgetItem *item : selectItems) {
                if (QDir((d->mLocalDirectory + u'/' + item->text())).removeRecursively()) {
                    delete item;
                } else {
                    KMessageBox::error(this,
                                       i18n("Theme \"%1\" cannot be deleted. Please contact your administrator.", item->text()),
                                       i18n("Delete theme failed"));
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

#include "moc_managethemes.cpp"
