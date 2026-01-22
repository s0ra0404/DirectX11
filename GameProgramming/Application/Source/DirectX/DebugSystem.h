#pragma once

class DebugSystem
{

private:
	static inline DebugSystem* s_instance;

	DebugSystem(){}

public:

	// インスタンス作成
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new DebugSystem();
	}
	// インスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// 唯一のインスタンスを取得
	static DebugSystem& GetInstance()
	{
		return *s_instance;
	}

	void Log(const std::wstring& message);
};

// DebugSystemの唯一のインスタンスを簡単に取得するためのマクロ
#define DEBUG DebugSystem::GetInstance()