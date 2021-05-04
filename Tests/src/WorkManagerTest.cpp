#include "gtest/gtest.h"
#include "Core/WorkManager.h"

TEST(WorkManagerTest, Can_Create)
{
    auto presenter = new IGraphicPresenter();
    auto params = TParameters();        
    std::string path_str = getPath("/ConfigFiles/TestConfig.xml");
    char* path = new char[path_str.length() + 1];
    strcpy(path, path_str.c_str());
    std::vector<const char*> options;
    options.push_back("programName");
    options.push_back(path);
    const char** argv = &options.front();
    params.LoadConsoleParameters(2, argv);
    
    ASSERT_NO_THROW(TWorkManager(params, presenter));
    delete presenter;
};

TEST(WorkManagerTest, Can_Start_And_Run)
{
    auto presenter = new IGraphicPresenter();
    auto params = TParameters();        
    std::string path_str = getPath("/ConfigFiles/TestConfig.xml");
    char* path = new char[path_str.length() + 1];
    strcpy(path, path_str.c_str());
    std::vector<const char*> options;
    options.push_back("programName");
    options.push_back(path);
    const char** argv = &options.front();
    params.LoadConsoleParameters(2, argv);
    
    auto wm = TWorkManager(params, presenter);
    
    ASSERT_NO_THROW(wm.Start(););
    delete presenter;
};

