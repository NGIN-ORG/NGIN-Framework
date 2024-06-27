#include <NGIN/IO/FileSystem.hpp>

#include <winerror.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.h>

namespace NGIN::IO
{
    bool FileSystem::Exists(const Path& path)
    {
#ifdef NGIN_PLATFORM_WINDOWS
        WString pathStr = path.ToWString();
        using namespace winrt::Windows::Storage;
        try
        {
            if (path.IsFile())
            {
                StorageFile file = StorageFile::GetFileFromPathAsync(winrt::to_hstring(pathStr.c_str())).get();
                return true;
            }

            StorageFolder folder = StorageFolder::GetFolderFromPathAsync(winrt::to_hstring(pathStr.c_str())).get();
            return true;
        } catch (const winrt::hresult_error& ex)
        {
            if (ex.code() == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                return false;
            }
            throw;// Re-throw the exception for other error cases
        }
#else

#endif
    }


}// namespace NGIN::IO