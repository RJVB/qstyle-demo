//////////////////////////////////////////////////////////////////////////////
// main.cpp
// oxygen-demo main
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

#include <QApplication>

#include <QCommandLineOption>
#include <QCommandLineParser>

#include <QIcon>
#include <QDebug>

namespace Oxygen
{

    int run(int argc, char *argv[])
    {
        QApplication app( argc, argv );

        QCommandLineParser commandLine;
        QCommandLineOption enableHighDpi( "highdpi", "Enable High DPI pixmaps" );
        commandLine.addOption( enableHighDpi );
        commandLine.addHelpOption();
        commandLine.process( app );

        app.setAttribute( Qt::AA_UseHighDpiPixmaps, commandLine.isSet( enableHighDpi ) );

        if ( QIcon::themeName().isEmpty()
            || QIcon::themeName() == QStringLiteral("hicolor")
            || QIcon::themeSearchPaths().at(0) == QStringLiteral(":/icons") ) {
            // No icon theme name is set, or we only search the embedded resource for it;
            // we'll get our icons from the embedded Oxygen icon theme copy.
            QIcon::setThemeName( QStringLiteral( "oxygen" ) );
            qInfo() << "Icon theme now" << QIcon::themeName() << "from search path" << QIcon::themeSearchPaths();
        }

        app.setApplicationName( app.tr( "QStyle Demo" ) );
        app.setWindowIcon( QIcon::fromTheme( QStringLiteral( "oxygen" ), app.windowIcon() ) );
        DemoDialog dialog;
        dialog.show();
        bool result = app.exec();
        return result;
    }

}

//__________________________________________
int main(int argc, char *argv[])
{
    return Oxygen::run( argc, argv );

}
