/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "themeeditorpage.h"
using namespace Qt::Literals::StringLiterals;

#include "contactprintthemepreview.h"
#include "desktopfilepage.h"
#include "editorpage.h"
#include "themeeditortabwidget.h"
#include "themeeditorwidget.h"
#include "themesession.h"

#include "contactprintthemeeditor_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <KZip>
#include <QInputDialog>
#include <QTemporaryDir>
#include <QUrl>

#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPointer>

ThemeEditorPage::ThemeEditorPage(const QString &projectDir, const QString &themeName, QWidget *parent)
    : QWidget(parent)
    , mThemeSession(new GrantleeThemeEditor::ThemeSession(projectDir, u"headerthemeeditor"_s))
{
    auto lay = new QHBoxLayout(this);
    mTabWidget = new GrantleeThemeEditor::ThemeEditorTabWidget;
    connect(mTabWidget, &GrantleeThemeEditor::ThemeEditorTabWidget::currentChanged, this, &ThemeEditorPage::slotCurrentWidgetChanged);
    lay->addWidget(mTabWidget);
    mEditorPage = new EditorPage(EditorPage::MainPage, projectDir);
    mEditorPage->setPageFileName(u"theme.html"_s);
    connect(mEditorPage, &EditorPage::needUpdateViewer, this, &ThemeEditorPage::slotUpdateViewer);
    connect(mEditorPage, &EditorPage::changed, this, &ThemeEditorPage::slotChanged);
    mTabWidget->addTab(mEditorPage, i18n("Editor (%1)", u"theme.html"_s));

    GrantleeThemeEditor::DesktopFilePage::DesktopFileOptions opt;
    mDesktopPage = new GrantleeThemeEditor::DesktopFilePage(u"theme.html"_s, opt, this);
    mDesktopPage->setDefaultDesktopName(u"theme.desktop"_s);
    mDesktopPage->setThemeName(themeName);
    mTabWidget->addTab(mDesktopPage, i18n("Desktop File"));

    connect(mDesktopPage,
            &GrantleeThemeEditor::DesktopFilePage::mainFileNameChanged,
            mEditorPage->preview(),
            &GrantleeThemeEditor::PreviewWidget::slotMainFileNameChanged);
    connect(mDesktopPage,
            &GrantleeThemeEditor::DesktopFilePage::mainFileNameChanged,
            mTabWidget,
            &GrantleeThemeEditor::ThemeEditorTabWidget::slotMainFileNameChanged);
    connect(mDesktopPage, &GrantleeThemeEditor::DesktopFilePage::changed, this, &ThemeEditorPage::slotChanged);
    connect(mTabWidget, &GrantleeThemeEditor::ThemeEditorTabWidget::tabCloseRequested, this, &ThemeEditorPage::slotCloseTab);
}

ThemeEditorPage::~ThemeEditorPage()
{
    qDeleteAll(mExtraPage);
    mExtraPage.clear();
    delete mThemeSession;
}

void ThemeEditorPage::slotCurrentWidgetChanged(int index)
{
    if (index < 0) {
        return;
    }
    auto page = dynamic_cast<GrantleeThemeEditor::EditorPage *>(mTabWidget->widget(index));
    Q_EMIT canInsertFile(page);
}

void ThemeEditorPage::updatePreview()
{
    mEditorPage->preview()->updateViewer();
}

void ThemeEditorPage::slotChanged()
{
    setChanged(true);
}

void ThemeEditorPage::setChanged(bool b)
{
    if (mChanged != b) {
        mChanged = b;
        Q_EMIT changed(b);
    }
}

void ThemeEditorPage::slotUpdateViewer()
{
    if (themeWasChanged()) {
        saveTheme(false);
    }
    mEditorPage->preview()->updateViewer();
}

void ThemeEditorPage::slotCloseTab(int index)
{
    mTabWidget->removeTab(index);
    setChanged(true);
}

void ThemeEditorPage::insertFile()
{
    QWidget *w = mTabWidget->currentWidget();
    if (!w) {
        return;
    }
    auto page = dynamic_cast<GrantleeThemeEditor::EditorPage *>(w);
    if (page) {
        const QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            page->insertFile(fileName);
        }
    }
}

bool ThemeEditorPage::themeWasChanged() const
{
    return mChanged;
}

void ThemeEditorPage::installTheme(const QString &themePath)
{
    QDir dir(themePath);
    QDir themeDir(themePath + u'/' + mDesktopPage->themeName());
    if (themeDir.exists()) {
        const int answer = KMessageBox::questionTwoActions(this,
                                                           i18n("Theme already exists. Do you want to overwrite it?"),
                                                           i18n("Theme already exists"),
                                                           KStandardGuiItem::overwrite(),
                                                           KStandardGuiItem::cancel());
        if (answer == KMessageBox::ButtonCode::SecondaryAction) {
            return;
        }
    } else {
        if (!dir.mkdir(mDesktopPage->themeName())) {
            KMessageBox::error(this, i18n("Cannot create theme folder."));
            return;
        }
    }
    const QString newPath = themePath + u'/' + mDesktopPage->themeName();
    mEditorPage->installTheme(newPath);
    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->installTheme(newPath);
    }
    mDesktopPage->installTheme(newPath);
    KMessageBox::information(this, i18n("Theme installed in \"%1\"", themeDir.absolutePath()));
}

void ThemeEditorPage::uploadTheme()
{
#if 0
    // force update for screenshot
    mEditorPage->preview()->updateViewer();
    QTemporaryDir tmp;
    const QString themename = mDesktopPage->themeName();
    const QString zipFileName = tmp.path() + u'/' + themename + QLatin1StringView(".zip");
    KZip *zip = new KZip(zipFileName);
    if (zip->open(QIODevice::WriteOnly)) {
        const QString previewFileName = tmp.path() + u'/' + themename + QLatin1StringView("_preview.png");
        // qCDebug(CONTACTPRINTTHEMEEDITOR_LOG)<<" previewFileName"<<previewFileName;
        QStringList lst;
        lst << previewFileName;
        mEditorPage->preview()->createScreenShot(lst);

        const bool fileAdded = zip->addLocalFile(previewFileName, themename + u'/' + QLatin1StringView("theme_preview.png"));
        if (!fileAdded) {
            KMessageBox::error(this, i18n("We cannot add preview file in zip file"), i18n("Failed to add file."));
            delete zip;
            return;
        }

        createZip(themename, zip);
        zip->close();
        // qCDebug(CONTACTPRINTTHEMEEDITOR_LOG)<< "zipFilename"<<zipFileName;

        QPointer<KNS3::UploadDialog> dialog = new KNS3::UploadDialog(u"messageviewer_header_themes.knsrc"_s, this);
        dialog->setUploadFile(QUrl::fromLocalFile(zipFileName));
        dialog->setUploadName(themename);
        dialog->setPreviewImageFile(0, QUrl::fromLocalFile(previewFileName));
        const QString description = mDesktopPage->description();
        dialog->setDescription(description.isEmpty() ? i18n("My favorite KMail header") : description);
        dialog->exec();
        delete dialog;
    } else {
        qCDebug(CONTACTPRINTTHEMEEDITOR_LOG) << " We can't open in zip write mode";
    }
    delete zip;
#endif
}

void ThemeEditorPage::createZip(const QString &themeName, KZip *zip)
{
    mEditorPage->createZip(themeName, zip);

    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->createZip(themeName, zip);
    }
    mDesktopPage->createZip(themeName, zip);
}

void ThemeEditorPage::addExtraPage()
{
    bool ok = false;
    QString filename = QInputDialog::getText(this, i18n("Filename of extra page"), i18n("Filename:"), {}, {}, &ok);
    if (ok) {
        if (!filename.trimmed().isEmpty()) {
            if (!filename.endsWith(QLatin1StringView(".html")) && !filename.endsWith(QLatin1StringView(".css"))
                && !filename.endsWith(QLatin1StringView(".js"))) {
                filename += QLatin1StringView(".html");
            }
            createExtraPage(filename);
            mThemeSession->addExtraPage(filename);
            setChanged(true);
        }
    }
}

EditorPage *ThemeEditorPage::createExtraPage(const QString &filename)
{
    auto extraPage = new EditorPage(EditorPage::ExtraPage, QString());
    connect(extraPage, &EditorPage::changed, this, &ThemeEditorPage::slotChanged);
    extraPage->setPageFileName(filename);
    mTabWidget->addTab(extraPage, filename);
    mTabWidget->setCurrentWidget(extraPage);
    mExtraPage.append(extraPage);
    return extraPage;
}

void ThemeEditorPage::storeTheme(const QString &directory)
{
    const QString themeDirectory = directory.isEmpty() ? projectDirectory() : directory;
    mEditorPage->saveTheme(themeDirectory);

    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->saveTheme(themeDirectory);
    }
    mDesktopPage->saveTheme(themeDirectory);
    mThemeSession->setMainPageFileName(mDesktopPage->filename());
    mThemeSession->writeSession(directory);
    if (directory.isEmpty()) {
        setChanged(false);
    }
}

bool ThemeEditorPage::saveTheme(bool withConfirmation)
{
    if (themeWasChanged()) {
        if (withConfirmation) {
            const int result = KMessageBox::questionTwoActionsCancel(this,
                                                                     i18n("Do you want to save current project?"),
                                                                     i18n("Save current project"),
                                                                     KStandardGuiItem::save(),
                                                                     KStandardGuiItem::discard());
            if (result == KMessageBox::ButtonCode::PrimaryAction) {
                storeTheme();
            } else if (result == KMessageBox::Cancel) {
                return false;
            }
        } else {
            storeTheme();
        }
    }
    setChanged(false);
    return true;
}

void ThemeEditorPage::loadTheme(const QString &filename)
{
    if (mThemeSession->loadSession(filename)) {
        mDesktopPage->loadTheme(mThemeSession->projectDirectory());
        mEditorPage->loadTheme(mThemeSession->projectDirectory() + u'/' + mThemeSession->mainPageFileName());
        mEditorPage->preview()->setThemePath(mThemeSession->projectDirectory(), mThemeSession->mainPageFileName());

        const QStringList lstExtraPages = mThemeSession->extraPages();
        for (const QString &page : lstExtraPages) {
            EditorPage *extraPage = createExtraPage(page);
            extraPage->loadTheme(mThemeSession->projectDirectory() + u'/' + page);
        }
        mTabWidget->setCurrentIndex(0);
        setChanged(false);
    }
}

void ThemeEditorPage::reloadConfig()
{
    mEditorPage->preview()->loadConfig();
}

QString ThemeEditorPage::projectDirectory() const
{
    return mThemeSession->projectDirectory();
}

void ThemeEditorPage::saveThemeAs(const QString &directory)
{
    storeTheme(directory);
}

#include "moc_themeeditorpage.cpp"
