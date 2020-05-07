#include "BasicExamples/DataPacket.h"
#include <algorithm>

TDataPacket::TDataPacket(int _size) : data(nullptr), size(0)
{
  if (_size <= 0)
  {
    throw - 1;
  }
  else
  {
    data = new char[_size];
    size = _size;
  }
}

TDataPacket::TDataPacket(int* _data, int _size) : data(nullptr), size(0)
{
  if ((_size <= 0) || (_data == nullptr))
  {
    throw -1;
  }
  else
  {
    int* tmp = new int[_size];
    size = _size * sizeof(int);
    for (int i = 0; i < _size; i++)
    {
      tmp[i] = _data[i];
    }
    data = (char*)tmp;
  }
}

TDataPacket::TDataPacket(double* _data, int _size) : data(nullptr), size(0)
{
  if ((_size <= 0) || (_data == nullptr))
  {
    throw - 1;
  }
  else
  {
    double* tmp = new double[_size];
    size = _size * sizeof(double);
    for (int i = 0; i < _size; i++)
    {
      tmp[i] = _data[i];
    }
    data = (char*)tmp;
  }
}

TDataPacket::TDataPacket(char* _data, int _size) : data(nullptr), size(0)
{
  if ((_size <= 0) || (_data == nullptr))
  {
    throw - 1;
  }
  else
  {
    data = new char[_size];
    size = _size;
    for (int i = 0; i < size; i++)
    {
      data[i] = _data[i];
    }

  }
}

TDataPacket::TDataPacket(const TDataPacket& packet)
{
  this->size = packet.size;
  this->data = new char[size];
  for (int i = 0; i < size; i++)
  {
    this->data[i] = packet.data[i];
  }
}

TDataPacket::~TDataPacket()
{
  if (data != nullptr)
  {
    delete[] data;
    data = nullptr;
    size = 0;
  }
}

char* TDataPacket::GetData()
{
  return data;
}

int TDataPacket::GetSize()
{
  return size;
}

void TDataPacket::Setdata(char* _data)
{
  if (size != 0)
  {
    try
    {
      for (int i = 0; i < size; i++)
      {
        data[i] = _data[i];
      }
    }
    catch (...)
    {
      throw - 1;
    }
  }
  else
    throw - 1;
}

void TDataPacket::SetSize(int _size)
{
  if (_size > 0)
  {
    if (size != _size)
    {
      char* tmp = new char[_size];
      for (int i = 0; i < std::min(size, _size); i++)
        tmp[i] = data[i];
      if (data != nullptr)
        delete[] data;
      data = tmp;
      size = _size;
    }
  }
  else
    throw - 1;
}

int* TDataPacket::GetInts()
{
  return (int*)data;
}

double* TDataPacket::GetDoubles()
{
  return (double*)data;
}
