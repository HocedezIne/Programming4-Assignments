#pragma once
#include <imgui.h>
#include <imgui_plot.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

namespace TrashCache
{
	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class GameObject3D {
	public:
		Transform transform{};
		int ID{ 1 };
	};
	class GameObject3DAlt {
	public:
		Transform* transform{}; // changed this to a pointer
		int ID{ 1 };
	};

	void ShowEx1Window();
	void ShowEx2Window();

	void GenerateIntData(const int sampleSize);
	void GenerateGOData(const int sampleSize);
	void GenerateGOAltData(const int sampleSize);

	static const float m_StepSizes[11]{ 1.f,2.f,4.f,8.f,16.f,32.f,64.f,128.f,256.f,512.f,1024.f };
	static float m_IntTimes[11];
	static float m_GOTimes[11];
	static float m_GOAltTimes[11];
}
