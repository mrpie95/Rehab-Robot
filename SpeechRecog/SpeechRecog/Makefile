# Copyright 2016 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#GOOGLEAPIS_GENS_PATH ?= $(HOME)/gitrepos/googleapis/gens
GOOGLEAPIS_GENS_PATH ?= /home/nao/Dependencies/googleapis/gens
GOOGLEAPIS_API_CCS = $(shell find $(GOOGLEAPIS_GENS_PATH)/google/api \
	-name '*.pb.cc')
GOOGLEAPIS_RPC_CCS = $(shell find $(GOOGLEAPIS_GENS_PATH)/google/rpc \
	-name '*.pb.cc')
GOOGLEAPIS_SPEECH_CCS = $(shell find \
	$(GOOGLEAPIS_GENS_PATH)/google/cloud/speech -name '*.pb.cc')
GOOGLEAPIS_LONGRUNNING_CCS = $(shell find \
	$(GOOGLEAPIS_GENS_PATH)/google/longrunning -name '*.pb.cc')
GOOGLEAPIS_CCS = $(GOOGLEAPIS_API_CCS) $(GOOGLEAPIS_RPC_CCS) \
	$(GOOGLEAPIS_LONGRUNNING_CCS) $(GOOGLEAPIS_SPEECH_CCS)

HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += -I/usr/local/include -I/usr/include/python2.7 -pthread 
# -I$(GOOGLEAPIS_GENS_PATH) 
CXXFLAGS += -std=c++11
LDFLAGS += -L/usr/local/lib -lpython2.7 -ldl -lutil -lpthread

#LDFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
#           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
#           -lprotobuf -lpthread -ldl

.PHONY: all
all: kinectmic speechrecog

googleapis.ar: $(GOOGLEAPIS_CCS:.cc=.o)
	ar r $@ $?

kinectmic: main.o kinectmic.o
	$(CXX) $^ $(LDFLAGS) -o $@

speechrecog: speechrecogwrapper.o main.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o speechrecog kinectmic googleapis.ar \
		$(GOOGLEAPIS_CCS:.cc=.o)

