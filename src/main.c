#include "main.h"
#include "devices.h"

int __init initialize(void)
{
    // Error return value
    int ret = 0;

    // Register the new device
    if ((ret = netlink_register()) != 0) {
        pr_warn("Link registration failed.");
        return ret;
    }

    pr_info("Initialized.");
    return ret;
}

void __init uninitialize(void)
{
    // Unregister the device
    netlink_unregister();

    pr_info("Uninitialized.");
}

module_init(initialize);
module_exit(uninitialize);
