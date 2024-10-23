################################################################################
#
# tty-clock
#
################################################################################

TTY_CLOCK_VERSION = 2.3
TTY_CLOCK_SITE = $(call github,xorg62,tty-clock,v$(TTY_CLOCK_VERSION))
TTY_CLOCK_LICENSE = BSD-3-Clause
TTY_CLOCK_LICENSE_FILES = LICENSE
TTY_CLOCK_DEPENDENCIES = host-pkgconf ncurses

$(eval $(autotools-package))
