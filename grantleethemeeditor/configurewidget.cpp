/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configurewidget.h"
#include "ui_configurewidget.h"
#include "globalsettings_base.h"

#include <KSharedConfig>
#include <QUrl>

using namespace GrantleeThemeEditor;
ConfigureWidget::ConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConfigureWidget)
{
    ui->setupUi(this);
}

ConfigureWidget::~ConfigureWidget()
{
    delete ui;
}

void ConfigureWidget::writeConfig()
{
    const QString authorEmail = ui->authorEmail->text().trimmed();
    if (!authorEmail.isEmpty()) {
        GrantleeThemeEditor::GrantleeThemeEditorSettings::setAuthorEmail(authorEmail);
    }
    const QString authorName = ui->author->text().trimmed();
    if (!authorName.isEmpty()) {
        GrantleeThemeEditor::GrantleeThemeEditorSettings::setAuthor(authorName);
    }
    QUrl url = ui->defaultPath->url();
    if (url.isValid()) {
        GrantleeThemeEditor::GrantleeThemeEditorSettings::setPath(url.path());
    }
    GrantleeThemeEditor::GrantleeThemeEditorSettings::self()->save();
}

void ConfigureWidget::readConfig()
{
    ui->authorEmail->setText(GrantleeThemeEditor::GrantleeThemeEditorSettings::authorEmail());
    ui->author->setText(GrantleeThemeEditor::GrantleeThemeEditorSettings::author());
    ui->defaultPath->setUrl(QUrl::fromLocalFile(GrantleeThemeEditor::GrantleeThemeEditorSettings::path()));
}

void ConfigureWidget::setDefault()
{
    ui->defaultPath->setUrl(QUrl());
    ui->authorEmail->clear();
    ui->author->clear();
}
