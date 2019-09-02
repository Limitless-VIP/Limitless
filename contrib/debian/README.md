
Debian
====================
This directory contains files used to package limitlessd/limitless-qt
for Debian-based Linux systems. If you compile limitlessd/limitless-qt yourself, there are some useful files here.

## limitless: URI support ##


limitless-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install limitless-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your limitlessqt binary to `/usr/bin`
and the `../../share/pixmaps/limitless128.png` to `/usr/share/pixmaps`

limitless-qt.protocol (KDE)

