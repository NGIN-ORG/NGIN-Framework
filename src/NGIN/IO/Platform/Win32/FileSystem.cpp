#include <NGIN/IO/FileSystem.hpp>
#include <string>
#include <windows.h>

namespace NGIN::IO
{

    // Convert Path to a wide string for Win32 API
    inline std::wstring to_wstring(const Path& path)
    {
        return path.ToWString();
    }

    // Get the status of a path (Win32)
    FSResult FileSystem::Check(const Path& path)
    {
        DWORD attributes = GetFileAttributesW(to_wstring(path).c_str());
        if (attributes == INVALID_FILE_ATTRIBUTES)
        {
            if (GetLastError() == ERROR_ACCESS_DENIED)
            {
                return FSResult::NotAuthorized;
            }
            else if (GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND)
            {
                return FSResult::NotFound;
            }
            else
            {
                return FSResult::UnknownError;
            }
        }
        return FSResult::Exists;
    }

    // Check if the path exists (Win32)
    bool FileSystem::Exists(const Path& path)
    {
        return Check(path) == FSResult::Exists;
    }

    // Check if a specific item within the path exists (Win32)
    bool FileSystem::Exists(const Path& path, std::string_view name)
    {
        Path fullPath = path / name;
        return Exists(fullPath);
    }

    // Create a file or directory at the specified path (Win32)
    FSResult FileSystem::Create(const Path& path, bool canOverride)
    {
        std::wstring wpath = to_wstring(path);
        if (path.IsFile())
        {
            HANDLE fileHandle = CreateFileW(wpath.c_str(), GENERIC_WRITE, 0, NULL, canOverride ? CREATE_ALWAYS : CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fileHandle == INVALID_HANDLE_VALUE)
            {
                return FSResult::UnknownError;
            }
            CloseHandle(fileHandle);
        }
        else if (path.IsDirectory())
        {
            if (!CreateDirectoryW(wpath.c_str(), NULL))
            {
                if (GetLastError() == ERROR_ALREADY_EXISTS && canOverride)
                {
                    RemoveDirectoryW(wpath.c_str());
                    CreateDirectoryW(wpath.c_str(), NULL);
                }
                else
                {
                    return FSResult::UnknownError;
                }
            }
        }
        return FSResult::Exists;
    }

    // Create a file or directory at the specified path with a given name (Win32)
    FSResult FileSystem::Create(const Path& path, std::string_view name, bool canOverride)
    {
        return Create(path / name, canOverride);
    }

    // Copy a file or directory from one path to another (Win32)
    FSResult FileSystem::Copy(const Path& from, const Path& to)
    {
        std::wstring wfrom = to_wstring(from);
        std::wstring wto   = to_wstring(to);
        if (!CopyFileW(wfrom.c_str(), wto.c_str(), FALSE))
        {
            return FSResult::UnknownError;
        }
        return FSResult::Exists;
    }

    // Delete a file or directory at the specified path (Win32)
    bool FileSystem::Delete(const Path& path)
    {
        std::wstring wpath = to_wstring(path);
        if (path.IsFile())
        {
            return DeleteFileW(wpath.c_str());
        }
        else if (path.IsDirectory())
        {
            return RemoveDirectoryW(wpath.c_str());
        }
        return false;
    }

    // Delete a specific item within the path (Win32)
    bool FileSystem::Delete(const Path& path, std::string_view name)
    {
        return Delete(path / name);
    }

}// namespace NGIN::IO
