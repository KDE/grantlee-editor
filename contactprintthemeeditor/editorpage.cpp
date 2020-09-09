/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "editorpage.h"
#include "editorwidget.h"
#include "previewwidget.h"
#include "themeeditorwidget.h"
#include "themetemplatewidget.h"
#include "contactprintthemepreview.h"
#include "contactprintthemeeditorutil.h"
#include <KPIMTextEdit/PlainTextEditor>
#include "KSplitterCollapserButton"

#include <KLocalizedString>

#include <KConfigGroup>

#include <QSplitter>
#include <QVBoxLayout>
#include <KSharedConfig>

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

        mPreview = new ContactPrintThemePreview(projectDirectory);
        mWidgetSplitter->addWidget(mPreview);
        connect(mPreview, &ContactPrintThemePreview::needUpdateViewer, this, &EditorPage::needUpdateViewer);
    } else {
        lay->addWidget(mMainSplitter);
    }

    mEditor = new ThemeEditorWidget;

    if (mType == MainPage) {
        ContactPrintThemeEditorutil contactUtil;
        KConfigGroup group(KSharedConfig::openConfig(), QStringLiteral("Global"));
        mEditor->setPlainText(group.readEntry("defaultTemplate", contactUtil.defaultTemplate()));
    }
    mMainSplitter->addWidget(mEditor);
    mThemeTemplate = new ThemeTemplateWidget(i18n("Theme Templates:"));
    connect(mThemeTemplate, &ThemeTemplateWidget::insertTemplate, mEditor->editor(), &QPlainTextEdit::insertPlainText);
    mMainSplitter->addWidget(mThemeTemplate);
    mMainSplitter->setCollapsible(0, false);
    new KSplitterCollapserButton(mThemeTemplate, mMainSplitter);

    connect(mEditor->editor(), &QPlainTextEdit::textChanged, this, &GrantleeThemeEditor::EditorPage::changed);

    if (mType == MainPage) {
        KConfigGroup group(KSharedConfig::openConfig(), "EditorPage");
        const QList<int> size {
            400, 100
        };
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

ContactPrintThemePreview *EditorPage::preview() const
{
    return mPreview;
}
