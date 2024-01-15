#include <NGIN/Logging/SimpleFormatter.hpp>
#include <NGIN/Meta/EnumTraits.hpp>
#include <NGIN/Util/Format.hpp>
#include <fmt/chrono.h>
/**
 * @brief Extracts the file name from a given full path string.
 *
 * This function looks for the last occurrence of both forward and backward slashes
 * in the given path string, and returns the substring after the last slash.
 * It is cross-platform and accounts for different directory separator conventions.
 *
 * @param fullPath The full path string from which the file name should be extracted.
 * @return A pointer to the character where the file name starts within the fullPath.
 */
inline const char* ExtractFileName(const char* fullPath)
{
    // Find the last backslash, diffrent OS can use diffrent slashes
    const char* fromSlash = strrchr(fullPath, '/');
    const char* fromBackslash = strrchr(fullPath, '\\');

    // Determine which one is the last separator in the path.
    const char* lastSeparator = (fromSlash > fromBackslash) ? fromSlash : fromBackslash;

    return (lastSeparator) ? lastSeparator + 1 : fullPath;
}

namespace NGIN::Logging
{
    String SimpleFormatter::Format(LogLevel level, const std::source_location& source, const String& message)
    {
        return Util::Format("{:%Y-%m-%d %H:%M:%S} | {:>20}:{:<5} | {:<8} | {}",
                            fmt::localtime(std::time(nullptr)),
                            ExtractFileName(source.file_name()),
                            source.line(),
                            Meta::EnumTraits<LogLevel>::ToString(level),
                            message);
    }
}// namespace NGIN::Logging
