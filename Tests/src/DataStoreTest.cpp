#include <algorithm>
#include "gtest/gtest.h"
#include "SimEngine/Object.h"
#include "Core/DataStore.h"

class DummyObject : public TObject {
public:
    DummyObject(std::string name) : TObject(name) {
        properties.insert(
            {"Property", new TProperties({{"Property", 0}}, false, "Property")});
    }
};

TEST(DataStoreTest, Can_Create) {
    std::vector<IObject*> allObjects(15);
    std::for_each(allObjects.begin(), allObjects.end(), [](auto& elem) {elem = new DummyObject("dummy");} );
    ASSERT_NO_THROW(TDataStore(allObjects, "DataStore"));
}

TEST(DataStoreTest, Can_Update_Table) {
    std::vector<IObject*> allObjects(15);
    std::for_each(allObjects.begin(), allObjects.end(), [](auto& elem) {elem = new DummyObject("dummy");} );
    TDataStore store(allObjects, "DataStore");
    ASSERT_NO_THROW(store.AddAllProperties(0ull));
}
