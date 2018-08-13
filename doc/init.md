Sample init scripts and service configuration for tittiecoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/tittiecoind.service:    systemd service unit configuration
    contrib/init/tittiecoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/tittiecoind.openrcconf: OpenRC conf.d file
    contrib/init/tittiecoind.conf:       Upstart service configuration file
    contrib/init/tittiecoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "tittiecoin" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, tittiecoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, tittiecoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that tittiecoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If tittiecoind is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/tittiecoin/tittiecoin.conf

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/tittiecoin.conf.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/tittiecoind
Configuration file:  /etc/tittiecoin/tittiecoin.conf
Data directory:      /var/lib/tittiecoind
PID file:            /var/run/tittiecoind/tittiecoind.pid (OpenRC and Upstart)
                     /var/lib/tittiecoind/tittiecoind.pid (systemd)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the tittiecoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
tittiecoin user and group.  Access to tittiecoin-cli and other tittiecoind rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists on just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start tittiecoind" and to enable for system startup run
"systemctl enable tittiecoind"

4b) OpenRC

Rename tittiecoind.openrc to tittiecoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/tittiecoind start" and configure it to run on startup with
"rc-update add tittiecoind"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop tittiecoind.conf in /etc/init.  Test by running "service tittiecoind start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon uitility.

4d) CentOS

Copy tittiecoind.init to /etc/init.d/tittiecoind. Test by running "service tittiecoind start".

Using this script, you can adjust the path and flags to the tittiecoind program by
setting the TittieCoinD and FLAGS environment variables in the file
/etc/sysconfig/tittiecoind. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
