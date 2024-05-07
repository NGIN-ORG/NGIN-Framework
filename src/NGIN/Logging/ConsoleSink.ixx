
export module NGIN.Logging:ConsoleSink;

export import NGIN.Types;
import :ISink;
import :LogLevel;
import std;
namespace NGIN::Logging
{
    export class ConsoleSink : public ISink
    {
    public:
        bool Initialize() override;

        void Shutdown() override;

        void Log(LogLevel level, const String& message) override;

        void Flush() override;

    };

    bool ConsoleSink::Initialize()
    {
        return std::cout.rdbuf() != nullptr;
    }
    void ConsoleSink::Shutdown()
    {
        
    }
    void ConsoleSink::Log(LogLevel level, const String& message)
    {
        std::cout << message << "\n";
    }

    void ConsoleSink::Flush()
    {
        std::cout.flush();
    }
}// namespace NGIN::Logging