CPPFLAGS += -I./MetaPhysicL/install/include -I./eigen
LDFLAGS += -L./MetaPhysicL/install/lib -lmetaphysicl

all:
	echo "Specify a valid target"

test1: test1.C
	$(CXX) -o test1 test1.C $(CPPFLAGS) $(LDFLAGS)

test2: test2.C
	$(CXX) -o test2 test2.C $(CPPFLAGS) $(LDFLAGS)
