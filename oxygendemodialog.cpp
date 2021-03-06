//////////////////////////////////////////////////////////////////////////////
// oxygendemodialog.cpp
// oxygen configuration dialog
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo.pereira@free.fr>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////
#include "oxygendemodialog.h"

#include "oxygenbenchmarkwidget.h"
#include "oxygenbuttondemowidget.h"
#include "oxygeninputdemowidget.h"
#include "oxygenframedemowidget.h"
#include "oxygenlistdemowidget.h"
#include "oxygenmdidemowidget.h"
#include "oxygensliderdemowidget.h"
#include "oxygentabdemowidget.h"
#include "oxygenstylechooser.h"

#include <QTextStream>
#include <QShortcut>
#include <QDialogButtonBox>

#include <QIcon>

namespace Oxygen
{
    //_______________________________________________________________
    DemoDialog::DemoDialog( QWidget* parent ):
        QDialog( parent ),
        _enableCheckBox( 0 ),
        _rightToLeftCheckBox( 0 )
    {

        setWindowTitle( tr( "Oxygen Demo" ) );
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
        setWindowFlag( Qt::Dialog, false );
#else
        setWindowFlags( windowFlags() & ~Qt::Dialog );
#endif

        // ui
        setupUi(this);

        // install Quit shortcut
        connect( new QShortcut( QKeySequence::Quit, this ), SIGNAL(activated()), SLOT(close()) );

        connect( buttonBox->button( QDialogButtonBox::Ok ), SIGNAL(clicked()), SLOT(close()) );

        // customize button box
        _enableCheckBox = new QCheckBox( tr( "Enabled" ) );
        _enableCheckBox->setChecked( true );
        connect( _enableCheckBox, SIGNAL(toggled(bool)), SLOT(toggleEnable(bool)) );
        buttonBox->addButton( _enableCheckBox, QDialogButtonBox::ResetRole );

        _rightToLeftCheckBox = new QCheckBox( tr( "Right to left layout" ) );
        _rightToLeftCheckBox->setChecked( qApp->isRightToLeft() );
        connect( _rightToLeftCheckBox, SIGNAL(toggled(bool)), SLOT(toggleRightToLeft(bool)) );
        connect( qApp, SIGNAL(layoutDirectionChanged(Qt::LayoutDirection)), SLOT(layoutDirectionChanged(Qt::LayoutDirection)) );
        buttonBox->addButton( _rightToLeftCheckBox, QDialogButtonBox::ResetRole );

        _flatLook = new QCheckBox( tr( "Flat look" ) );
        _flatLook->setChecked( false );
        connect( _flatLook, SIGNAL(toggled(bool)), SLOT(toggleFlat(bool)) );
        buttonBox->addButton( _flatLook, QDialogButtonBox::ResetRole );

        WidgetStyleChooser *styleChooser = new WidgetStyleChooser(this);
        styleChooser->createStyleSelectionMenu( tr( "Style" ) );
        buttonBox->addButton( styleChooser, QDialogButtonBox::ResetRole );

        connect( buttonBox->addButton( tr("About Qt"), QDialogButtonBox::HelpRole),
                 &QPushButton::clicked, qApp, &QApplication::aboutQt );

        // connections
        connect( pageWidget, SIGNAL(currentPageChanged(KPageWidgetItem*,KPageWidgetItem*)), SLOT(updateWindowTitle(KPageWidgetItem*)) );
        connect( pageWidget, SIGNAL(currentPageChanged(KPageWidgetItem*,KPageWidgetItem*)), SLOT(updateEnableState(KPageWidgetItem*)) );
        KPageWidgetItem *page, *first;
        DemoWidget *widget;

        // Create and add pages, "displaying" them immediately to pre-render them
        // (required to let the global "Flat look" feature work on pages the user
        // didn't visit yet.

        // inputs
        {
            first = page = new KPageWidgetItem( widget = new InputDemoWidget(nullptr, this) );
            page->setName( tr("Input Widgets") );
            setPageIcon( page, QStringLiteral( "edit-rename" ) );
            page->setHeader( tr("Shows the appearance of text input widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // tab
        {
            page = new KPageWidgetItem( widget = new TabDemoWidget() );
            page->setName( tr("Tab Widgets") );
            setPageIcon( page, QStringLiteral( "tab-detach" ) );
            page->setHeader( tr("Shows the appearance of tab widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // buttons
        {
            page = new KPageWidgetItem( widget = new ButtonDemoWidget(nullptr, this) );
            page->setName( tr("Buttons") );
            setPageIcon( page, QStringLiteral( "go-jump-locationbar" ) );
            page->setHeader( tr("Shows the appearance of buttons") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // lists
        {
            page = new KPageWidgetItem( widget = new ListDemoWidget() );
            page->setName( tr("Lists") );
            setPageIcon( page, QStringLiteral( "view-list-tree" ) );
            page->setHeader( tr("Shows the appearance of lists, trees and tables") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // frames
        {
            page = new KPageWidgetItem( widget = new FrameDemoWidget() );
            page->setName( tr("Frames") );
            setPageIcon( page, QStringLiteral( "draw-rectangle" ) );
            page->setHeader( tr("Shows the appearance of various framed widgets") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // mdi
        {
            page = new KPageWidgetItem( widget = new MdiDemoWidget() );
            page->setName( tr( "MDI Windows & Menus" ) );
            setPageIcon( page, QStringLiteral( "preferences-system-windows" ) );
            page->setHeader( tr( "Shows the appearance of MDI windows" ) );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // sliders
        {
            page = new KPageWidgetItem( widget = new SliderDemoWidget() );
            page->setName( tr("Sliders") );
            setPageIcon( page, QStringLiteral( "measure" ) );
            page->setHeader( tr("Shows the appearance of sliders, progress bars and scrollbars") );
            pageWidget->addPage( page );
            _widgets.append( widget );
            pageWidget->setCurrentPage(page);
        }

        // benchmark
        {
            BenchmarkWidget* benchmarkWidget( new BenchmarkWidget() );
            page = new KPageWidgetItem( benchmarkWidget );
            page->setName( tr("Benchmark") );
            setPageIcon( page, QStringLiteral( "system-run" ) );
            page->setHeader( tr("Emulates user interaction with widgets for benchmarking") );
            benchmarkWidget->init( pageWidget );

            pageWidget->addPage( page );
            _widgets.append( benchmarkWidget );
            pageWidget->setCurrentPage(page);
        }
        pageWidget->setCurrentPage(first);

        // connections
        QShortcut* shortcut( new QShortcut( Qt::CTRL + Qt::Key_X, this ) );
        foreach( DemoWidget* widget, _widgets )
        {
            if( widget->metaObject()->indexOfSlot( "benchmark()" ) >= 0 )
            { connect( shortcut, SIGNAL(activated()), widget, SLOT(benchmark()) ); }

            connect( this, SIGNAL(abortSimulations()), &widget->simulator(), SLOT(abort()) );

        }

    }

    //_______________________________________________________________
    void DemoDialog::updateWindowTitle( KPageWidgetItem* item )
    {

        QString title;
        QTextStream what( &title );
        if( item )
        {
            what << item->name();
            what << " - ";
        }

        what << tr( "Oxygen Demo" );
        setWindowTitle( title );
    }

    //_______________________________________________________________
    void DemoDialog::updateEnableState( KPageWidgetItem* item )
    {

        if( !( item && item->widget() && _enableCheckBox ) ) return;
        item->widget()->setEnabled( _enableCheckBox->isChecked() );

    }

    //_______________________________________________________________
    void DemoDialog::toggleEnable( bool value )
    {
        if( !( pageWidget->currentPage() && pageWidget->currentPage()->widget() ) ) return;
        pageWidget->currentPage()->widget()->setEnabled( value );
    }

    //_______________________________________________________________
    void DemoDialog::toggleRightToLeft( bool value )
    { qApp->setLayoutDirection( value ? Qt::RightToLeft:Qt::LeftToRight ); }

    //_______________________________________________________________
    void DemoDialog::layoutDirectionChanged( Qt::LayoutDirection direction )
    { _rightToLeftCheckBox->setChecked( direction == Qt::RightToLeft ); }

    //_______________________________________________________________
    void DemoDialog::toggleFlat( bool value )
    {
        for (auto w : pageWidget->findChildren<QLineEdit*>() ) {
            w->setFrame(!value);
        }
        for (auto w : pageWidget->findChildren<QComboBox*>() ) {
            w->setFrame(!value);
        }
        for (auto w : pageWidget->findChildren<QSpinBox*>() ) {
            w->setFrame(!value);
        }
        for (auto w : pageWidget->findChildren<QPushButton*>() ) {
            w->setFlat(value);
        }
        for (auto w : pageWidget->findChildren<QToolButton*>() ) {
            w->setAutoRaise(value);
        }
    }

    //_______________________________________________________________
    void DemoDialog::closeEvent( QCloseEvent* event )
    {
        emit abortSimulations();
        QDialog::closeEvent( event );
    }

    //_______________________________________________________________
    void DemoDialog::hideEvent( QHideEvent* event )
    {
        emit abortSimulations();
        QDialog::hideEvent( event );
    }

    //_______________________________________________________________
    void DemoDialog::setPageIcon( KPageWidgetItem* page, const QString& iconName ) const
    {
        #ifdef OXYGEN_USE_KDE4
        page->setIcon( KIcon( iconName ) );
        #else
        page->setIcon( QIcon::fromTheme( iconName ) );
        #endif
    }

}
