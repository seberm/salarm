TEMPLATE = subdirs

# Release option is ignored if debug is also specified
CONFIG += release \
		debug

SUBDIRS = src


unix {
	DISTFILES += LICENSE \
			 README
}
