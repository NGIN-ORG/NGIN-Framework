#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/IO/Path.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <string_view>

namespace NGIN::IO
{
    enum class FSResult : UInt32
    {
        Exists,       ///< Path exists.
        NotFound,     ///< Path not found.
        NotAuthorized,///< Access to the path is not authorized.
        UnknownError  ///< An unknown error occurred.
    };

    class NGIN_API FileSystem
    {
    public:
        // Delete the constructor and destructor to prevent instantiation
        FileSystem()  = delete;
        ~FileSystem() = delete;

        /// @brief Get the status of a path (file or directory).
        /// @param path The path to check.
        /// @return FSResult indicating the result of the check.
        static FSResult Check(const Path& path);

        /// @brief Check if the path exists.
        /// @param path The path to the file or directory.
        /// @return True if the path exists, false otherwise.
        static bool Exists(const Path& path);

        /// @brief Check if a specific item within the path exists.
        /// @param path The path to the directory.
        /// @param name The name of the file or directory to check within the path.
        /// @return True if the item exists, false otherwise.
        static bool Exists(const Path& path, std::string_view name);

        /// @brief Create a file or directory at the specified path.
        /// @param path The path to the object. The last component in the path is what is being created.
        /// @param canOverride If true, allows overwriting an existing file or directory.
        /// @return FSResult indicating the result of the creation operation.
        static FSResult Create(const Path& path, bool canOverride);

        /// @brief Create a file or directory at the specified path with a given name.
        /// @param path The path to the directory where the object will be created.
        /// @param name The name of the file or directory to create.
        /// @param canOverride If true, allows overwriting an existing file or directory.
        /// @return FSResult indicating the result of the creation operation.
        static FSResult Create(const Path& path, std::string_view name, bool canOverride);

        /// @brief Copy a file or directory from one path to another.
        /// @param from The source path.
        /// @param to The destination path.
        /// @return FSResult indicating the result of the copy operation.
        static FSResult Copy(const Path& from, const Path& to);

        /// @brief Delete a file or directory at the specified path.
        /// @param path The path to the file or directory to delete.
        /// @return True if the deletion was successful, false otherwise.
        static bool Delete(const Path& path);

        /// @brief Delete a specific item within the path.
        /// @param path The path to the directory.
        /// @param name The name of the file or directory to delete within the path.
        /// @return True if the deletion was successful, false otherwise.
        static bool Delete(const Path& path, std::string_view name);
    };
}// namespace NGIN::IO
