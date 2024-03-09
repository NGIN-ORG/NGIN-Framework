import std;
import NGIN.Logging;
import NGIN.Reflection;
import NGIN.Meta;
import NGIN.Util;
import NGIN.Units;

namespace
{


    struct TestClass
    {
        struct NestedClass
        {
        };
    };
}// namespace
constexpr NGIN::StringView RemoveAnonymousNamespace(NGIN::StringView name)
{
    const auto pos = name.find("::");
    return (pos != NGIN::StringView::npos) ? name.substr(pos + 2) : name;
}
int main()
{
    using namespace NGIN;

    const Seconds SECONDS(.01);                     // 120 seconds
    Minutes minutes = static_cast<Minutes>(SECONDS);// Convert seconds to minutes

    std::cout << "Microseconds: " << static_cast<Microseconds>(SECONDS) << std::endl;
    std::cout << Util::RuntimeFormat("Milliseconds: {}", static_cast<Milliseconds>(SECONDS)) << std::endl;

    using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
    const auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
    std::cout << namespaceName << std::endl;

    std::cout << "Hello World!" << std::endl;

    NGIN::Meta::EnumTraits<Logging::LogLevel> te = {};
    std::cout << te.ToString(Logging::LogLevel::Info) << std::endl;

    Logging::SimpleLogger<Logging::SimpleFormatter> logger = {};
    logger.AddSink<Logging::ConsoleSink>();


    logger.Log(NGIN::Logging::LogLevel::Info, "Hey gal");

    // NGIN::Util::Format("test {}", 2);
    return 0;
}
