SUBDIRS = 3ds \
	c_file \
	ds_arm9 \
	empty \
	empty_file \
	gamecube \
	gba \
	h_file \
	switch \
	wii

pkgdata_DATA = scriptedwizard.zip
CLEANFILES = $(pkgdata_DATA)

scriptdir = $(pkgdatadir)/templates/wizard

dist_script_DATA = common_functions.script \
		config.script

EXTRA_DIST = manifest.xml

scriptedwizard.zip: $(EXTRA_DIST)
	PWD=`pwd` cd $(srcdir) && zip $(PWD)/scriptedwizard.zip manifest.xml > /dev/null

