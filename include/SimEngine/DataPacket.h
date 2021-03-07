#pragma once
#include <vector>
#include <algorithm>

/// Класс описывающий передоваемое сообщение
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
    std::memcpy(data, _data, size);
  }

  TDataPacket(std::size_t _size): data(nullptr), size(_size) {}

  TDataPacket(const TDataPacket& packet): size(packet.size) {
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
      char* tmp;
      std::memcpy(tmp, data, std::min(size, _size));
      if (data != nullptr)
        delete[] data;
      data = tmp;
      size = _size;
    }
  }

};