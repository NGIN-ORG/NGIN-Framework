#include <NGIN/Containers/Vector.hpp>
#include <NGIN/IO/Path.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <windows.h>

namespace NGIN::IO
{

    Path::Path(const char* path)
        : path(path)
    {
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
    }

    Path::Path(std::string_view path)
        : path(String(path))
    {
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
    }

    Path::Path(const Path& other)
        : path(other.path)
    {}

    Path::Path(Path&& other) noexcept
        : path(std::move(other.path)) {}

    Path::Path(String&& other) noexcept
        : path(std::move(other))
    {
        std::replace(path.begin(), path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
    }
    // Equality operator
    bool Path::operator==(const Path& other) const
    {
        return path == other.path;
    }

    // Inequality operator
    bool Path::operator!=(const Path& other) const
    {
        return !(*this == other);
    }

    // Assignment operator
    Path& Path::operator=(const Path& other)
    {
        if (this != &other)
        {
            path = other.path;
        }
        return *this;
    }

    // Move assignment operator
    Path& Path::operator=(Path&& other) noexcept
    {
        if (this != &other)
        {
            path = std::move(other.path);
        }
        return *this;
    }

    // Assignment from std::string_view
    Path& Path::operator=(std::string_view path)
    {
        this->path = path;
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
        return *this;
    }

    Path& Path::operator=(const char* path)
    {
        this->path = path;
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
        return *this;
    }

    // Concatenation operator
    Path Path::operator+(const Path& other) const
    {
        Path newPath = *this;
        newPath.Append(other);
        return newPath;
    }

    // Concatenation operator
    Path Path::operator+(std::string_view other) const
    {
        Path newPath = *this;
        newPath.Append(other);
        return newPath;
    }

    // Concatenation assignment operator
    Path& Path::operator+=(const Path& other)
    {
        this->Append(other);
        return *this;
    }

    // Concatenation assignment operator
    Path& Path::operator+=(std::string_view other)
    {
        this->Append(other);
        return *this;
    }

    Path& Path::operator+=(const char* other)
    {
        this->Append(other);
        return *this;
    }

    // Append operator
    Path Path::operator/(const Path& other) const
    {
        Path newPath = *this;
        newPath.Append(other);
        return newPath;
    }


    // Append operator
    Path Path::operator/(std::string_view other) const
    {
        Path newPath = *this;
        newPath.Append(other);
        return newPath;
    }

    // Append assignment operator
    Path& Path::operator/=(const Path& other)
    {
        this->Append(other);
        return *this;
    }

    // Append assignment operator
    Path& Path::operator/=(std::string_view other)
    {
        this->Append(other);
        return *this;
    }

    Path& Path::operator/=(const char* other)
    {
        this->Append(other);
        return *this;
    }

    // Conversion to bool
    Path::operator bool() const
    {
        return !path.empty();
    }

    // Append a path
    void Path::Append(const Path& path)
    {
        if (path.IsAbsolute())
            throw std::runtime_error("Can't append with an absolute path");

        this->path.reserve(this->path.size() + 1 + path.path.size());

        if (!this->path.empty() && this->path.back() != Path::SEPARATOR)
            this->path += Path::SEPARATOR;
        this->path += path.path;
    }

    // Append a path
    void Path::Append(std::string_view path)
    {
        Path appendPath {path};
        if (appendPath.IsAbsolute())
            throw std::runtime_error("Can't append with an absolute path");

        this->path.reserve(this->path.size() + 1 + appendPath.path.size());

        if (!this->path.empty() && this->path.back() != Path::SEPARATOR)
            this->path += Path::SEPARATOR;
        this->path += appendPath.path;
    }

    void Path::Append(const char* path)
    {
        Path appendPath {path};
        if (appendPath.IsAbsolute())
            throw std::runtime_error("Can't append with an absolute path");

        this->path.reserve(this->path.size() + 1 + appendPath.path.size());

        if (!this->path.empty() && this->path.back() != Path::SEPARATOR)
            this->path += Path::SEPARATOR;
        this->path += appendPath.path;
    }

    // Clear the path
    void Path::Clear()
    {
        path.clear();
    }

    void Path::Normalize()
    {
        if (path.empty())
            return;

        // Split the path by the separator
        Vector<String> parts;
        auto start = path.begin();
        auto end   = path.end();


        while (start != end)
        {
            // Find the next separator
            auto next = std::find(start, end, Path::SEPARATOR);

            // Extract the part
            String item(start, next);

            if (item == "..")
            {
                // Pop the last valid part if not empty and not ".."
                if (!parts.empty() && parts.back() != "..")
                {
                    const String& back = parts.back();

                    if ((back.size() != 2) || !std::isupper(back[0]) || !(back[1] == ':'))
                        parts.pop_back();
                }
                else//Must be relative
                {
                    parts.push_back(item);
                }
            }
            else if (item != "." && !item.empty())
            {
                parts.push_back(item);
            }

            // Move to the next part
            if (next != end)
                start = next + 1;
            else
                start = next;
        }

        String normalizedPath;

        //Resolve absolute / to system drive
        if (path.at(0) == Path::SEPARATOR)
        {
            char systemDirectory[MAX_PATH];
            UINT result = GetSystemDirectory(systemDirectory, MAX_PATH);
            if (result == 0)
            {
                // Handle error
                throw std::runtime_error("Failed to get system directory");
            }

            // The drive letter will be the first two characters (e.g., "C:")
            std::string mainDrive(systemDirectory, 2);
            normalizedPath += mainDrive + Path::SEPARATOR;
        }

        for (size_t i = 0; i < parts.size(); ++i)
        {
            normalizedPath += parts[i];
            if (i < parts.size() - 1)
                normalizedPath += Path::SEPARATOR;
        }

        if (path.back() == Path::SEPARATOR)
            normalizedPath += Path::SEPARATOR;

        path = std::move(normalizedPath);
    }

    // Set the path
    void Path::Set(const Path& path)
    {
        this->path = path.path;
    }

    // Set the path
    void Path::Set(std::string_view path)
    {
        this->path = path;
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
    }

    void Path::Set(const char* path)
    {
        this->path = path;
        std::replace(this->path.begin(), this->path.end(), Path::ALT_SEPARATOR, Path::SEPARATOR);
    }

    // Get the normalized path
    Path Path::GetNormalized() const
    {
        Path result(*this);
        result.Normalize();
        return result;
    }

    // Check if the path is valid
    bool Path::IsValid() const
    {
        return !path.empty();
    }

    // Check if the path is empty
    bool Path::IsEmpty() const
    {
        return path.empty();
    }

    // Check if the path is absolute
    bool Path::IsAbsolute() const
    {
        if (path.size() > 0 && (path[0] == Path::SEPARATOR))
            return true;
        if (path.size() >= 3 && std::isupper(path[0]) && path[1] == ':' && path[2] == Path::SEPARATOR)
            return true;
        return false;
    }

    // Check if the path is relative
    bool Path::IsRelative() const
    {
        return !IsAbsolute();
    }

    // Check if the path is the root directory
    bool Path::IsRoot() const
    {
        //C:/
        //Z:/
        if (path.size() == 3 && std::isupper(path[0]) && path[1] == ':' && path[2] == Path::SEPARATOR)
            return true;
        return false;
    }

    // Check if the path is a directory
    bool Path::IsDirectory() const
    {
        return !path.empty() && path.back() == Path::SEPARATOR;
    }

    // Check if the path is a file
    bool Path::IsFile() const
    {
        return !IsDirectory();
    }

    // Check if the path exists
    const String& Path::GetPathString() const
    {
        return this->path;
    }

    // Convert the path to a string
    String Path::ToString() const
    {
        return path;
    }

    // Get the current directory
    Path Path::Current()
    {
        WChar buffer[MAX_PATH];
        GetCurrentDirectoryW(MAX_PATH, buffer);

        // Calculate the number of bytes required for the UTF-8 string
        Size utf8Length = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);

        if (utf8Length == 0)
        {
            // Handle error
            throw std::runtime_error("WideCharToMultiByte failed to calculate the length.");
        }

        String utf8String(utf8Length, 0);

        int result = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, utf8String.data(), utf8Length, nullptr, nullptr);

        if (result == 0)
        {
            // Handle error
            throw std::runtime_error("WideCharToMultiByte failed to convert the string.");
        }

        utf8String.back() = Path::SEPARATOR;

        return Path(std::move(utf8String));
    }

}// namespace NGIN::IO
