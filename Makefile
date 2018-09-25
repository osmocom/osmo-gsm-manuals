LIBOSMO_DIR ?= ~/source/gsm/libosmocore

all: check-deps
	cd OsmoBTS; $(MAKE)
	cd OsmoNITB; $(MAKE)
	cd OsmoBSC; $(MAKE)
	cd OsmoMGCP; $(MAKE)
	cd OsmoSGSN; $(MAKE)
	cd OsmoGGSN; $(MAKE)
	cd OsmoNAT; $(MAKE)
	cd OsmoPCU; $(MAKE)
	cd OsmoGSMTester; $(MAKE)
	cd OsmoMSC; $(MAKE)
	cd OsmoHLR; $(MAKE)
	cd OsmoSIPConnector; $(MAKE)
	cd OsmoSTP; $(MAKE)
	cd OsmocomBB; $(MAKE)
	cd OsmoMGW; $(MAKE)
	cd OsmoTRX; $(MAKE)

clean:
	cd OsmoBTS; $(MAKE) clean
	cd OsmoNITB; $(MAKE) clean
	cd OsmoBSC; $(MAKE) clean
	cd OsmoMGCP; $(MAKE) clean
	cd OsmoSGSN; $(MAKE) clean
	cd OsmoGGSN; $(MAKE) clean
	cd OsmoNAT; $(MAKE) clean
	cd OsmoPCU; $(MAKE) clean
	cd OsmoGSMTester; $(MAKE) clean
	cd OsmoMSC; $(MAKE) clean
	cd OsmoHLR; $(MAKE) clean
	cd OsmoSIPConnector; $(MAKE) clean
	cd OsmoSTP; $(MAKE) clean
	cd OsmocomBB; $(MAKE) clean
	cd OsmoMGW; $(MAKE) clean
	cd OsmoTRX; $(MAKE) clean

upload:
	cd OsmoBTS; $(MAKE) upload
	cd OsmoNITB; $(MAKE) upload
	cd OsmoBSC; $(MAKE) upload
	cd OsmoMGCP; $(MAKE) upload
	cd OsmoSGSN; $(MAKE) upload
	cd OsmoGGSN; $(MAKE) upload
	cd OsmoNAT; $(MAKE) upload
	cd OsmoPCU; $(MAKE) upload
	cd OsmoGSMTester; $(MAKE) upload
	cd OsmoMSC; $(MAKE) upload
	cd OsmoHLR; $(MAKE) upload
	cd OsmoSIPConnector; $(MAKE) upload
	cd OsmoSTP; $(MAKE) upload
	cd OsmocomBB; $(MAKE) upload
	cd OsmoMGW; $(MAKE) upload
	cd OsmoTRX; $(MAKE) upload

check:
	cd OsmoBTS; $(MAKE) check
	cd OsmoNITB; $(MAKE) check
	cd OsmoBSC; $(MAKE) check
	cd OsmoSGSN; $(MAKE) check
	cd OsmoGGSN; $(MAKE) check
	cd OsmoPCU; $(MAKE) check
	cd OsmoSTP; $(MAKE) check
	# These don't use asciidoc, so they have no 'make check' target:
	#cd OsmoMGCP; $(MAKE) check
	#cd OsmoNAT; $(MAKE) check
	#cd OsmoMGW; $(MAKE) check
	cd OsmoGSMTester; $(MAKE) check
	cd OsmoMSC; $(MAKE) check
	cd OsmoHLR; $(MAKE) check
	cd OsmoSIPConnector; $(MAKE) check
	cd OsmoSTP; $(MAKE) check
	cd OsmocomBB; $(MAKE) check
	cd OsmoTRX; $(MAKE) check

define check_dep_bin
    @type $(1) >/dev/null 2>&1 || { echo >&2 "Binary '$(1)' not found in path, please install $(2)."; exit 1; }
endef
define check_dep_python2_module
    @echo "import $(1)" | python2 - >/dev/null 2>&1 || { echo >&2 "Failed to import '$(1)' module, please install $(2)."; exit 1; }
endef
define check_dep_dir
	@test -d $(1) || { echo >&2 "Directory '$(1)' not found, please set $(2) to the path of your libosmocom source tree: make LIBOSMO_DIR=/path/to/libosmocore"; exit 1; }
endef

check-deps:
	$(call check_dep_bin,mscgen,mscgen)
	$(call check_dep_bin,xsltproc,libxslt)
	$(call check_dep_bin,git,git)
	$(call check_dep_bin,a2x,asciidoc)
	$(call check_dep_bin,asciidoc,asciidoc)
	$(call check_dep_bin,dblatex,dblatex)
	$(call check_dep_bin,packetdiag,nwdiag)
	$(call check_dep_bin,dot,graphviz)
	$(call check_dep_bin,python2,python2)
	$(call check_dep_python2_module,pychart,python2-pychart)
	$(call check_dep_dir,$(LIBOSMO_DIR),LIBOSMO_DIR)
