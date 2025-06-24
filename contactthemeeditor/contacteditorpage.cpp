/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contacteditorpage.h"
using namespace Qt::Literals::StringLiterals;

#include "contacteditorwidget.h"
#include "desktopfilepage.h"
#include "editorpage.h"
#include "previewwidget.h"
#include "themeeditortabwidget.h"
#include "themesession.h"

#include "contactthemeeditor_debug.h"
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

ContactEditorPage::ContactEditorPage(const QString &projectDir, const QString &themeName, QWidget *parent)
    : QWidget(parent)
    , mThemeSession(new GrantleeThemeEditor::ThemeSession(projectDir, u"contactthemeeditor"_s))
{
    auto lay = new QHBoxLayout(this);
    mTabWidget = new GrantleeThemeEditor::ThemeEditorTabWidget(this);
    connect(mTabWidget, &GrantleeThemeEditor::ThemeEditorTabWidget::currentChanged, this, &ContactEditorPage::slotCurrentWidgetChanged);
    lay->addWidget(mTabWidget);
    mEditorPage = new EditorPage(EditorPage::MainPage, projectDir);
    mEditorPage->setPageFileName(u"contact.html"_s);
    connect(mEditorPage, &EditorPage::needUpdateViewer, this, &ContactEditorPage::slotUpdateViewer);
    connect(mEditorPage, &EditorPage::changed, this, &ContactEditorPage::slotChanged);
    mTabWidget->addTab(mEditorPage, i18n("Editor") + QLatin1StringView(" (contact.html)"));

    mEditorEmbeddedPage = createCustomPage(u"contact_embedded.html"_s);

    mEditorGroupPage = createCustomPage(u"contactgroup.html"_s);

    mEditorGroupEmbeddedPage = createCustomPage(u"contactgroup_embedded.html"_s);

    GrantleeThemeEditor::DesktopFilePage::DesktopFileOptions opt;
    mDesktopPage = new GrantleeThemeEditor::DesktopFilePage(u"contact.html"_s, opt, this);
    mDesktopPage->setDefaultDesktopName(u"theme.desktop"_s);
    mDesktopPage->setThemeName(themeName);
    mTabWidget->addTab(mDesktopPage, i18n("Desktop File"));

    connect(mDesktopPage, &GrantleeThemeEditor::DesktopFilePage::changed, this, &ContactEditorPage::slotChanged);
    connect(mTabWidget, &GrantleeThemeEditor::ThemeEditorTabWidget::tabCloseRequested, this, &ContactEditorPage::slotCloseTab);
}

ContactEditorPage::~ContactEditorPage()
{
    qDeleteAll(mExtraPage);
    mExtraPage.clear();
    delete mThemeSession;
}

void ContactEditorPage::updatePreview()
{
    mEditorPage->preview()->updateViewer();
}

void ContactEditorPage::slotChanged()
{
    setChanged(true);
}

void ContactEditorPage::setChanged(bool b)
{
    if (mChanged != b) {
        mChanged = b;
        Q_EMIT changed(b);
    }
}

void ContactEditorPage::slotUpdateViewer()
{
    if (themeWasChanged()) {
        (void)saveTheme(false);
    }
    mEditorPage->preview()->updateViewer();
}

void ContactEditorPage::slotCloseTab(int index)
{
    mTabWidget->removeTab(index);
    setChanged(true);
}

void ContactEditorPage::insertFile()
{
    QWidget *w = mTabWidget->currentWidget();
    if (!w) {
        return;
    }
    auto page = qobject_cast<GrantleeThemeEditor::EditorPage *>(w);
    if (page) {
        const QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            page->insertFile(fileName);
        }
    }
}

bool ContactEditorPage::themeWasChanged() const
{
    return mChanged;
}

void ContactEditorPage::installTheme(const QString &themePath)
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
    mEditorGroupPage->installTheme(newPath);
    mEditorGroupEmbeddedPage->installTheme(newPath);
    mEditorEmbeddedPage->installTheme(newPath);

    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->installTheme(newPath);
    }
    mDesktopPage->installTheme(newPath);
    KMessageBox::information(this, i18n("Theme installed in \"%1\"", themeDir.absolutePath()));
}

void ContactEditorPage::uploadTheme()
{
#if 0
    // force update for screenshot
    mEditorPage->preview()->updateViewer();
    QTemporaryDir tmp;
    const QString themename = mDesktopPage->themeName();
    const QString zipFileName = tmp.path() + u'/' + themename + QLatin1StringView(".zip");
    KZip *zip = new KZip(zipFileName);
    if (zip->open(QIODevice::WriteOnly)) {
        // TODO reactivate it when we will be able to create a preview
        const QString previewContactFileName = tmp.path() + u'/' + themename + QLatin1StringView("contact_preview.png");
        const QString previewContactGroupFileName = tmp.path() + u'/' + themename + QLatin1StringView("contactgroup_preview.png");
        QStringList lst;
        lst << previewContactFileName << previewContactGroupFileName;

        mEditorPage->preview()->createScreenShot(lst);

        bool fileAdded = zip->addLocalFile(previewContactFileName, themename + u'/' + QLatin1StringView("contact_preview.png"));
        if (!fileAdded) {
            KMessageBox::error(this, i18n("We cannot add preview file in zip file"), i18n("Failed to add file."));
            delete zip;
            return;
        }
        fileAdded = zip->addLocalFile(previewContactGroupFileName, themename + u'/' + QLatin1StringView("contactgroup_preview.png"));
        if (!fileAdded) {
            KMessageBox::error(this, i18n("We cannot add preview file in zip file"), i18n("Failed to add file."));
            delete zip;
            return;
        }
        createZip(themename, zip);
        zip->close();
        // qCDebug(CONTACTTHEMEEDITOR_LOG)<< "zipFilename"<<zipFileName;

        QPointer<KNS3::UploadDialog> dialog = new KNS3::UploadDialog(u"kaddressbook_themes.knsrc"_s, this);
        dialog->setUploadFile(QUrl::fromLocalFile(zipFileName));
        dialog->setUploadName(themename);
        dialog->setPreviewImageFile(0, QUrl::fromLocalFile(previewContactFileName));
        const QString description = mDesktopPage->description();
        dialog->setDescription(description.isEmpty() ? i18n("My favorite Kaddressbook theme") : description);
        dialog->exec();
        delete dialog;
    } else {
        qCDebug(CONTACTTHEMEEDITOR_LOG) << " We can't open in zip write mode";
    }
    delete zip;
#endif
}

void ContactEditorPage::createZip(const QString &themeName, KZip *zip)
{
    mEditorPage->createZip(themeName, zip);
    mEditorGroupPage->createZip(themeName, zip);
    mEditorGroupEmbeddedPage->createZip(themeName, zip);
    mEditorEmbeddedPage->createZip(themeName, zip);

    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->createZip(themeName, zip);
    }
    mDesktopPage->createZip(themeName, zip);
}

void ContactEditorPage::addExtraPage()
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

EditorPage *ContactEditorPage::createCustomPage(const QString &filename)
{
    auto customPage = new EditorPage(EditorPage::SecondPage, QString());
    connect(customPage, &EditorPage::changed, this, &ContactEditorPage::slotChanged);
    customPage->setPageFileName(filename);
    mTabWidget->addTab(customPage, filename);
    return customPage;
}

EditorPage *ContactEditorPage::createExtraPage(const QString &filename)
{
    auto extraPage = new EditorPage(EditorPage::ExtraPage, QString());
    connect(extraPage, &EditorPage::changed, this, &ContactEditorPage::slotChanged);
    extraPage->setPageFileName(filename);
    mTabWidget->addTab(extraPage, filename);
    mTabWidget->setCurrentWidget(extraPage);
    mExtraPage.append(extraPage);
    return extraPage;
}

void ContactEditorPage::storeTheme(const QString &directory)
{
    const QString themeDirectory = directory.isEmpty() ? projectDirectory() : directory;
    mEditorPage->saveTheme(themeDirectory);

    mEditorGroupPage->saveTheme(themeDirectory);
    mEditorGroupEmbeddedPage->saveTheme(themeDirectory);
    mEditorEmbeddedPage->saveTheme(themeDirectory);

    for (EditorPage *page : std::as_const(mExtraPage)) {
        page->saveTheme(themeDirectory);
    }
    mDesktopPage->saveTheme(themeDirectory);
    mThemeSession->setMainPageFileName(mEditorPage->pageFileName());
    mThemeSession->writeSession(themeDirectory);
    if (directory.isEmpty()) {
        setChanged(false);
    }
}

bool ContactEditorPage::saveTheme(bool withConfirmation)
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

void ContactEditorPage::loadTheme(const QString &filename)
{
    if (mThemeSession->loadSession(filename)) {
        const QString projectDirectory = mThemeSession->projectDirectory();
        mDesktopPage->loadTheme(projectDirectory);
        mEditorGroupPage->loadTheme(projectDirectory + QLatin1StringView("/contactgroup.html"));
        mEditorGroupEmbeddedPage->loadTheme(projectDirectory + QLatin1StringView("/contactgroup_embedded.html"));
        mEditorEmbeddedPage->loadTheme(projectDirectory + QLatin1StringView("/contact_embedded.html"));

        mEditorPage->loadTheme(projectDirectory + u'/' + mThemeSession->mainPageFileName());
        mEditorPage->preview()->setThemePath(projectDirectory, mThemeSession->mainPageFileName());

        const QStringList lstExtraPages = mThemeSession->extraPages();
        for (const QString &page : lstExtraPages) {
            EditorPage *extraPage = createExtraPage(page);
            extraPage->loadTheme(projectDirectory + u'/' + page);
        }
        mTabWidget->setCurrentIndex(0);
        setChanged(false);
    }
}

void ContactEditorPage::reloadConfig()
{
    mEditorPage->preview()->loadConfig();
}

QString ContactEditorPage::projectDirectory() const
{
    return mThemeSession->projectDirectory();
}

void ContactEditorPage::slotCurrentWidgetChanged(int index)
{
    if (index < 0) {
        return;
    }

    auto page = qobject_cast<GrantleeThemeEditor::EditorPage *>(mTabWidget->widget(index));
    Q_EMIT canInsertFile(page);
}

void ContactEditorPage::saveThemeAs(const QString &directory)
{
    storeTheme(directory);
}

#include "moc_contacteditorpage.cpp"
