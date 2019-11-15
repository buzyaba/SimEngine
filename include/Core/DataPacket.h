#pragma once
#include <vector>
class TDataPacket
{
protected:
  char* data;
  int size;
public:
  TDataPacket(int* data, int size = 1);
  TDataPacket(double* data, int size = 1);
  TDataPacket(char* data, int size = 1);
  TDataPacket(const TDataPacket& packet);
  ~TDataPacket();

  virtual char* GetData();
  virtual int GetSize();
  virtual void Setdata(char*);
  virtual void SetSize(int);
  virtual int* GetInts();
  virtual double* GetDoubles();
};