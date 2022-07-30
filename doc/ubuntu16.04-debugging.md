# Debugging on Ubuntu 16.04

This document describes how I set up Ubuntu 16.04 for PHP extension debugging. There are really two cases: 

* PHP 7.x installed from packages
* PHP 7.x built from source code

In both cases, Apache2 was installed from standard Ubuntu apt repositories. 

I imagine these procedures would be similar for any contemporary Debian lineage distribution. (I happen to be working mostly on Ubuntu16.04 these days. Being a busy guy, I haven't tried this in other environments yet.)


# Common Operations Applicable to Both

## Step 1: Core File Setup

Ubuntu 16.04 comes with apport enabled ... which is groovy for conventional users but a pain for developers. 

### Disable apport

As root (via sudo or whatever), edit the file /etc/default/apport. Set

> enabled = 0

### Step 2: Set Core Pattern 

Decide where you want your core files to wind up. I put mine in a directory called /var/crash, and that is the destination I use in this procedure. Adapt to personal taste. 

As root (via sudo or whatever) create the crash directory

```bash
mkdir -p /var/crash
```

Insure that your user has read/write access to this directory.

As root (via sudo or whatever) create the file 

```
/etc/syscrtl.d/60-core-pattern.conf
```

Edit it so that it contains the line

```
kernel.core_pattern = /var/crash/core.%e.%p.%t
```

Now at this point, you can reboot and see if your changes are now reflected in /proc/sys/kernel/core_pattern. 

Note that you can achieve the same effect *temporarily* by issuing the command

```bash
sudo echo "/var/crash/core.%e.%p.%t" > /proc/sys/kernel/core_pattern
```
On next reboot, that would be wiped out. 

# PHP 7.x Installed from Packages

This procedure will allow gdb to resolve PHP internal symbols, enable some user defined gdb commands which are tailed for PHP 7 internals, and allow the user to inspect PHP 7 source code from gdb. This setup works even if you did not build PHP from source code, but instead installed from the usual repositories.

## Preconditions:

This procedure presumes you have Apache 2 and PHP 7.x (in my case, 7.3) set up and operating basically correctly. Apache and PHP have been installed from the widely used  ondrej repositories, and are currently up to date with the latest minor rev levels. In my setup up, I am using mod-php. 

In my /etc/apt/sources.list.d directory I have the following apt lists:

* ondrej-ubuntu-apache2-xenial.list
* ondrej-ubuntu-php-xenial.list

ondrej-ubuntu-apache2-xenial.list contains:

```
deb http://ppa.launchpad.net/ondrej/apache2/ubuntu xenial main
# deb-src http://ppa.launchpad.net/ondrej/apache2/ubuntu xenial main
```

Initially, ondrej-ubuntu-php-xenial.list contained:

```
deb http://ppa.launchpad.net/ondrej/php/ubuntu xenial main
# deb-src http://ppa.launchpad.net/ondrej/php/ubuntu xenial main
```

Insure that Steps 1 and 2 of the common operations above have been performed 
to your satisfaction. 


## Procedure Step 1: Install PHP debug symbols

As root, add the following line to /etc/apt/sources.list.d/ondrej-ubuntu-php-xenial.list

```
deb http://ppa.launchpad.net/ondrej/php/ubuntu xenial main/debug
```
So the file now looks like

```
deb http://ppa.launchpad.net/ondrej/php/ubuntu xenial main
deb http://ppa.launchpad.net/ondrej/php/ubuntu xenial main/debug
# deb-src http://ppa.launchpad.net/ondrej/php/ubuntu xenial main
```

Then install the debug symbols package. 

```Shell
sudo apt-get update
sudo apt-get upgrade
sudo apt install libapache2-mod-php7.3-dbgsym
```

## Procedure Step 2: Install the PHP source code

This is kind of optional but I highly recommend it. Download the PHP source code for the exact version of php you have installed. I got mine from 

https://www.php.net/distributions/php-7.3.13.tar.gz

Let's assume that was downloaded to /home/myname/Downloads/php-7.3.13.tar.gz

The debugger (because of the symbols we installed in step 1) is expecting the php source tree to be rooted at:

> /build/php7.3-UwOnoh/php7.3-7.3.13

This procedure makes that happen. 

```bash
sudo su -
mkdir -p /build/php7.3-UwOnoh/
cd /build/php7.3-UwOnoh/
tar -xvzf /home/myname/Downloads/php-7.3.13.tar.gz 
```

This will create a directory named php-7.3.13 in the /build/php7.3-UwOnoh/ directory. The debugger is expecting a somewhat different path ... so we will rename to conform the debug symbol and gdb expectations

```bash
mv php-7.3.13 php7.3-7.3.13
```

Then exit the superuser shell. 

## Procedure Step 3: Get a .gdbinit file

One is provided in the doc directory, and you could just get that one. But it is best to obtain the most current from the github repository: 

[php/php-src]https://github.com/php/php-src

.gdbinit will be in the php-src root.

However you obtain it, copy that to your home directory. 

To examine a core file, 

```
gdb <path to application> <path to core file>
```
For example, 

```Shell
gdb apache2 /var/crash/core.apache2.4187.1579553424
```

The zbacktrace command provided by the php .gdbinit file is incredibly convenient as it presents that stack in terms of you php code. The gdb where and bt commands work as normal. You will have symbolic references and be able to inspect code. 

# PHP 7.x build from source code

To be provided. 
