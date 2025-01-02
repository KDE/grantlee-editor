/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "themeeditortabwidget.h"
#include "editorpage.h"

#include <KLocalizedString>
#include <QIcon>
#include <QMenu>

#include <QTabBar>
using namespace GrantleeThemeEditor;

ThemeEditorTabWidget::ThemeEditorTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    setElideMode(Qt::ElideRight);
    tabBar()->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    setDocumentMode(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ThemeEditorTabWidget::customContextMenuRequested, this, &ThemeEditorTabWidget::slotTabContextMenuRequest);
}

ThemeEditorTabWidget::~ThemeEditorTabWidget() = default;

void ThemeEditorTabWidget::slotMainFileNameChanged(const QString &fileName)
{
    QTabBar *bar = tabBar();
    if (count() < 1) {
        return;
    }
    bar->setTabText(0, i18n("Editor (%1)", fileName));
}

void ThemeEditorTabWidget::slotTabContextMenuRequest(const QPoint &pos)
{
    if (count() <= 1) {
        return;
    }

    QTabBar *bar = tabBar();
    const int indexBar = bar->tabAt(bar->mapFrom(this, pos));
    QWidget *w = widget(indexBar);
    auto page = qobject_cast<EditorPage *>(w);
    if (!page) {
        return;
    }

    if (page->pageType() == EditorPage::ExtraPage) {
        QMenu menu(this);
        QAction *closeTab = menu.addAction(i18nc("@action:inmenu", "Close Tab"));
        closeTab->setIcon(QIcon::fromTheme(QStringLiteral("tab-close")));

        QAction *action = menu.exec(mapToGlobal(pos));

        if (action == closeTab) {
            Q_EMIT tabCloseRequested(indexBar);
        }
    }
}

#include "moc_themeeditortabwidget.cpp"
