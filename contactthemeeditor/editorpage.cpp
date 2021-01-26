/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "editorpage.h"
#include "contacteditorwidget.h"
#include "contacttemplatewidget.h"
#include "editorwidget.h"
#include "previewwidget.h"
#include <KPIMTextEdit/PlainTextEditor>

#include <KSplitterCollapserButton>

#include <KLocalizedString>

#include <KConfigGroup>
#include <KSharedConfig>

#include <QSplitter>
#include <QVBoxLayout>

EditorPage::EditorPage(GrantleeThemeEditor::EditorPage::PageType type, const QString &projectDirectory, QWidget *parent)
    : GrantleeThemeEditor::EditorPage(type, parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);

    mMainSplitter = new QSplitter;
    if (mType == MainPage) {
        mWidgetSplitter = new QSplitter;
        mWidgetSplitter->setOrientation(Qt::Vertical);
        mWidgetSplitter->setChildrenCollapsible(false);
        lay->addWidget(mWidgetSplitter);

        mWidgetSplitter->addWidget(mMainSplitter);

        mPreview = new PreviewWidget(projectDirectory, this);
        mWidgetSplitter->addWidget(mPreview);
        connect(mPreview, &PreviewWidget::needUpdateViewer, this, &EditorPage::needUpdateViewer);
    } else {
        lay->addWidget(mMainSplitter);
    }

    mEditor = new ContactEditorWidget;

    if (mType == MainPage) {
        KConfigGroup group(KSharedConfig::openConfig(), QStringLiteral("Global"));
        mEditor->setPlainText(group.readEntry("defaultTemplate", QString()));
    }
    mMainSplitter->addWidget(mEditor);
    mContactTemplate = new ContactTemplateWidget(i18n("Theme Templates:"));
    connect(mContactTemplate, &ContactTemplateWidget::insertTemplate, mEditor->editor(), &QPlainTextEdit::insertPlainText);
    mMainSplitter->addWidget(mContactTemplate);
    mMainSplitter->setCollapsible(0, false);
    new KSplitterCollapserButton(mContactTemplate, mMainSplitter);

    connect(mEditor->editor(), &QPlainTextEdit::textChanged, this, &GrantleeThemeEditor::EditorPage::changed);

    if (mType == MainPage) {
        KConfigGroup group(KSharedConfig::openConfig(), "EditorPage");
        const QList<int> size{400, 100};
        mMainSplitter->setSizes(group.readEntry("mainSplitter", size));
        mWidgetSplitter->setSizes(group.readEntry("widgetSplitter", size));
    }
}

EditorPage::~EditorPage()
{
    if (mType == MainPage) {
        KConfigGroup group(KSharedConfig::openConfig(), "EditorPage");
        group.writeEntry("mainSplitter", mMainSplitter->sizes());
        group.writeEntry("widgetSplitter", mWidgetSplitter->sizes());
    }
}

GrantleeThemeEditor::PreviewWidget *EditorPage::preview() const
{
    return mPreview;
}
