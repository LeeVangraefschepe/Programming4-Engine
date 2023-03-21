
#pragma once
#include "TrashCacheGameObject.h"
#include <chrono>
#include "imgui_plot.h"

dae::TrashCacheGameObject::~TrashCacheGameObject()
{
	delete[] m_groupedData;
}

void dae::TrashCacheGameObject::Render()
{
	//Create window
	ImGui::SetNextWindowSize(ImVec2(500, 500));
	if (ImGui::Begin("Exercise 3"))
	{
		if (!m_isCalculating3D && !m_isCalculating3DP)
		{
			//UI for input and action call
			ImGui::InputInt("##InputValue", &m_samples);
			ImGui::SameLine();
			ImGui::Text("#samples");
			if (ImGui::Button("Trash the cache with GameObject3D", ImVec2(400, 30)))
			{
				delete[] m_groupedData;
				m_groupedData = nullptr;
				m_isCalculating3D = true;
				std::thread t(&TrashCacheGameObject::TrashCacheTest3D, this);
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
		if (m_times3D.empty() == false)
		{
			//Graph with just the time data
			ImGui::PlotConfig conf;
			conf.values.ys = m_times3D.data();
			conf.values.count = static_cast<int>(m_times3D.size());
			conf.scale.min = 0.f;
			conf.scale.max = m_times3D[0];
			conf.tooltip.show = false;
			conf.values.color = ImColor(255, 0, 0);
			conf.tooltip.format = "x=%.f, y=%.f";
			conf.grid_x.show = false;
			conf.grid_y.show = false;
			conf.frame_size = ImVec2(250, 100);
			conf.line_thickness = 2.f;
			ImGui::Plot("plot", conf);
		}
		if (!m_isCalculating3D && !m_isCalculating3DP && ImGui::Button("Trash the cache with GameObject3DP", ImVec2(400, 30)))
		{
			delete[] m_groupedData;
			m_groupedData = nullptr;
			m_isCalculating3DP = true;
			std::thread t(&TrashCacheGameObject::TrashCacheTest3DP, this);
			t.detach();
		}
		if (m_times3DP.empty() == false)
		{
			//Graph with just the time data
			ImGui::PlotConfig conf;
			conf.values.ys = m_times3DP.data();
			conf.values.count = static_cast<int>(m_times3DP.size());
			conf.scale.min = 0.f;
			conf.values.color = ImColor(0, 255, 0);
			conf.scale.max = m_times3DP[0];
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
			ImGui::Text("Combined:");
			ImGui::PlotConfig conf;
			conf.values.ys_list = m_groupedData;
			conf.values.ys_count = 2;
			const ImU32 colors[] = { ImColor(255, 0, 0), ImColor(0, 255, 0) };
			conf.values.colors = colors;
			conf.values.count = static_cast<int>(m_times3D.size());
			conf.scale.min = 0.f;
			conf.scale.max = m_times3D[0];
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

void dae::TrashCacheGameObject::TrashCacheTest3D()
{
	constexpr int size{ 1000000 };
	m_times3D.clear();
	m_progress = 0;

	if (m_samples <= 0)
	{
		return;
	}

	constexpr int amountOfTests{ 10 };
	constexpr int maxAmountSteps{ 1024 };
	m_times3D.resize(amountOfTests+1);
	const auto buffer = new GameObject3D[size] {};

	for (int sample{}; sample < m_samples; ++sample)
	{
		int id{};
		for (int stepsize = 1; stepsize <= maxAmountSteps; stepsize *= 2)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i{}; i < size; i += stepsize)
			{
				buffer[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_times3D[id] += static_cast<float>(elapsedTime) / 1000.f;
			++id;
		}
		++m_progress;
	}
	delete[] buffer;

	for (auto& element : m_times3D)
	{
		element /= static_cast<float>(amountOfTests);
	}

	m_isCalculating3D = false;

	if (static_cast<int>(m_times3DP.size()) == amountOfTests + 1 && static_cast<int>(m_times3D.size()) == amountOfTests + 1)
	{
		m_groupedData = new const float* [2] {m_times3D.data(), m_times3DP.data()};
	}
}
void dae::TrashCacheGameObject::TrashCacheTest3DP()
{
	constexpr int size{ 1000000 };
	m_times3DP.clear();
	m_progress = 0;

	if (m_samples <= 0)
	{
		return;
	}

	constexpr int amountOfTests{ 10 };
	constexpr int maxAmountSteps{ 1024 };
	m_times3DP.resize(amountOfTests+1);
	const auto buffer = new GameObject3DP[size]{};

	for (int sample{}; sample < m_samples; ++sample)
	{
		int id{};
		for (int stepsize = 1; stepsize <= maxAmountSteps; stepsize *= 2)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (int i{}; i < size; i += stepsize)
			{
				buffer[i].id *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			m_times3DP[id] += static_cast<float>(elapsedTime) / 1000.f;
			++id;
		}
		++m_progress;
	}
	delete[] buffer;

	for (auto& element : m_times3DP)
	{
		element /= static_cast<float>(amountOfTests);
	}

	m_isCalculating3DP = false;

	if (static_cast<int>(m_times3DP.size()) == amountOfTests + 1 && static_cast<int>(m_times3D.size()) == amountOfTests + 1)
	{
		m_groupedData = new const float* [2] {m_times3D.data(), m_times3DP.data()};
	}
}