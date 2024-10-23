################################################################################
#
# libiniparser
#
################################################################################

LIBINIPARSER_VERSION = 4.2.2
LIBINIPARSER_SITE = $(call gitlab,iniparser,iniparser,v$(LIBINIPARSER_VERSION))
LIBINIPARSER_LICENSE = MIT
LIBINIPARSER_LICENSE_FILES = LICENSE
LIBINIPARSER_INSTALL_STAGING = YES
LIBINIPARSER_INSTALL_TARGET = NO
LIBINIPARSER_CONF_OPTS += -DBUILD_DOCS=OFF
LIBINIPARSER_DEPENDENCIES  = host-pkgconf

$(eval $(cmake-package))
