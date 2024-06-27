#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/String.hpp>

namespace NGIN::IO
{
    /// @brief Cross-platform path manipulation
    /// @details This class provides a platform-independent way to handle filesystem paths.
    /// It includes methods to manipulate, normalize, and validate paths.
    /// Paths can be either absolute or relative:
    /// - Absolute paths start from the root of the filesystem. Examples include /home/user on Unix-like systems or C:\Users\user on Windows.
    /// - Relative paths are relative to another path and do not start with a drive letter or a separator. Examples include ./Foo/Bar or Foo/Bar/.
    ///
    /// Paths can represent either directories or files:
    /// - A directory path ends with a separator.
    /// - A file path does not end with a separator.
    class NGIN_API Path : public Stringifiable
    {
    public:
        /// @brief Default constructor
        Path() = default;

        /// @brief Constructor from const char*
        /// @param path The C-string path
        Path(const char* path);

        /// @brief Constructor from std::string_view
        /// @param path The string view path
        Path(std::string_view path);

        /// @brief Copy constructor
        /// @param other The other Path object to copy from
        Path(const Path& other);

        /// @brief Move constructor
        /// @param other The other Path object to move from
        Path(Path&& other) noexcept;

        /// @brief Move constructor from String
        /// @param other The String object to move from
        Path(String&& other) noexcept;

        /// @brief Default destructor
        ~Path() = default;

        /// @brief Equality operator
        /// @param other The other Path object to compare with
        /// @return True if paths are equal, false otherwise
        bool operator==(const Path& other) const;

        /// @brief Inequality operator
        /// @param other The other Path object to compare with
        /// @return True if paths are not equal, false otherwise
        bool operator!=(const Path& other) const;

        /// @brief Copy assignment operator
        /// @param other The other Path object to copy from
        /// @return Reference to this Path object
        Path& operator=(const Path& other);

        /// @brief Move assignment operator
        /// @param other The other Path object to move from
        /// @return Reference to this Path object
        Path& operator=(Path&& other) noexcept;

        /// @brief Assignment operator from std::string_view
        /// @param path The string view path
        /// @return Reference to this Path object
        Path& operator=(std::string_view path);

        /// @brief Assignment operator from const char*
        /// @param path The C-string path
        /// @return Reference to this Path object
        Path& operator=(const char* path);

        /// @brief Concatenate two paths
        /// @param other The other Path object to concatenate with
        /// @return New Path object
        Path operator+(const Path& other) const;

        /// @brief Concatenate a path with a string view
        /// @param other The string view path to concatenate with
        /// @return New Path object
        Path operator+(std::string_view other) const;

        /// @brief Append and assign another path
        /// @param other The other Path object to append
        /// @return Reference to this Path object
        Path& operator+=(const Path& other);

        /// @brief Append and assign a string view path
        /// @param other The string view path to append
        /// @return Reference to this Path object
        Path& operator+=(std::string_view other);

        /// @brief Append and assign a const char* path
        /// @param other The const char* path to append
        /// @return Reference to this Path object
        Path& operator+=(const char* other);

        /// @brief Combine two paths using a separator
        /// @param other The other Path object to combine with
        /// @return New Path object
        Path operator/(const Path& other) const;

        /// @brief Combine a path with a string view using a separator
        /// @param other The string view path to combine with
        /// @return New Path object
        Path operator/(std::string_view other) const;

        /// @brief Combine and assign another path using a separator
        /// @param other The other Path object to combine with
        /// @return Reference to this Path object
        Path& operator/=(const Path& other);

        /// @brief Combine and assign a string view path using a separator
        /// @param other The string view path to combine with
        /// @return Reference to this Path object
        Path& operator/=(std::string_view other);

        /// @brief Combine and assign a const char* path using a separator
        /// @param other The const char* path to combine with
        /// @return Reference to this Path object
        Path& operator/=(const char* other);

        /// @brief Conversion to bool
        /// @return True if path is not empty, false otherwise
        explicit operator bool() const;

        /// @brief Append another path
        /// @param path The other Path object to append
        void Append(const Path& path);

        /// @brief Append a string view path
        /// @param path The string view path to append
        void Append(std::string_view path);

        /// @brief Append a const char* path
        /// @param path The const char* path to append
        void Append(const char* path);

        /// @brief Clear the path
        void Clear();

        /// @brief Normalize the path
        void Normalize();

        /// @brief Set the path from another Path object
        /// @param path The other Path object to set from
        void Set(const Path& path);

        /// @brief Set the path from a string view
        /// @param path The string view path to set from
        void Set(std::string_view path);

        /// @brief Set the path from a const char*
        /// @param path The const char* path to set from
        void Set(const char* path);

        /// @brief Get a normalized copy of the path
        /// @return Normalized Path object
        Path GetNormalized() const;

        /// @brief Check if the path is valid
        /// @return True if path is valid, false otherwise
        bool IsValid() const;

        /// @brief Check if the path is empty
        /// @return True if path is empty, false otherwise
        bool IsEmpty() const;

        /// @brief Check if the path is absolute
        /// @return True if path is absolute, false otherwise
        bool IsAbsolute() const;

        /// @brief Check if the path is relative
        /// @return True if path is relative, false otherwise
        bool IsRelative() const;

        /// @brief Check if the path is root
        /// @return True if path is root, false otherwise
        bool IsRoot() const;

        /// @brief Check if the path is a directory
        /// @return True if path is a directory, false otherwise
        bool IsDirectory() const;

        /// @brief Check if the path is a file
        /// @return True if path is a file, false otherwise
        bool IsFile() const;

        /// @brief Get the path as a String object
        /// @return The path as a String object
        const String& GetPathString() const;

        /// @brief Convert the path to a string
        /// @return The path as a string
        String ToString() const override;

        /// @brief Get the current path
        /// @return The current Path object
        static Path Current();

        /// @brief The path separator
        constexpr static char SEPARATOR     = '/';
        constexpr static char ALT_SEPARATOR = '\\';

    private:
        /// @brief The internal string representation of the path
        String path;
    };
}// namespace NGIN::IO
