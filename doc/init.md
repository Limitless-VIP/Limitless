# Sample init scripts and service configuration for limitlessd

Sample scripts and configuration files for systemd, Upstart and OpenRC can be
found in the contrib/init folder.

```
contrib/init/limitlessd.service:    systemd service unit configuration
contrib/init/limitlessd.openrc:     OpenRC compatible SysV style init script
contrib/init/limitlessd.openrcconf: OpenRC conf.d file
contrib/init/limitlessd.conf:       Upstart service configuration file
contrib/init/limitlessd.init:       CentOS compatible SysV style init script
```

## 1. Service User

All three startup configurations assume the existence of a "limitless" user and
group. They must be created before attempting to use these scripts.

## 2. Configuration

At a bare minimum, `limitlessd` requires that the rpcpassword setting be set
when running as a daemon. If the configuration file does not exist or this
setting is not set, `limitlessd` will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used as
a fixed token that `limitlessd` and client programs read from the configuration
file, however it is recommended that a strong and secure password be used as
this password is security critical to securing the wallet should the wallet be
enabled.

If `limitlessd` is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr. You can also generate
one from the shell yourself like this:

```
bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'
```

Once you have a password in hand, set rpcpassword= in `/etc/limitless/limitless.conf`

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/limitless.conf`.

## 3. Paths

All three configurations assume several paths that might need to be adjusted.

```
Binary:              /usr/bin/limitlessd
Configuration file:  /etc/limitless/limitless.conf
Data directory:      /var/lib/limitlessd
PID file:            /var/run/limitlessd/limitlessd.pid (OpenRC and Upstart)
                     /var/lib/limitlessd/limitlessd.pid (systemd)
```

The configuration file, PID directory (if applicable) and data directory should
all be owned by the limitless user and group. It is advised for security reasons
to make the configuration file and data directory only readable by the limitless
user and group. Access to `limitless-cli` and other `limitlessd` rpc clients can
then be controlled by group membership.

## 4. Installing Service Configuration

### 4.1. systemd

Installing this .service file consists on just copying it to
`/usr/lib/systemd/system` directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start limitlessd` and to enable for system startup run `systemctl enable limitlessd`

### 4.2. OpenRC

Rename `limitlessd.openrc` to `limitlessd` and drop it in `/etc/init.d`. Double
check ownership and permissions and make it executable. Test it with
`/etc/init.d/limitlessd start` and configure it to run on startup with
`rc-update add limitlessd`

### 4.3. Upstart (for Debian/Ubuntu based distributions)

Drop `limitlessd.conf` in `/etc/init`. Test by running `service limitlessd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the `start-stop-daemon` uitility.

### 4.4. CentOS

Copy `limitlessd.init` to `/etc/init.d/limitlessd`. Test by running
`service limitlessd start`.

Using this script, you can adjust the path and flags to the `limitlessd` program
by setting the `LIMITLESSD` and `FLAGS` environment variables in the file
`/etc/sysconfig/limitlessd`. You can also use the `DAEMONOPTS` environment
variable here.

## 5. Auto-respawn

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
