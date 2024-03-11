#include "CachePlotComponent.h"

void engine::CachePlotComponent::Render() const
{
	RenderWindowEx1();
	RenderWindowEx2();
}

void engine::CachePlotComponent::RenderWindowEx1() const
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

	if (!ImGui::Begin("Exercise 1"))
	{
		ImGui::End();
		return;
	}

	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
	ImGui::Spacing();

	static int sampleCount = 10;
	ImGui::InputInt("# samples", &sampleCount);

	static bool clicked{};
	if (ImGui::Button("Trash the cache"))
	{
		clicked = true;
		GenerateIntData(sampleCount);
	}

	if (clicked)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_StepSizes;
		conf.values.ys = m_IntTimes;
		conf.values.count = 11;
		conf.values.color = ImColor(0, 0, 255);
		conf.scale.min = m_IntTimes[10];
		conf.scale.max = m_IntTimes[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("Int", conf);
	}

	ImGui::PopItemWidth();
	ImGui::End();
}

void engine::CachePlotComponent::RenderWindowEx2() const
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

	if (!ImGui::Begin("Exercise 2"))
	{
		ImGui::End();
		return;
	}

	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
	ImGui::Spacing();

	static int sampleCount = 10;
	ImGui::InputInt("# samples", &sampleCount);

	static bool clickedGO{};
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		clickedGO= true;
		GenerateGOData(sampleCount);
	}

	if (clickedGO)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_StepSizes;
		conf.values.ys = m_GOTimes;
		conf.values.count = 11;
		conf.values.color = ImColor(0, 255, 0);
		conf.scale.min = m_GOTimes[10];
		conf.scale.max = m_GOTimes[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = false;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("Int", conf);
	}

	static bool clickedGOAlt;
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		clickedGOAlt = true;
		GenerateGOAltData(sampleCount);
	}

	if (clickedGOAlt)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_StepSizes;
		conf.values.ys = m_GOAltTimes;
		conf.values.count = 11;
		conf.values.color = ImColor(255, 0, 0);
		conf.scale.min = m_GOAltTimes[10];
		conf.scale.max = m_GOAltTimes[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = false;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("Int", conf);
	}

	if (clickedGO && clickedGOAlt)
	{
		static const float* y_data[] = { m_GOTimes, m_GOAltTimes };
		static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };
		ImGui::PlotConfig conf;
		conf.values.xs = m_StepSizes;
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.count = 11;
		conf.values.colors = colors;
		conf.scale.min = m_GOAltTimes[10];
		conf.scale.max = m_GOTimes[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = false;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		ImGui::Plot("Int", conf);
	}

	ImGui::PopItemWidth();
	ImGui::End();
}

void engine::CachePlotComponent::GenerateIntData(const int sampleSize) const
{
	std::vector<int>arr(int(pow(2, 23)));
	std::fill(arr.begin(), arr.end(), 1);
	int idx{};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<long long> times;

		for (int repeat{}; repeat < sampleSize; repeat++)
		{
			const auto startT{ std::chrono::high_resolution_clock::now() };

			for (int i = 0; i < int(arr.size()); i += stepsize)
			{
				arr[i] *= 2;
			}

			const auto diffT = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			times.push_back(diffT);
		}

		std::sort(times.begin(), times.end());
		if (times.size() >= 3)
		{
			times.erase(times.begin());
			times.erase(times.end() - 1);
		}

		m_IntTimes[idx] = static_cast<float>(std::accumulate(times.begin(), times.end(), 0LL)) / times.size();
		++idx;
	}

	arr.clear();
}

void engine::CachePlotComponent::GenerateGOData(const int sampleSize) const
{
	std::vector<GameObject3D>arr(int(pow(2, 22)));
	std::fill(arr.begin(), arr.end(), GameObject3D());
	int idx{};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<long long> times;

		for (int repeat{}; repeat < sampleSize; repeat++)
		{
			const auto startT{ std::chrono::high_resolution_clock::now() };

			for (int i = 0; i < int(arr.size()); i += stepsize)
			{
				arr[i].ID *= 2;
			}

			const auto diffT = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			times.push_back(diffT);
		}

		std::sort(times.begin(), times.end());
		if (times.size() >= 3)
		{
			times.erase(times.begin());
			times.erase(times.end() - 1);
		}

		m_GOTimes[idx] = static_cast<float>(std::accumulate(times.begin(), times.end(), 0LL)) / times.size();
		++idx;
	}

	arr.clear();
}

void engine::CachePlotComponent::GenerateGOAltData(const int sampleSize) const
{
	std::vector<GameObject3DAlt>arr(int(pow(2, 22)));
	std::fill(arr.begin(), arr.end(), GameObject3DAlt());
	int idx{};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<long long> times;

		for (int repeat{}; repeat < sampleSize; repeat++)
		{
			const auto startT{ std::chrono::high_resolution_clock::now() };

			for (int i = 0; i < int(arr.size()); i += stepsize)
			{
				arr[i].ID *= 2;
			}

			const auto diffT = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startT).count();
			times.push_back(diffT);
		}

		std::sort(times.begin(), times.end());
		if (times.size() >= 3)
		{
			times.erase(times.begin());
			times.erase(times.end() - 1);
		}

		m_GOAltTimes[idx] = static_cast<float>(std::accumulate(times.begin(), times.end(), 0LL)) / times.size();
		++idx;
	}

	arr.clear();
}
