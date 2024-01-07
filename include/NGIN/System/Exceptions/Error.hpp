#pragma once
#include <source_location>
#include <stdexcept>
#include <string>
namespace NGIN::System::Exceptions
{

    /// @class Error
    /// @brief Base exception class for NGIN framework.
    /// @details This class serves as the root for all exceptions in NGIN.
    class Error : std::runtime_error
    {
    public:
        /// @brief Constructor for NGINException.
        /// @param message The error message.
        Error(const std::string& message, const std::source_location& location = std::source_location::current());

    private:
        std::source_location location;
    };
}// namespace NGIN::System::Exceptions