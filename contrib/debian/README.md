
Debian
====================
This directory contains files used to package tittiecoind/tittiecoin-qt
for Debian-based Linux systems. If you compile tittiecoind/tittiecoin-qt yourself, there are some useful files here.

## tittiecoin: URI support ##


tittiecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tittiecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your tittiecoinqt binary to `/usr/bin`
and the `../../share/pixmaps/tittiecoin128.png` to `/usr/share/pixmaps`

tittiecoin-qt.protocol (KDE)

