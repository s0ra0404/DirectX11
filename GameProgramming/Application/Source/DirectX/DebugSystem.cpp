#include <string>
#include <windows.h>

#include "DebugSystem.h"

void DebugSystem::Log(const std::wstring& message)
{
	OutputDebugStringW(message.c_str()); // Unicode”Å
}
