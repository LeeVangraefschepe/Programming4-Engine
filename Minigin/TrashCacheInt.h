#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TrashCacheInt final : public BaseComponent
	{
	public:
		explicit TrashCacheInt(GameObject* pGameObject) : BaseComponent(pGameObject){}
		~TrashCacheInt() override;
		void Render() override;

		TrashCacheInt(const TrashCacheInt& other) = delete;
		TrashCacheInt(TrashCacheInt&& other) = delete;
		TrashCacheInt& operator=(const TrashCacheInt& other) = delete;
		TrashCacheInt& operator=(TrashCacheInt&& other) = delete;
	private:
		void TrashCacheTest();

		bool m_isCalculating{ false };
		int m_samples{ 10 };
		int m_progress{};
		const float** m_groupedData{nullptr};
		std::vector<float> m_times{};
		std::vector<float> m_expectedTimes{};
	};
}