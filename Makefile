METAPHYSICL_DIR ?= ./MetaPhysicL/install
CPPFLAGS += -I$(METAPHYSICL_DIR)/include -I./eigen
LDFLAGS += -L$(METAPHYSICL_DIR)/lib -lmetaphysicl

all:
	echo "Specify a valid target"

test1: test1.C
	$(CXX) --std=c++14 -o test1 test1.C $(CPPFLAGS) $(LDFLAGS)

test2: test2.C
	$(CXX) --std=c++14 -o test2 test2.C $(CPPFLAGS) $(LDFLAGS)

clean:
	rm -f test1 test2
