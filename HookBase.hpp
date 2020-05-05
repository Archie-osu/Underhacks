#pragma once

namespace nHookBase
{
	bool Hook(char* src, char* dst, int len);

	char* TrampHook(char* src, char* dst, unsigned int len);
}

