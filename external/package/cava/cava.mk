################################################################################
#
# cava
#
################################################################################

CAVA_VERSION = 0.10.2
CAVA_SITE = $(call github,karlstav,cava,$(CAVA_VERSION))
CAVA_LICENSE = MIT
CAVA_LICENSE_FILES = LICENSE
CAVA_DEPENDENCIES = host-pkgconf alsa-lib fftw-single libtool ncurses libiniparser

CAVA_CONF_OPTS += --disable-input-pipewire
CAVA_CONF_OPTS += --disable-input-pulse
CAVA_CONF_OPTS += --disable-input-portaudio
CAVA_CONF_OPTS += --disable-input-sndio
CAVA_CONF_OPTS += --disable-input-oss
CAVA_CONF_OPTS += --disable-input-jack
CAVA_CONF_OPTS += --disable-output-sdl
CAVA_CONF_OPTS += --disable-output-sdl-glsl
CAVA_CONF_OPTS += --libdir=$(STAGING_DIR)/usr/lib

CAVA_AUTORECONF = YES

$(eval $(autotools-package))
