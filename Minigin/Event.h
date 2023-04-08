#pragma once
#include <string>

namespace dae
{
    class GameObject;
    class Event final
    {
    public:
        Event() = default;
        explicit Event(const std::string& name) : m_name{ name } {}

        bool IsValid() const { return m_name.length() != 0; }
        const std::string& GetName() const { return m_name; }

        bool operator==(const Event& other) const
        {
            return m_name == other.m_name;
        }
        struct Hash
        {
            std::size_t operator()(const Event& event) const noexcept
            {
                return std::hash<std::string>()(event.GetName());
            }
        };
    private:
        std::string m_name{};
    };
}
template <>
struct std::hash<dae::Event>
{
	std::size_t operator()(const dae::Event& event) const noexcept
	{
		return std::hash<std::string>()(event.GetName());
	}
};