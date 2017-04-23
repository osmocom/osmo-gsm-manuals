all:
	cd OsmoBTS; $(MAKE)
	cd OsmoNITB; $(MAKE)
	cd OsmoBSC; $(MAKE)
	cd OsmoMGCP; $(MAKE)
	cd OsmoSGSN; $(MAKE)
	cd OsmoNAT; $(MAKE)
	cd OsmoPCU; $(MAKE)
	cd OsmoGSMTester; $(MAKE)

clean:
	cd OsmoBTS; $(MAKE) clean
	cd OsmoNITB; $(MAKE) clean
	cd OsmoBSC; $(MAKE) clean
	cd OsmoMGCP; $(MAKE) clean
	cd OsmoSGSN; $(MAKE) clean
	cd OsmoNAT; $(MAKE) clean
	cd OsmoPCU; $(MAKE) clean
	cd OsmoGSMTester; $(MAKE) clean

upload:
	cd OsmoBTS; $(MAKE) upload
	cd OsmoNITB; $(MAKE) upload
	cd OsmoBSC; $(MAKE) upload
	cd OsmoMGCP; $(MAKE) upload
	cd OsmoSGSN; $(MAKE) upload
	cd OsmoNAT; $(MAKE) upload
	cd OsmoPCU; $(MAKE) upload
	cd OsmoGSMTester; $(MAKE) upload

check:
	cd OsmoBTS; $(MAKE) check
	cd OsmoNITB; $(MAKE) check
	cd OsmoBSC; $(MAKE) check
	cd OsmoSGSN; $(MAKE) check
	cd OsmoPCU; $(MAKE) check
	# These don't use asciidoc, so they have no 'make check' target:
	#cd OsmoMGCP; $(MAKE) check
	#cd OsmoNAT; $(MAKE) check
	cd OsmoGSMTester; $(MAKE) check
