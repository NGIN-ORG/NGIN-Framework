#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Common/Types/String.hpp>

#include <NGIN/Util/ISingleton.hpp>

namespace NGIN::System
{

    NGIN_API struct Info : public Util::ISingleton<Info>
    {
    protected:
        friend class Util::ISingleton<Info>;

        Info();
        ~Info() override = default;

    public:
        String hostName = "N/A"; // Host name
        String osName = "N/A";   // Operating System name
        String osVersion = "N/A";// Operating System version

        String architecture = "N/A";// CPU architecture, e.g., x86_64
        String cpuModel = "N/A";    // CPU model
        UInt32 logicalCores = 0;    // Number of physical CPUs
        UInt32 physicalCores = 0;   // Number of cores per CPU

        UInt64 totalMemMB = 0;           // Total physical RAM size
        UInt64 availableMemMB = 0;       // Currently available physical RAM size
        UInt64 totalVirtualMemMB = 0;    // Total virtual memory size
        UInt64 availableVirtualMemMB = 0;// Currently available virtual memory size

        F64 systemUptime = 0.0;// System uptime in seconds
    };


}// namespace NGIN::System
