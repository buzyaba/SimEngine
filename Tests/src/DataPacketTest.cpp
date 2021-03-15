#include "gtest/gtest.h"
#include "SimEngine/DataPacket.h"
#include <memory>

TEST(DataPacketTest, Can_Create_Instance_char) {
    ASSERT_NO_THROW(TDataPacket("data", 5));
}

TEST(DataPacketTest, Can_Create_Instance_int) {
    std::unique_ptr<int> ptr(new int{5});
    ASSERT_NO_THROW(TDataPacket(ptr.get(), 1));
}

TEST(DataPacketTest, Can_Create_Instance_double) {
    std::unique_ptr<double> ptr(new double{12.13});
    ASSERT_NO_THROW(TDataPacket(ptr.get(), 1));
}

TEST(DataPacketTest, Copying_Constructor) {
    std::unique_ptr<int> ptr(new int{5});
    TDataPacket packet(ptr.get(), 1);
    TDataPacket cp(packet);

    ASSERT_EQ(*packet.GetData<int>(), *cp.GetData<int>());
}

TEST(DataPacketTest, Get_Size) {
    TDataPacket pack("data", 5);

    ASSERT_EQ(5, pack.GetSize());
}

TEST(DataPacketTest, Set_Size) {
    TDataPacket packet(8);

    packet.SetSize(16);

    ASSERT_EQ(16, packet.GetSize());
}
