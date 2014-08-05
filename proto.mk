BUILD_ROOT := $(shell pwd)
PROTO_FILE_NAMES = common.proto meta_data.proto db_config.proto data.proto svc_config.proto
PROTO_PATH := $(BUILD_ROOT)/
PROTO_FILES := $(patsubst %.proto,$(PROTO_PATH)/%.proto,$(PROTO_FILE_NAMES)) 
PROTO_SOURCES := $(patsubst %.proto,%.pb.cc,$(PROTO_FILES))
PROTO_OBJECTS := $(patsubst %.pb.cc,%.pb.o,$(PROTO_SOURCES))
PROTO_DESCS := $(patsubst %.pb.cc,%.pb.desc,$(PROTO_SOURCES))
PROTOBUF_LDFLAGS := $(shell pkg-config --libs protobuf)
PROTOBUF_CFLAGS := $(shell pkg-config --cflags protobuf)
GTEST_PATH := $(BUILD_ROOT)/src/gtest
GTEST_CONFIG_STATUS := $(GTEST_PATH)/config.status
# FIXME integrate libtool better ...
GTEST_LIBDIR := $(GTEST_PATH)/lib/.libs/
GTEST_INCLUDE := $(GTEST_PATH)/include
GTEST_LIBS :=  $(GTEST_LIBDIR)/libgtest.a
GTEST_LDFLAGS := $(GTEST_LIBS) -L$(GTEST_LIBDIR)
GTEST_CFLAGS := -I$(GTEST_INCLUDE)

# FIXME on Windows
FIX_CXX_11_BUG =
LINUX_LDFLAGS =  
ifeq ($(shell uname), Linux)
FIX_CXX_11_BUG =  -Wl,--no-as-needed
LINUX_LDFLAGS =  -pthread
endif

CXXFLAGS += -std=c++11 -fPIC $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_CFLAGS) $(GTEST_CFLAGS)
LDFLAGS += $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_LDFLAGS) $(GTEST_LDFLAGS)

all: proto-static-lib gtest-pkg-build-all $(PROTO_DESCS)

proto-static-lib: $(PROTO_OBJECTS)
	ar rcs libproto.a $(PROTO_OBJECTS)

gtest-pkg-build-all: gtest-pkg-configure gtest-pkg-lib

gtest-pkg-configure: $(GTEST_CONFIG_STATUS)

$(GTEST_CONFIG_STATUS):
	@echo "doing configure in gtest in " $(GTEST_PATH) 
	cd $(GTEST_PATH) ; ./configure
	@echo "configure done in gtest"

# NOTE: assumption: the libdir will be created during build
gtest-pkg-lib: $(GTEST_LIBDIR)

$(GTEST_LIBDIR):
	@echo "building the gtest package"
	@make -C $(GTEST_PATH)
	@echo "building finished in gtest package"

gtest-pkg-clean:
	@echo "cleaning the gtest package"
	@make -C $(GTEST_PATH) clean
	@echo "cleaning finished in gtest package"

%.pb.o: %.pb.cc %.pb.h

%.pb.cc %.pb.h: %.proto
	protoc -I $(PROTO_PATH)/ --cpp_out=$(PROTO_PATH)/ $<

%.pb.desc: %.proto
	protoc -I $(PROTO_PATH)/ --descriptor_set_out=$@ --include_imports $<

$(PROTO_PATH)/data.pb.cc: $(PROTO_PATH)/common.pb.cc $(PROTO_PATH)/common.pb.h

$(PROTO_PATH)/meta_data.pb.cc: $(PROTO_PATH)/common.pb.cc $(PROTO_PATH)/common.pb.h

$(PROTO_PATH)/db_config.pb.cc: $(PROTO_PATH)/meta_data.pb.cc $(PROTO_PATH)/meta_data.pb.h

$(PROTO_PATH)/svc_config.pb.cc: $(PROTO_PATH)/meta_data.pb.h

clean: gtest-pkg-clean
	rm -f $(PROTO_OBEJCTS) *.a *.o *.pb.cc *.pb.h *.pb.desc

