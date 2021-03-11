#pragma once
#include <vector>
#include <algorithm>
#include <cstring>

/// Класс описывающий передаваемое сообщение
class TDataPacket
{
protected:
  /// массив данных
  char* data;
  /// размер массива данных в байтах
  std::size_t size;
public:

  template<typename T>
  TDataPacket(T* _data, std::size_t _size) {
    size = _size * sizeof(T);
    data = new char[size];
    std::memcpy(data, _data, size);
  }

  TDataPacket(std::size_t _size): size(_size) {
    data = new char[size];
  }

  TDataPacket(const TDataPacket& packet): size(packet.size) {
    data = new char[size];
    std::memcpy(data, packet.data, size);
  }

  ~TDataPacket() {
    if (data)
      delete[] data;
  }

  template<typename T>
  T* GetData() {
    return reinterpret_cast<T*>(data);
  }

  std::size_t GetSize() { return size; }

  void SetSize(const std::size_t _size) {
    if (size != _size) {
      char* tmp = new char[std::min(size, _size)];
      std::memcpy(tmp, data, std::min(size, _size));
      if (data != nullptr)
        delete[] data;
      data = tmp;
      size = _size;
    }
  }

};