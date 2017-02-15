#include "devices.h"

/**
 * @brief Initialize the socket
 *
 * @param[in]   device  the created netlink device
 * @retval      0       on success, anything else on failure
 */
int socket_initialize(netlink_device_t * device);

/**
 * @brief Uninitialize the socket
 *
 * @param[in]   device  the created netlink device
 */
void socket_destroy(netlink_device_t * device);
