export module NGIN.Logging:MTLogger;
export import std;

import :ILogger;
import :ISink;
import :LogLevel;

import NGIN.Containers;
import NGIN.Memory;
import std;

namespace NGIN::Logging
{
    export template<typename FormatterType>
    class MTLogger final : public ILogger
    {
    public:
        MTLogger() : running(true), logThread(&MTLogger::ProcessQueue, this) {}

        ~MTLogger()
        {
            Shutdown();
        }

        void Initialize() override
        {
            std::lock_guard<std::mutex> lock(mutex);
            for (const auto& sink: sinks)
            {
                sink->Initialize();
            }
        }

        void Shutdown() override
        {
            {
                std::lock_guard<std::mutex> lock(mutex);
                running = false;
            }
            cv.notify_one();
            if(logThread.joinable())
                logThread.join();
        }

        void Flush() override
        {
            std::lock_guard<std::mutex> lock(mutex);
            for (const auto& sink: sinks)
            {
                sink->Flush();
            }
        }

        template<typename T, typename... Args>
        MTLogger<FormatterType>& AddSink(Args&&... args)
        {
            std::lock_guard<std::mutex> lock(mutex);
            sinks.emplace_back(CreateScope<T>(std::forward<Args>(args)...));
            return *this;
        }

        void Log(const LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) override
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            logQueue.push(LogMessage {level, message, source});
            cv.notify_one();
        }

    private:
        struct LogMessage
        {
            LogLevel level;
            String message;
            std::source_location source;
        };

        std::mutex mutex;
        std::mutex queueMutex;
        std::condition_variable cv;
        std::queue<LogMessage> logQueue;
        bool running;
        std::thread logThread;
        FormatterType formatter = {};
        Vector<Scope<ISink>> sinks = {};

        void ProcessQueue()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                cv.wait(lock, [this] { return !logQueue.empty() || !running; });

                while (!logQueue.empty())
                {
                    LogMessage logMessage = logQueue.front();
                    logQueue.pop();
                    lock.unlock();

                    for (const auto& sink: sinks)
                    {
                        sink->Log(logMessage.level, formatter.Format(logMessage.level, logMessage.message, logMessage.source));
                    }

                    lock.lock();
                }

                if (!running && logQueue.empty())
                    break;
            }
        }
    };
}// namespace NGIN::Logging
