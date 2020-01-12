#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

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
    int type = 0;
    std::string xmlFile = "";

    if (argc >= 2)
      type = atoi(argv[1]);

    if (argc >= 3)
      xmlFile = argv[2];

    TWorkManager WorkManager(type, xmlFile, 1000, 0.5, -1.0, 1000);//60*60*24*30);

    WorkManager.Start();

    _getch();
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