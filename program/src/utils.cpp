#include <chrono>
#include <cmath>
#include <climits>

/**
 * Get current UNIX epoch time in milliseconds
 * 
 * @return Current time, in epoch.
 */
unsigned long long get_current_time() {
    return std::chrono::system_clock::now().time_since_epoch() / 
        std::chrono::milliseconds(1);
}
