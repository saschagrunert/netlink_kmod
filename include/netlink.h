#include <net/rtnetlink.h>

/**
 * @brief Register the netlink device
 *
 * @retval  0   on success, anything other on failure
 */
int netlink_register(void);

/**
 * @brief Unregister the netlink device
 */
void netlink_unregister(void);
