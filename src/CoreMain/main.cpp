#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Core/main.h"

#include "Core/ObjectOfObservation.h"
#include "Core/CoordinateObject.h"
#include "Core/WorkManager.h"

#include "output_system.h"
#include "exception.h"
#include "discpp.h"


int main(int argc, char* argv[])
{
  //std::chrono::milliseconds delta(100);

  //for (int t = 0; t < 50; t++)
  //{
  //  double val = double(rand()) / RAND_MAX * 30.0 + 5;
  //  std::string s = "curl -v -X POST -d \"{\\\"Power\\\": " +
  //    std::to_string(val) +
  //    " }\" http://localhost:8080/api/v1/FISKOaCIWwS5dlpZtL4c/telemetry --header \"Content-Type:application/json\"";
  //  std::system(s.c_str());
  //  std::this_thread::sleep_for(delta);
  //}
  try
  {
    int type = 0;
    std::string xmlScript = "", xmlFile = "";

    if (argc >= 2)
      type = atoi(argv[1]);

    if (argc >= 3)
      xmlScript = argv[2];

    if (argc >= 4)
      xmlFile = argv[3];

    TWorkManager WorkManager(type, xmlScript, xmlFile, 1000, 1.0, -1.0, 1000);//60*60*24*30);

    WorkManager.Start();

    //_getch();
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