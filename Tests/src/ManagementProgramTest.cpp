#include "SimEngine/ManagementProgram.h"
#include "Core/MainSet.h"
#include "gtest/gtest.h"

TEST(ManagementProgramTest, Can_Create) {
  ASSERT_NO_THROW(TManagementProgram());
}

TEST(ManagementProgramTest, Can_Create_With_Things) {
    TMainSet *set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml"));
    ASSERT_NO_THROW(TManagementProgram(set->GetThings()));
    free(set);
}

TEST(ManagementProgramTest, Write_To_Table_On_Run) {
    TMainSet *set = TSetFactory::Create(getPath("/Tests/common/MainSet.xml"));
    auto program = TManagementProgram(set->GetThings());
    program.Run();
    auto table = program.GetTable();
    std::vector<std::string> ref_table = { "0", "7.000000", "17.000000", "15.000000 "};
    for (size_t i = 0; i < table.size(); i++)
        ASSERT_EQ(table[0][i], ref_table[i]);
    free(set);
}
