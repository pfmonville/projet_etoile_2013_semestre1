CXX=gcc
CXXFLAGS= -W -Wall -I./$(INCLDIR) -MMD -std=c99 #-fno-stack-protector
LDFLAGS=-lm#-L/usr/lib/x86_64-linux-gnu -lX11
EXEC=test
MOD=debug
ifeq ($(MOD), debug)
    CXXFLAGS+= -g
else ifeq ($(MOD), release)
	CXXFLAGS+= -O3
else
$(error Error : compilation mod not set correctly !)
endif
LIBDIR=lib
OBJDIR=obj
SRCDIR=src
INCLDIR=include
SRC:= $(shell find $(SRCDIR) -name '*.c')

OBJ= $(notdir $(SRC:.c=.o))
ALLOBJ:= $(addprefix $(OBJDIR)/,$(OBJ))


all: pre-build $(EXEC) post-build

pre-build: build-info
-include $(ALLOBJ:.o=.d)

post-build:
ifeq ($(MOD), release)
	@echo "Stripping binary"
	@strip $(EXEC)
endif
	@echo "End of compilation"

test: $(ALLOBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)


$(OBJDIR)/%.o:  $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	$(eval DepPath := $(patsubst %.o,%.d,$@))
	@cp -f $(DepPath) $(DepPath).tmp
	#@sed -e 's|.*:|$*.o:|' < $(DepPath).tmp > $(DepPath)
	@sed -e 's/.*://' -e 's/\\$$//' < $(DepPath).tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(DepPath)
	@rm -f $(DepPath).tmp

$(SRCDIR)/%.c: 	
	$(CXX) -o $@ -c -MM -MF $(patsubst %.o,%.d,$@) $< $(CXXFLAGS)

.PHONY: clean cleanall

cleanobj: 
	rm -rf $(OBJDIR)/*.o
	
cleandep:
	rm -rf $(OBJDIR)/*.d
	
clean: cleanobj cleandep

cleanall: clean
	rm -rf $(EXEC)
	
build-info:
	@echo "--------------------------------------------------------------"
	@echo "               COMPILATION OF PROJECT : "$(EXEC)             
	@echo "Generation mod is "$(MOD)
	@echo ""
	@echo "sources directory search path is : "$(SRCDIR)" (SRCDIR)"
	@echo "includes directory search path is : "$(INCLDIR)" (INCLDIR)"
	@echo "libraries directory search path is : "$(LIBDIR)" (LIBDIR)"
	@echo "objects directory is : "$(OBJDIR)" (OBJDIR)"
	@echo "--------------------------------------------------------------"

