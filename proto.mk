BUILD_ROOT           := $(shell pwd)
PROTO_PATH           := $(BUILD_ROOT)/
PROTO_FILE_NAMES     := common.proto meta_data.proto db_config.proto data.proto svc_config.proto diag.proto
PROTO_FILES          := $(patsubst %.proto,$(PROTO_PATH)/%.proto,$(PROTO_FILE_NAMES)) 
PROTO_SOURCES        := $(patsubst %.proto,%.pb.cc,$(PROTO_FILES))
PROTO_HEADERS        := $(patsubst %.proto,%.pb.h,$(PROTO_FILES))
PROTO_OBJECTS        := $(patsubst %.pb.cc,%.pb.o,$(PROTO_SOURCES))
PROTO_DESCS          := $(patsubst %.pb.cc,%.pb.desc,$(PROTO_SOURCES))
PROTOBUF_LDFLAGS     := $(shell pkg-config --libs protobuf)
PROTOBUF_CFLAGS      := $(shell pkg-config --cflags protobuf)
PROTOC               := $(shell which protoc)
PROTOC_VERSION       := $(shell $(PROTOC) --version)
PROTOC_MIN_VERSION   := 2.5.0
PROTOC_CHECK         := $(shell ./check-protoc-version.sh $(PROTOC_MIN_VERSION))


$(info protoc version is: $(PROTOC_VERSION) required minimum is: $(PROTOC_MIN_VERSION))
ifeq ($(PROTOC_CHECK), OK)
  $(info protoc check result is $(PROTOC_CHECK))
else
  $(error protoc check result is $(PROTOC_CHECK))
endif

# FIXME on Windows
FIX_CXX_11_BUG =
LINUX_LDFLAGS =  
ifeq ($(shell uname), Linux)
FIX_CXX_11_BUG  = -Wl,--no-as-needed
LINUX_LDFLAGS   = -pthread
endif

CXXFLAGS += -std=c++11 -fPIC $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_CFLAGS) -I$(BUILD_ROOT)/. -Wall
LDFLAGS += $(FIX_CXX_11_BUG) $(LINUX_LDFLAGS) $(PROTOBUF_LDFLAGS) 

PROTO_LIB := libproto.a

all: $(PROTO_LIB) $(PROTO_DESCS) 

$(PROTO_LIB): $(PROTO_OBJECTS) 
	ar rcsv $(PROTO_LIB) $(PROTO_OBJECTS)

.PRECIOUS: $(PROTO_SOURCES) $(PROTO_HEADERS)

%.pb.o: %.pb.cc %.pb.h

%.pb.cc %.pb.h: %.proto
	protoc -I $(PROTO_PATH)/ --cpp_out=$(PROTO_PATH)/ $<

%.pb.desc: %.proto
	protoc -I $(PROTO_PATH)/ --descriptor_set_out=$@ --include_imports $<

$(PROTO_PATH)/data.pb.cc: $(PROTO_PATH)/common.proto $(PROTO_PATH)/meta_data.proto

$(PROTO_PATH)/meta_data.pb.cc: $(PROTO_PATH)/common.proto

$(PROTO_PATH)/db_config.pb.cc: $(PROTO_PATH)/common.proto $(PROTO_PATH)/meta_data.proto 

$(PROTO_PATH)/svc_config.pb.cc: $(PROTO_PATH)/meta_data.pb.h

clean: 
	rm -f $(PROTO_OBEJCTS) *.a *.o *.pb.cc *.pb.h *.pb.desc

