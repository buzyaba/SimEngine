﻿#pragma once
#include "Core/DataPacket.h"

/// Интерфейс запускаемой программы
class IManagementProgram
{
protected:
public:
  virtual void Run() = 0;
};