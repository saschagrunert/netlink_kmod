#include <net/rtnetlink.h>

/**
 * @brief A custom netlink device
 */
typedef struct _netlink_device_t {
} netlink_device_t;

/**
 * @brief Register the netlink device
 *
 * @retval  0   on success, anything else on failure
 */
int netlink_register(void);

/**
 * @brief Unregister the netlink device
 */
void netlink_unregister(void);
