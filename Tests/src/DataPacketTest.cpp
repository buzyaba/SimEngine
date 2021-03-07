// #include "gtest/gtest.h"
// #include "SimEngine/DataPacket.h"
// #include <memory>

// TEST(DataPacketTest, Can_Create_Instance_char) {
//     ASSERT_NO_THROW(TDataPacket("data", 5));
// }

// TEST(DataPacketTest, Can_Create_Instance_int) {
//     std::unique_ptr<int> ptr(new int{5});
//     ASSERT_NO_THROW(TDataPacket(ptr.get(), 1));
// }

// TEST(DataPacketTest, Can_Create_Instance_double) {
//     std::unique_ptr<double> ptr(new double{12.13});
//     ASSERT_NO_THROW(TDataPacket(ptr.get(), 1));
// }

// TEST(DataPacketTest, Copying_Constructor) {
//     std::unique_ptr<int> ptr(new int{5});
//     TDataPacket packet(ptr.get(), 1);
//     TDataPacket cp(packet);

//     ASSERT_EQ(*packet.GetData(), *cp.GetData());
// }

// TEST(DataPacketTest, Destructor) {
//     std::unique_ptr<int> ptr(new int{5});
//     TDataPacket* packet = new TDataPacket(ptr.get(), 1);

//     auto data1 = *packet->GetData();
//     auto data2 = packet->GetData();
//     delete packet;

//     ASSERT_NE(data1, *data2);
// }

// TEST(DataPacketTest, Get_Size) {
//     TDataPacket pack("data", 5);

//     ASSERT_EQ(5, pack.GetSize());
// }

// TEST(DataPacketTest, Set_Data) {
//     std::unique_ptr<char> ptr(new char{1});
//     TDataPacket packet(ptr.get(), 1);
    
//     ptr.reset(new char{3});
//     packet.Setdata(ptr.get());


//     ASSERT_EQ(*ptr, *packet.GetData());
// }

// TEST(DataPacketTest, Set_Size) {
//     TDataPacket packet(8);

//     packet.SetSize(16);

//     ASSERT_EQ(16, packet.GetSize());
// }

// TEST(DataPacketTest, Get_Ints) {
//     TDataPacket pack("data", 5);

//     auto data = pack.GetData();

//     ASSERT_EQ(*(int*)data, *pack.GetInts());
// }

// TEST(DataPacketTest, Get_Doubles) {
//     TDataPacket pack("data", 5);

//     auto data = pack.GetData();

//     ASSERT_DOUBLE_EQ(*(double*)data, *pack.GetData<double>());
// }
