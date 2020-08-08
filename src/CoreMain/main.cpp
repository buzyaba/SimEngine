// #include "Core/ObjectOfObservation.h"
// #include "Core/CoordinateObject.h"
// #include "Core/WorkManager.h"

// #include "output_system.h"
// #include "exception.h"

// int main(int argc, char* argv[])
// {
//   try
//   {
//     int type = 0;
//     std::string xmlScript = "", xmlFile = "";

//     if (argc >= 2)
//       type = atoi(argv[1]);

//     if (argc >= 3)
//       xmlScript = argv[2];

//     if (argc >= 4)
//       xmlFile = argv[3];

//     TWorkManager WorkManager(type, xmlScript, xmlFile, 1000, 0.0, -1.0, 1000);//60*60*24*30);

//     WorkManager.Start();

//   }
//   catch (const TException & e)
//   {
//     std::string excFileName = std::string("exception_") + ".txt";
//     e.Print(excFileName.c_str());
//     return 1;
//   }
//   catch (...)
//   {
//     print << "\nUNKNOWN EXCEPTION !!!\n";
//     std::string excFileName = std::string("exception_") + ".txt";
//     TException e("UNKNOWN FILE", -1, "UNKNOWN FUCNTION", "UNKNOWN EXCEPTION");
//     e.Print(excFileName.c_str());
//     return 1;
//   }
//   return 0;
// }
