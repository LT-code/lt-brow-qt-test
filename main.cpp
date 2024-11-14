#include <QApplication>
#include <QCefContext.h>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    // create QApplication instance
    QApplication a(argc, argv);

    // build QCefConfig
    QCefConfig config;
    // set user agent
    config.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");
    // set log level
    config.setLogLevel(QCefConfig::LOGSEVERITY_DEBUG);
    // set JSBridge object name (default value is QCefViewClient)
    config.setBridgeObjectName("CallBridge");
    // port for remote debugging (default is 0 and means to disable remote debugging)
    config.setRemoteDebuggingPort(9000);
    // set background color for all browsers
    // (QCefSetting.setBackgroundColor will overwrite this value for specified browser instance)
    config.setBackgroundColor(Qt::red);

    // WindowlessRenderingEnabled is set to true by default,
    // set to false to disable the OSR mode
    config.setWindowlessRenderingEnabled(true);

    // add command line args, you can any cef supported switches or parameters
    config.addCommandLineSwitch("use-mock-keychain");
    // config.addCommandLineSwitch("disable-gpu");
    // config.addCommandLineSwitch("enable-gpu");

    // config.addCommandLineSwitch("enable-media-stream");
    // config.addCommandLineSwitch("allow-file-access-from-files");
    // config.addCommandLineSwitch("disable-spell-checking");
    // config.addCommandLineSwitch("disable-site-isolation-trials");
    // config.addCommandLineSwitch("enable-aggressive-domstorage-flushing");
    config.addCommandLineSwitchWithValue("renderer-process-limit", "1");
    // config.addCommandLineSwitchWithValue("disable-features", "BlinkGenPropertyTrees,TranslateUI,site-per-process");

    // create QCefContext instance with config,
    // the lifecycle of cefContext must be the same as QApplication instance
    QCefContext cefContext(&a, argc, argv, &config);

    // application window
    MainWindow w;
    w.show();

    // flying
    return a.exec();
}
