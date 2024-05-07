
export module NGIN.Util:TimeUtil;

export import NGIN.Types;
import std;
namespace NGIN::Util
{
    export String GetCurrentFormattedTime()
    {
        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);
        const std::tm tm = *std::localtime(&time);

        // Use a static buffer if this is performance-critical and thread safety is not a concern
        static thread_local char time_buffer[20];// Enough space for "%Y-%m-%d %H:%M:%S"
        std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &tm);

        return String(time_buffer);
    }

}// namespace NGIN::Util
