BUILD_ROOT := $(shell pwd)
PROTO_FILE_NAMES = common.proto meta_data.proto db_config.proto data.proto
PROTO_PATH := $(BUILD_ROOT)/
PROTO_FILES := $(patsubst %.proto,$(PROTO_PATH)/%.proto,$(PROTO_FILE_NAMES)) 
PROTO_SOURCES := $(patsubst %.proto,%.pb.cc,$(PROTO_FILES))
PROTO_OBJECTS := $(patsubst %.pb.cc,%.pb.o,$(PROTO_SOURCES))
PROTO_DESCS := $(patsubst %.pb.cc,%.pb.desc,$(PROTO_SOURCES))
PROTOBUF_LDFLAGS := $(shell pkg-config --libs protobuf)
PROTOBUF_CFLAGS := $(shell pkg-config --cflags protobuf)

# FIXME on Windows
FIX_CXX_11_BUG =
LINUX_LDFLAGS =  
ifeq ($(shell uname), Linux)
FIX_CXX_11_BUG =  -Wl,--no-as-needed
LINUX_LDFLAGS =  -pthread
endif

CXXFLAGS += -std=c++11 -fPIC $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_CFLAGS) 
LDFLAGS += $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_LDFLAGS) 

all: proto-static-lib $(PROTO_DESCS)

proto-static-lib: $(PROTO_OBJECTS)
	ar rcs libproto.a $(PROTO_OBJECTS)

%.pb.o: %.pb.cc %.pb.h

%.pb.cc %.pb.h: %.proto
	protoc -I $(PROTO_PATH)/ --cpp_out=$(PROTO_PATH)/ $<

%.pb.desc: %.proto
	protoc -I $(PROTO_PATH)/ --descriptor_set_out=$@ --include_imports $<

$(PROTO_PATH)/data.pb.cc: $(PROTO_PATH)/common.pb.cc $(PROTO_PATH)/common.pb.h

$(PROTO_PATH)/meta_data.pb.cc: $(PROTO_PATH)/common.pb.cc $(PROTO_PATH)/common.pb.h

$(PROTO_PATH)/db_config.pb.cc: $(PROTO_PATH)/meta_data.pb.cc $(PROTO_PATH)/meta_data.pb.h

clean:
	rm -f $(PROTO_OBEJCTS) *.a *.o *.pb.cc *.pb.h *.pb.desc

