#include <NGIN/Util/UUID.hpp>
#include <iomanip>
#include <random>
#include <sstream>
namespace NGIN::Util
{
    UUID::UUID()
        : uuid(GenerateUUID())
    {
    }

    UUID::UUID(IDType uuid)
        : uuid(uuid)
    {
    }

    String UUID::ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << uuid;
        return ss.str();
    }

    Bool UUID::operator==(const UUID& other) const
    {
        return uuid == other.uuid;
    }

    Bool UUID::operator!=(const UUID& other) const
    {
        return uuid != other.uuid;
    }

    UUID::IDType UUID::GenerateUUID()
    {
        thread_local std::random_device rd;
        thread_local std::mt19937_64 generator(rd());
        thread_local std::uniform_int_distribution<IDType> distribution;
        return distribution(generator);
    }
}// namespace NGIN::Util