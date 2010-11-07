TEMPLATE = subdirs

# Release option is ignored if debug is also specified
CONFIG += release \
		debug


SUBDIRS = src

DISTFILES += LICENSE \
	     README
