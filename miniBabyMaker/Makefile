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
cms2_core := CORE
CPPFLAGS  += -I$(cms2_core) 

# add CORE/MT2 support
cms2_core_mt2 := CORE/MT2
CPPFLAGS      += -I$(cms2_core_mt2) 

# add Tools support
cms2_tools  := Tools
CPPFLAGS  += -I$(cms2_tools) 

# add Tools/BTagReshaping support
cms2_tools_btagreshaping  := Tools/BTagReshaping
CPPFLAGS  += -I$(cms2_tools_btagreshaping) 

# add looperTools support
cwelke_tools  := looperTools
CPPFLAGS  += -I$(cwelke_tools) 

# add looperTools support
local_src  := src
CPPFLAGS  += -Iinclude 

# # create the dict.cc
# $(rootdict): $(headers)
# 	$(call root-cint,$(rootdict),$(headers),$(include_dir),$(link_def),$(defines))

# project specific variables 
# ----------------------------------------------------------------------- #

lib := libScanChain.so


sources := $(local_src)/ZMET.cc		                         \
		   $(local_src)/ScanChain.cc                \
		   $(local_src)/goodrun.cc                           \
		   $(cms2_tools_btagreshaping)/BTagReshaping.cc      \
		   $(cms2_tools_btagreshaping)/btag_payload_light.cc \
		   $(cms2_tools_btagreshaping)/btag_payload_b.cc     \
		   $(cms2_core)/metTemplatesSelections.cc  \
		   $(cms2_core_mt2)/MT2.cc                 \
		   $(cms2_core_mt2)/MT2Utility.cc          \
		   $(cwelke_tools)/eventFilter.cc          \
		   $(cwelke_tools)/jetUtils.cc             \
		   $(cwelke_tools)/genbtagTools.cc

objects := $(subst .cc,.o,$(sources)) ScanChain_dict.o
deps    := $(subst .cc,.d,$(sources)) ScanChain_dict.d


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
	@echo cms2_core = $(cms2_core)
	@echo cms2_core_mt2 = $(cms2_core_mt2)
	@echo cms2_tools = $(cms2_tools)
	@echo cms2_tools_btagreshaping = $(cms2_tools_btagreshaping)
	@echo cwelke_tools = $(cwelke_tools)
	@echo LDFLAGS = $(LDFLAGS)
	@echo CPPFLAGS = $(CPPFLAGS)

# build the library 
library: $(lib)

.PHONY: clean
clean:
	@rm $(lib) $(objects) $(deps)
	@if [ -f ScanChain_dict.h  ]; then rm ScanChain_dict.h  ; fi 
	@if [ -f ScanChain_dict.cc ]; then rm ScanChain_dict.cc ; fi 
	@if [ -f ScanChain_dict.o  ]; then rm ScanChain_dict.o  ; fi 
	@if [ -f ScanChain_dict.d  ]; then rm ScanChain_dict.d  ; fi 

# actual rule to build the library
$(lib) : $(objects)
	$(SHAREDLIB.cc) $@ $^

# root to build the ROOT CINT dictionary
ScanChain_dict.cc : include/ScanChain.h
	rootcint -v3 -f $@ -c -I$(cms2_core) -I$(cms2_core_mt2) -I$(cms2_tools) -I$(cms2_tools_btagreshaping) -I$(cwelke_tools) -DNDEBUG $^ LinkDef.h 

# ----------------------------------------------------------------------- #
# check dependencies
# ----------------------------------------------------------------------- #
-include $(deps)

%.d: %.cc
	@$(CXX) -M $(CXXFLAGS) $(CPPFLAGS) $< > $@.$$$$;    \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
