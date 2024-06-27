#include <NGIN/IO/Path.hpp>
#include <boost/ut.hpp>
using namespace boost::ut;
using namespace NGIN::IO;

suite<"PathTests"> _ = [] {
    "DefaultConstructor"_test = [] {
        Path path;
        expect(path.IsEmpty()) << "Default constructed path should be empty";
    };

    "CharConstructor"_test = [] {
        Path path("C:\\Users\\user");
        expect(!path.IsEmpty()) << "Path should not be empty";
        expect(path.IsAbsolute()) << "Path should be absolute";
    };

    "StringViewConstructor"_test = [] {
        std::string_view svPath = "C:\\Users\\user";
        Path path(svPath);
        expect(!path.IsEmpty()) << "Path should not be empty";
        expect(path.IsAbsolute()) << "Path should be absolute";
    };

    "CopyConstructor"_test = [] {
        Path path1("C:\\Users\\user");
        Path path2(path1);
        expect(path1 == path2) << "Copied path should be equal to the original";
    };

    "MoveConstructor"_test = [] {
        Path path1("C:\\Users\\user");
        Path path2(std::move(path1));
        expect(!path2.IsEmpty()) << "Moved path should not be empty";
    };

    "AssignmentOperator"_test = [] {
        Path path1("C:\\Users\\user");
        Path path2 = path1;
        expect(path1 == path2) << "Assigned path should be equal to the original";
    };

    "MoveAssignmentOperator"_test = [] {
        Path path1("C:\\Users\\user");
        Path path2 = std::move(path1);
        expect(!path2.IsEmpty()) << "Moved path should not be empty";
    };

    "StringViewAssignment"_test = [] {
        Path path;
        path = "C:\\Users\\user";
        expect(path.IsAbsolute()) << "Path should be absolute";
    };

    "ConcatenatePaths"_test = [] {
        Path path1("C:\\Users");
        Path path2("user");
        Path path3 = path1 + path2;
        expect(path3.GetPathString() == "C:/Users/user") << "Concatenated path should be C:/Users/user";
    };

    "ConcatenateStringView"_test = [] {
        Path path("C:\\Users");
        path += "user";
        expect(path.GetPathString() == "C:/Users/user") << "Concatenated path should be C:/Users/user";
    };

    "CombinePathsUsingSeparator"_test = [] {
        Path path1("C:\\Users");
        Path path2("user");
        Path path3 = path1 / path2;
        expect(path3.GetPathString() == "C:/Users/user") << "Combined path should be C:/Users/user";
    };

    "CombineStringViewUsingSeparator"_test = [] {
        Path path("C:\\Users");
        path /= "user";
        expect(path.GetPathString() == "C:/Users/user") << "Combined path should be C:/Users/user";
    };

    "AppendPath"_test = [] {
        Path path("C:\\Users");
        path.Append("user");
        expect(path.GetPathString() == "C:/Users/user") << "Appended path should be C:/Users/user";
    };

    "ClearPath"_test = [] {
        Path path("C:\\Users\\user");
        path.Clear();
        expect(path.IsEmpty()) << "Cleared path should be empty";
    };

    "NormalizePath"_test = [] {
        Path path("C:\\Users\\.\\user\\");
        path.Normalize();
        expect(path.GetPathString() == "C:/Users/user/") << "Normalized path should be C:/Users/user/";
    };

    "SetPath"_test = [] {
        Path path;
        path.Set("C:\\Users\\user");
        expect(path.GetPathString() == "C:/Users/user") << "Set path should be C:/Users/user";
    };

    "GetNormalizedPath"_test = [] {
        Path path("C:\\Users\\.\\user\\");
        Path normalizedPath = path.GetNormalized();
        expect(normalizedPath.GetPathString() == "C:/Users/user/") << "Normalized path should be C:/Users/user/";
    };

    "IsValidPath"_test = [] {
        Path path("C:\\Users\\user");
        expect(path.IsValid()) << "Path should be valid";
    };

    "IsEmptyPath"_test = [] {
        Path path;
        expect(path.IsEmpty()) << "Path should be empty";
    };

    "IsAbsolutePath"_test = [] {
        Path path("C:\\Users\\user");
        expect(path.IsAbsolute()) << "Path should be absolute";
    };

    "IsRelativePath"_test = [] {
        Path path("user");
        expect(path.IsRelative()) << "Path should be relative";
    };

    "IsRootPath"_test = [] {
        Path path("C:\\");
        expect(path.IsRoot()) << "Path should be root";
    };

    "IsDirectoryPath"_test = [] {
        Path path("C:\\Users\\user\\");
        expect(path.IsDirectory()) << "Path should be a directory";
    };

    "IsFilePath"_test = [] {
        Path path("C:\\Users\\user\\file.txt");
        expect(path.IsFile()) << "Path should be a file";
    };

    "ToStringTest"_test = [] {
        Path path("C:\\Users\\user");
        expect(path.ToString() == "C:/Users/user") << "Stringified path should be C:/Users/user";
    };

    "CurrentPath"_test = [] {
        Path currentPath = Path::Current();
        expect(!currentPath.IsEmpty()) << "Current path should not be empty";
    };

    "AbsolutePathResolution"_test = [] {
        Path path("/Foo/Test");
        expect(path.IsAbsolute()) << "Path should be absolute";
        // The drive letter should be the main drive (e.g., "C:/Foo/Test")
        path.Normalize();
        expect(path.IsAbsolute()) << "Path should still be absolute after normalization";

        expect(std::isupper(path.GetPathString().at(0)));
        expect(path.GetPathString().at(1) == ':');
        expect(path.GetPathString().at(2) == Path::SEPARATOR);
    };

    "MultipleSeparators"_test = [] {
        Path path("C:\\Users\\\\user\\\\");
        path.Normalize();
        expect(path.GetPathString() == "C:/Users/user/") << "Normalized path should handle multiple separators correctly";
    };

    "RelativePathWithDots"_test = [] {
        Path path("C:\\Users\\user\\..\\otheruser");
        path.Normalize();
        expect(path.GetPathString() == "C:/Users/otheruser") << "Normalized path should correctly resolve ..";
    };

    "HandlingTrailingSeparators"_test = [] {
        Path dirPath("C:\\Users\\user\\");
        expect(dirPath.IsDirectory()) << "Path should be a directory";

        Path filePath("C:\\Users\\user\\file.txt");
        expect(filePath.IsFile()) << "Path should be a file";
    };

    "EmptyPathAppend"_test = [] {
        Path path;
        path.Append("user");
        expect(path.GetPathString() == "user") << "Appending to an empty path should work correctly";
    };

    "EmptyPathSet"_test = [] {
        Path path;
        path.Set("C:\\Users\\user");
        expect(path.GetPathString() == "C:/Users/user") << "Setting an empty path should work correctly";
    };

    "MainDriveAbsolutePathResolution"_test = [] {
        Path path("/Foo/Test");
        NGIN::String mainDrive = "C:";// Assume main drive is C: for this test
        path.Set(mainDrive + path.GetPathString());
        expect(path.GetPathString() == mainDrive + "/Foo/Test") << "Path should correctly resolve with main drive";
    };

    "AppendingMultipleRelativePaths"_test = [] {
        Path path("C:\\Users");
        path.Append("user");
        path.Append("documents");
        expect(path.GetPathString() == "C:/Users/user/documents") << "Path should append multiple relative paths correctly";
    };

    "AppendingPathToRootPath"_test = [] {
        Path rootPath("C:\\");
        rootPath.Append("Users");
        expect(rootPath.GetPathString() == "C:/Users") << "Appending relative path to root path should work correctly";
    };

    "EmptyStringPath"_test = [] {
        Path path;
        path.Set("");
        expect(path.IsEmpty()) << "Setting an empty string should result in an empty path";
    };
};
