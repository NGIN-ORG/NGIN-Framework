
#include <iostream>
#include <source_location>

import NGIN.Logging;
import NGIN.Reflection;
import NGIN.Meta;
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

    using TypeInfo = NGIN::Meta::TypeInfo<TestClass>;
    auto namespaceName = RemoveAnonymousNamespace(TypeInfo::Namespace());
    std::cout << namespaceName << std::endl;

    std::cout << "Hello World!" << std::endl;

    NGIN::Meta::EnumTraits<Logging::LogLevel> te = {};
    std::cout << te.ToString(Logging::LogLevel::Info) << std::endl;

    Logging::SimpleLogger<Logging::SimpleFormatter> logger = {};
    logger.AddSink<Logging::ConsoleSink>();


    logger.Log(NGIN::Logging::LogLevel::Info, "Hey gal");
    logger.Log(NGIN::Logging::LogLevel::Debug, "Hey gal {}", 2);

   // NGIN::Util::Format("test {}", 2);
    return 0;
}
