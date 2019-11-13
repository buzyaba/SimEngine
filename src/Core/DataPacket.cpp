#include "Core/DataPacket.h"

TDataPacket::TDataPacket(int* data, int size)
{
}

TDataPacket::TDataPacket(double* data, int size)
{
}

TDataPacket::TDataPacket(char* data, int size)
{
}

TDataPacket::TDataPacket(const TDataPacket& packet)
{
}

TDataPacket::~TDataPacket()
{
}

char* TDataPacket::GetData()
{
  return nullptr;
}

int TDataPacket::GetSize()
{
  return 0;
}

void TDataPacket::Setdata(char*)
{
}

void TDataPacket::SetSize(int)
{
}

int* TDataPacket::GetInts()
{
  return nullptr;
}

double* TDataPacket::GetDoubles()
{
  return nullptr;
}
