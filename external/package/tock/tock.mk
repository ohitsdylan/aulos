################################################################################
#
# tock
#
################################################################################

TOCK_VERSION = 7d92d621559c5ac45f536ad987f6cd905ccc010b
TOCK_SITE = $(call github,nwtnni,tock,$(TOCK_VERSION))
TOCK_LICENSE = MIT
TOCK_LICENSE_FILES = LICENSE
TOCK_DEPENDENCIES = host-pkgconf ncurses

TOCK_CARGO_BUILD_OPTS += --no-default-features

$(eval $(cargo-package))
