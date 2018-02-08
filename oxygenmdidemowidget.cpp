//////////////////////////////////////////////////////////////////////////////
// oxygenmdidemowidget.cpp
// oxygen mdi windows demo widget
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

#include "oxygenmdidemowidget.h"

#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMenu>
#include <QIcon>
#include <QGuiApplication>

namespace Oxygen
{

    //______________________________________________________________
    MdiDemoWidget::MdiDemoWidget( QWidget* parent ):
        DemoWidget( parent )
    {
        setLayout( new QVBoxLayout() );
        QMenuBar* menuBar = new QMenuBar( this );
        // let the menubar appear in the MDI window on all platforms
        menuBar->setNativeMenuBar( false );
        layout()->addWidget( menuBar );

        QWidget* widget = new QWidget( this );
        layout()->addWidget( widget );
        ui.setupUi( widget );

        QMenu* menu = menuBar->addMenu( tr( "Layout" ) );
        QAction *action;
        menu->addSection( tr( "Exclusive actions" ) );
        QActionGroup *aGroup = new QActionGroup( menu );
        action = menu->addAction( tr( "Tile" ) );
        action->setCheckable( true );
        aGroup->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(setLayoutTiled()) );
        action = menu->addAction( tr( "Cascade" ) );
        action->setCheckable( true );
        aGroup->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(setLayoutCascade()) );
        action = menu->addAction( tr( "Tabs" ) );
        action->setCheckable( true );
        aGroup->addAction( action );
        connect( action, SIGNAL(triggered()), this, SLOT(setLayoutTabbed()) );

        menu->addSeparator();

        action = menu->addAction( tr( "<- Check here" ) );
        action->setCheckable( true );

        menu = menuBar->addMenu( tr( "Tools" ) );
        connect( action = menu->addAction( QIcon::fromTheme( QStringLiteral( "arrow-right" ) ), tr( "Select Next Window" ) ), SIGNAL(triggered()), ui.mdiArea, SLOT(activateNextSubWindow()) );
        action->setShortcut( Qt::CTRL + Qt::Key_Tab );
        addAction( action );

        connect( action = menu->addAction( QIcon::fromTheme( QStringLiteral( "arrow-left" ) ), tr( "Select Previous Window" ) ), SIGNAL(triggered()), ui.mdiArea, SLOT(activatePreviousSubWindow()) );
        action->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_Tab );
        addAction( action );

#ifdef Q_OS_MACOS
        // duplicate the MDI menubar in the native menubar
        if (QGuiApplication::platformName().contains(QLatin1String("cocoa")))
        {
            QMenuBar* menuBar = new QMenuBar( 0 );
            // make a global menubar
            menuBar->setNativeMenuBar( true );

            QMenu* menu = menuBar->addMenu( tr( "Layout" ) );
            QAction *action;
            menu->addSection( tr( "Exclusive actions" ) );
            QActionGroup *aGroup = new QActionGroup( menu );
            action = menu->addAction( tr( "Tile" ) );
            action->setCheckable( true );
            aGroup->addAction( action );
            connect( action, SIGNAL(triggered()), this, SLOT(setLayoutTiled()) );
            action = menu->addAction( tr( "Cascade" ) );
            action->setCheckable( true );
            aGroup->addAction( action );
            connect( action, SIGNAL(triggered()), this, SLOT(setLayoutCascade()) );
            action = menu->addAction( tr( "Tabs" ) );
            action->setCheckable( true );
            aGroup->addAction( action );
            connect( action, SIGNAL(triggered()), this, SLOT(setLayoutTabbed()) );

            menu->addSeparator();

            action = menu->addAction( tr( "<- Check here" ) );
            action->setCheckable( true );

            menu = menuBar->addMenu( tr( "Tools" ) );
            connect( action = menu->addAction( QIcon::fromTheme( QStringLiteral( "arrow-right" ) ), tr( "Select Next Window" ) ), SIGNAL(triggered()), ui.mdiArea, SLOT(activateNextSubWindow()) );
            action->setShortcut( Qt::CTRL + Qt::Key_Tab );
            addAction( action );

            connect( action = menu->addAction( QIcon::fromTheme( QStringLiteral( "arrow-left" ) ), tr( "Select Previous Window" ) ), SIGNAL(triggered()), ui.mdiArea, SLOT(activatePreviousSubWindow()) );
            action->setShortcut( Qt::CTRL + Qt::SHIFT + Qt::Key_Tab );
            addAction( action );
        }
#endif //Q_OS_MACOS
    }

    //______________________________________________________________
    void MdiDemoWidget::setLayoutTiled( void )
    {
        ui.mdiArea->setViewMode( QMdiArea::SubWindowView );
        ui.mdiArea->tileSubWindows();
    }

    //______________________________________________________________
    void MdiDemoWidget::setLayoutCascade( void )
    {
        ui.mdiArea->setViewMode( QMdiArea::SubWindowView );
        ui.mdiArea->cascadeSubWindows();
    }

    //______________________________________________________________
    void MdiDemoWidget::setLayoutTabbed( void )
    { ui.mdiArea->setViewMode( QMdiArea::TabbedView ); }

    //______________________________________________________________
    void MdiDemoWidget::benchmark( void )
    {
        if( !isVisible() ) return;

        if( true )
        {
            // slide windows
            foreach( QMdiSubWindow* window, ui.mdiArea->findChildren<QMdiSubWindow*>() )
            {
                simulator().click( window );
                simulator().slide( window, QPoint( 20, 20 ) );
                simulator().slide( window, QPoint( -20, -20 ) );
            }

        }

        if( true )
        {
            foreach( QAbstractButton* button, ui.toolBox->findChildren<QAbstractButton*>() )
            { simulator().click( button ); }

            foreach( QAbstractButton* button, ui.toolBox->findChildren<QAbstractButton*>() )
            { simulator().click( button ); }
        }

        simulator().run();

    }
}
