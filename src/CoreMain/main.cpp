#include <iostream>
#include <chrono>
#include <thread>

#include "Core/main.h"

#include "Core/ObjectOfObservation.h"
#include "Core/CoordinateObject.h"
#include "Core/WorkManager.h"

#include "output_system.h"
#include "exception.h"
#include "discpp.h"


int main(int argc, char* argv[])
{
  try
  {
    TWorkManager WorkManager(0, 1000, 0, -1.0, 100);//60*60*24*30);

    WorkManager.Start();
  }
  catch (const TException & e)
  {
    std::string excFileName = std::string("exception_") + ".txt";
    e.Print(excFileName.c_str());
    return 1;
  }
  catch (...)
  {
    print << "\nUNKNOWN EXCEPTION !!!\n";
    std::string excFileName = std::string("exception_") + ".txt";
    TException e("UNKNOWN FILE", -1, "UNKNOWN FUCNTION", "UNKNOWN EXCEPTION");
    e.Print(excFileName.c_str());
    return 1;
  }
  return 0;
}