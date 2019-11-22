#include <iostream>
#include "Core/main.h"

#include "Core/ObjectOfObservation.h"
#include "Core/CoordinateObject.h"
#include "Core/WorkManager.h"

int main(int argc, char* argv[])
{
  std::cout << "Hello World!\n";
  main0(argc, argv);

  //TCoordinateObject a;
  //IProperties& coordinate = a.GetProperty();
  //coordinate.SetValues({ 20, 25 });
  //a.SetProperty(coordinate); // Не обязательно
  //coordinate.SetValues({ 40, 45 });

  TWorkManager WorkManager;

  WorkManager.Start();

  return 0;
}