# simple make file to compile the Z_looper

# low level stuff that independent of this project
# ----------------------------------------------------------------------- #

# include ROOT friendly c++ variables
include Makefile.arch

# conveniance command to make shared libs
SHAREDLIB.cc = $(CXX) $(ROOTLIBS) $(CPPFLAGS) $(LDFLAGS) $(SOFLAGS) $(TARGET_ARCH) -fPIC -o

# ROOT is missing the GenVector in its default setup 
LDFLAGS += -lGenVector -lEG -lTMVA -lMinuit -lMLP -lXMLIO -lTreePlayer -lMathMore

# CMS2 specific includes 
# ----------------------------------------------------------------------- #

# add CORE support
# cms2_core := ../CORE
# CPPFLAGS  += -I$(cms2_core) 
# LDFLAGS   += -L$(cms2_core) 

# add Tools/BTagReshaping support
cms2_tools_btagreshaping  := ../../Tools/BTagReshaping
CPPFLAGS  += -I$(cms2_tools_btagreshaping) 
LDFLAGS   += -L$(cms2_tools_btagreshaping) 

cwelke_tools  := ../../looperTools
CPPFLAGS  += -I$(cwelke_tools) 
LDFLAGS   += -L$(cwelke_tools) 

# create the dict.cc
$(rootdict): $(headers)
	$(call root-cint,$(rootdict),$(headers),$(include_dir),$(link_def),$(defines))

# project specific variables 
# ----------------------------------------------------------------------- #

lib := libvtxLooper.so

sources := TEMPLATES.cc		   		    \
		   $(cms2_tools_btagreshaping)/BTagReshaping.cc      \
		   $(cms2_tools_btagreshaping)/btag_payload_light.cc \
		   $(cms2_tools_btagreshaping)/btag_payload_b.cc     \
		   $(cwelke_tools)/genbtagTools.cc \
			vtxLooper.cc

objects := $(subst .cc,.o,$(sources)) vtxLooper_dict.o


# rules 
# ----------------------------------------------------------------------- #

# all rule should be first
.PHONY: all
all: library 

# for troubleshooting
.PHONY: test
test: 
	@echo lib = $(lib)
	@echo sources = $(sources)
	@echo objects = $(objects)
	@echo SHAREDLIB.cc = $(SHAREDLIB.cc)
	@echo cms2_tools_btagreshaping = $(cms2_tools_btagreshaping)
# @echo cms2_core = $(cms2_core)
	@echo cwelke_tools = $(cwelke_tools)
	@echo LDFLAGS = $(LDFLAGS)
	@echo CPPFLAGS = $(CPPFLAGS)

# build the library 
.PHONY: library
library: $(lib)

.PHONY: clean
clean:
	rm $(objects) $(lib) vtxLooper_dict.{cc,h} 

# actual rule to build the library
$(lib) : $(objects)
	$(SHAREDLIB.cc) $@ $^

# root to build the ROOT CINT dictionary
vtxLooper_dict.cc : vtxLooper.h #Z_looper.h
	rootcint -v3 -f $@ -c -DNDEBUG $^ LinkDef.h 

