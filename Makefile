CPPFLAGS += -I./MetaPhysicL/install/include -I./eigen
LDFLAGS += -L./MetaPhysicL/install/lib -lmetaphysicl
all: test

test: test.C
	$(CXX) -o test test.C $(CPPFLAGS) $(LDFLAGS)
