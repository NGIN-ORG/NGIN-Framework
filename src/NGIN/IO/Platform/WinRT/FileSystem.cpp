#include <NGIN/IO/FileSystem.hpp>
#include <string>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>

namespace NGIN::IO
{

    // Helper function to convert Path to WinRT format
    winrt::hstring to_hstring(const Path& path)
    {
        return winrt::hstring(path.ToWString());
    }

    // Get the status of a path (WinRT)
    FSResult FileSystem::Check(const Path& path)
    {
        try
        {
            auto item = winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(to_hstring(path)).get();
            if (item)
            {
                return FSResult::Exists;
            }
            else
            {
                return FSResult::NotFound;
            }
        } catch (const winrt::hresult_error& e)
        {
            if (e.code() == E_ACCESSDENIED)
            {
                return FSResult::NotAuthorized;
            }
            return FSResult::UnknownError;
        }
    }

    // Check if the path exists (WinRT)
    bool FileSystem::Exists(const Path& path)
    {
        return Check(path) == FSResult::Exists;
    }

    // Check if a specific item within the path exists (WinRT)
    bool FileSystem::Exists(const Path& path, std::string_view name)
    {
        Path fullPath = Path(path.toString() + "\\" + std::string(name));
        return Exists(fullPath);
    }

    // Create a file or directory at the specified path (WinRT)
    FSResult FileSystem::Create(const Path& path, bool canOverride)
    {
        try
        {
            auto folder = winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(to_hstring(path.Parent())).get();
            if (path.isFile())
            {
                if (canOverride)
                {
                    auto file = folder.CreateFileAsync(path.Name(), winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting).get();
                }
                else
                {
                    auto file = folder.CreateFileAsync(path.Name(), winrt::Windows::Storage::CreationCollisionOption::FailIfExists).get();
                }
            }
            else if (path.isDirectory())
            {
                if (canOverride)
                {
                    auto subfolder = folder.CreateFolderAsync(path.Name(), winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting).get();
                }
                else
                {
                    auto subfolder = folder.CreateFolderAsync(path.Name(), winrt::Windows::Storage::CreationCollisionOption::FailIfExists).get();
                }
            }
            return FSResult::Exists;
        } catch (...)
        {
            return FSResult::UnknownError;
        }
    }

    // Create a file or directory at the specified path with a given name (WinRT)
    FSResult FileSystem::Create(const Path& path, std::string_view name, bool canOverride)
    {
        return Create(Path(path.toString() + "\\" + std::string(name)), canOverride);
    }

    // Copy a file or directory from one path to another (WinRT)
    FSResult FileSystem::Copy(const Path& from, const Path& to)
    {
        try
        {
            auto sourceItem = winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(to_hstring(from)).get();
            auto destFolder = winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(to_hstring(to.Parent())).get();
            sourceItem.CopyAsync(destFolder, to.Name(), winrt::Windows::Storage::NameCollisionOption::ReplaceExisting).get();
            return FSResult::Exists;
        } catch (...)
        {
            return FSResult::UnknownError;
        }
    }

    // Delete a file or directory at the specified path (WinRT)
    bool FileSystem::Delete(const Path& path)
    {
        try
        {
            auto item = winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(to_hstring(path)).get();
            if (item)
            {
                item.DeleteAsync().get();
                return true;
            }
            return false;
        } catch (...)
        {
            return false;
        }
    }

    // Delete a specific item within the path (WinRT)
    bool FileSystem::Delete(const Path& path, std::string_view name)
    {
        return Delete(Path(path.toString() + "\\" + std::string(name)));
    }

}// namespace NGIN::IO
