#pragma once
#include "Component.h"
#include <imgui.h>
#include <imgui_plot.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

namespace engine
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

	class CachePlotComponent : public Component, public IRenderable
	{
	public:
		void Render() const override;

		CachePlotComponent(std::shared_ptr<GameObject> pOwner) : Component(pOwner) {};
		~CachePlotComponent() = default;
		CachePlotComponent(const CachePlotComponent& other) = delete;
		CachePlotComponent(CachePlotComponent&& other) = delete;
		CachePlotComponent& operator=(const CachePlotComponent& other) = delete;
		CachePlotComponent& operator=(CachePlotComponent&& other) = delete;

	private:
		void RenderWindowEx1() const;
		void RenderWindowEx2() const;

		void GenerateIntData(const int sampleSize) const;
		void GenerateGOData(const int sampleSize) const;
		void GenerateGOAltData(const int sampleSize) const;

		const float m_StepSizes[11]{ 1.f,2.f,4.f,8.f,16.f,32.f,64.f,128.f,256.f,512.f,1024.f };
		mutable float m_IntTimes[11]{};
		mutable float m_GOTimes[11]{};
		mutable float m_GOAltTimes[11]{};
	};
}