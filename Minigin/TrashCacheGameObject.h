#pragma once
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	class TrashCacheGameObject final : public BaseComponent
	{
		public:
			explicit TrashCacheGameObject(GameObject* pGameObject) : BaseComponent(pGameObject) {}
			~TrashCacheGameObject() override;
			void Render() override;
		
			TrashCacheGameObject(const TrashCacheGameObject& other) = delete;
			TrashCacheGameObject(TrashCacheGameObject&& other) = delete;
			TrashCacheGameObject& operator=(const TrashCacheGameObject& other) = delete;
			TrashCacheGameObject& operator=(TrashCacheGameObject&& other) = delete;
		private:
			void TrashCacheTest3D();
			void TrashCacheTest3DP();

			struct Transform
			{
				float matrix[16]{};
			};
			class GameObject3D
			{
			public:
				Transform transform = Transform{};
				int id{};
			};
			class GameObject3DP final
			{
			public:
				Transform* transform = new Transform{};
				~GameObject3DP() { delete transform; }
				int id{};
			};

			bool m_isCalculating3D{ false }, m_isCalculating3DP{ false };
			int m_samples{ 10 }, m_progress{};
			const float** m_groupedData{ nullptr };
			std::vector<float> m_times3D{};
			std::vector<float> m_times3DP{};
	};
	
}

