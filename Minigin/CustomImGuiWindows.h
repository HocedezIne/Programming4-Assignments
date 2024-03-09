#pragma once
#include <imgui.h>
#include <imgui_plot.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr size_t buf_size = 512;
static float x_data[buf_size];
static float y_data1[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];

void generate_data() {
	constexpr float sampling_freq = 44100;
	constexpr float freq = 500;
	for (size_t i = 0; i < buf_size; ++i) {
		const float t = i / sampling_freq;
		x_data[i] = t;
		const float arg = float(2 * M_PI * freq * t);
		y_data1[i] = sin(arg);
		y_data2[i] = y_data1[i] * -0.6f + sinf(2 * arg) * 0.4f;
		y_data3[i] = y_data2[i] * -0.6f + sinf(3 * arg) * 0.4f;
	}
}

void ShowExercise1Window()
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

	static int clicked = 0;
	if (ImGui::Button("Trash the cache")) ++clicked;
	if (clicked & 1)
	{
		ImGui::Text("Wait for it...");
	}

	if (clicked > 0)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = new float[3] {0.5f, 0.3f, 0.4f};
		conf.values.ys = new float[3] {1.f,2.f,3.f};
		conf.values.count = 3;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.tooltip.show = false;
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(400, 400);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	ImGui::PopItemWidth();
	ImGui::End();
}

void ShowExercise2Window()
{
	static const float* y_data[] = { y_data1, y_data2, y_data3 };
	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.count = buf_size;
	conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 3;
	conf.values.colors = colors;
	conf.scale.min = -1;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(buf_size, 200);
	ImGui::Plot("plot1", conf);

	// Draw second plot with the selection
	// reset previous values
	conf.values.ys_list = nullptr;
	conf.selection.show = false;
	// set new ones
	conf.values.ys = y_data3;
	conf.values.offset = selection_start;
	conf.values.count = selection_length;
	conf.line_thickness = 2.f;
	ImGui::Plot("plot2", conf);

	ImGui::End();
}