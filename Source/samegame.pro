QT += core gui

TARGET = samegame
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp samegamewidget.cpp
HEADERS += mainwindow.h samegamewidget.h
RESOURCES += samegame.qrc
TRANSLATIONS = samegame_en.ts samegame_fi.ts samegame_es.ts
CODECFORTR = UTF-8

os2: RC_FILE = samegame_os2.rc
win32: RC_FILE = samegame_win.rc

unix {
	message(Unix build)
	
	BINARY.path = $$PREFIX/bin
	BINARY.files = $$TARGET
	
	message(BINARY: $$BINARY.path/$$BINARY.files)
	
	DESKTOP.path = $$PREFIX/share/applications
	DESKTOP.files += samegame.desktop
	
	message(DESKTOP ENTRY: $$DESKTOP.path/$$DESKTOP.files)

	DOCS.path = $$PREFIX/share/doc/samegame-$$VERSION
	DOCS.files += gpl.txt readme.txt
	
	message(DOCS PATH: $$DOCS.path)	
	message(DOCS FILES: $$DOCS.files)	

	ICONS.path = $$PREFIX/share/icons/hicolor/scalable/apps
	ICONS.files += samegame.svg
	
	message(ICONS: $$ICONS.path/$$ICONS.files)	

	INSTALLS += BINARY DESKTOP DOCS ICONS
}

