################################################################################
#
# cli-visualizer
#
################################################################################

CLI_VISUALIZER_VERSION = 1.8
CLI_VISUALIZER_SITE = $(call github,dpayne,cli-visualizer,v$(CLI_VISUALIZER_VERSION))
CLI_VISUALIZER_LICENSE = MIT
CLI_VISUALIZER_LICENSE_FILES = LICENSE
CLI_VISUALIZER_DEPENDENCIES = host-pkgconf fftw-single ncurses

# Define the VIS_COMPILER_ARCH variable as "armv8-a" in CMakeLists.txt
# Is set to "native" if empty and throws an error when compiling
define CLI_VISUALIZER_VARFIX
	sed -i '11i set\(VIS_COMPILER_ARCH \"armv8-a\"\)' $(@D)/CMakeLists.txt
endef

CLI_VISUALIZER_POST_EXTRACT_HOOKS += CLI_VISUALIZER_VARFIX

$(eval $(cmake-package))