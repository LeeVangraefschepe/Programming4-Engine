#pragma once
#include "TrashCacheInt.h"
#include <chrono>
#include "imgui_plot.h"

dae::TrashCacheInt::~TrashCacheInt()
{
	delete[] m_groupedData;
}

void dae::TrashCacheInt::Render()
{
	//Create window
	ImGui::SetNextWindowSize(ImVec2(400, 500));
	if (ImGui::Begin("Exercise 2"))
	{
		if (!m_isCalculating)
		{
			//UI for input and action call
			ImGui::InputInt("##InputValue", &m_samples);
			ImGui::SameLine();
			ImGui::Text("#samples");
			if (ImGui::Button("Trash the cache", ImVec2(200, 30)))
			{
				m_isCalculating = true;
				delete[] m_groupedData;
				m_groupedData = nullptr;
				//TrashCacheTest();
				std::thread t(&TrashCacheInt::TrashCacheTest, this);
				t.detach();
			}
		}
		else
		{
			//UI while calculating
			std::stringstream text{};
			text << "Calculating please standby (" << m_progress << "/" << m_samples << ")";
			ImGui::Text(text.str().c_str());
		}
		if (m_times.empty() == false)
		{
			//Graph with just the time data
			ImGui::PlotConfig conf;
			conf.values.ys = m_times.data();
			conf.values.count = static_cast<int>(m_times.size());
			conf.scale.min = 0.f;
			conf.scale.max = m_times[0];
			conf.tooltip.show = false;
			conf.tooltip.format = "x=%.f, y=%.f";
			conf.grid_x.show = false;
			conf.grid_y.show = false;
			conf.frame_size = ImVec2(250, 100);
			conf.line_thickness = 2.f;
			ImGui::Plot("plot", conf);
		}
		if (m_groupedData)
		{
			//Graph with time data and expected time
			ImGui::Text("Result (RED)\nExpected (GREEN)");
			ImGui::PlotConfig conf;
			conf.values.ys_list = m_groupedData;
			conf.values.ys_count = 2;
			const ImU32 colors[] = { ImColor(255, 0, 0), ImColor(0, 255, 0)};
			conf.values.colors = colors;
			conf.values.count = static_cast<int>(m_expectedTimes.size());
			conf.scale.min = 0.f;
			conf.scale.max = m_expectedTimes[0];
			conf.values.color = ImColor(255, 0, 0);
			conf.tooltip.show = false;
			conf.tooltip.format = "x=%.f, y=%.f";
			conf.grid_x.show = false;
			conf.grid_y.show = false;
			conf.frame_size = ImVec2(250, 100);
			conf.line_thickness = 2.f;
			ImGui::Plot("plot", conf);
		}
	} ImGui::End();
}

void dae::TrashCacheInt::TrashCacheTest()
{
	constexpr int size{ 100000000 };

	m_progress = 0;
	m_times.clear();
	m_expectedTimes.clear();

	if (m_samples <= 0)
	{
		m_isCalculating = false;
		return;
	}

	constexpr int amountOfTests{ 10 };
	constexpr int maxAmountSteps{ 1024 };
	m_times.resize(amountOfTests);
	const auto buffer = new int[size] {};

	for (int sample{}; sample < m_samples; ++sample)
	{
		int id{};
		for (int stepsize = 1; stepsize < maxAmountSteps; stepsize *= 2)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i{}; i < size; i += stepsize)
			{
				buffer[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_times[id] += static_cast<float>(elapsedTime) / 1000.f;
			++id;
		}
		++m_progress;
	}
	delete[] buffer;

	for (auto& element : m_times)
	{
		element /= static_cast<float>(amountOfTests);
	}

	m_isCalculating = false;

	const float maxTime = m_times[0];
	float divide{ 2 };
	m_expectedTimes.push_back(maxTime);
	for (int i{}; i < amountOfTests - 1; ++i)
	{
		m_expectedTimes.push_back(maxTime / divide);
		divide *= 2.f;
	}

	m_groupedData = new const float* [2] {m_times.data(), m_expectedTimes.data()};
}
