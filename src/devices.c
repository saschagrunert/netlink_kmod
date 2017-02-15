#include "sockets.h"

void setup(struct net_device * dev);
void destruct(struct net_device * dev);
int newlink(struct net * src_net, struct net_device * dev, struct nlattr * tb[], struct nlattr * data[]);
int ndo_open(struct net_device * dev);
int ndo_stop(struct net_device * dev);

/// Static options for the netlink registration
static struct rtnl_link_ops options __read_mostly = {
    .kind = KBUILD_MODNAME, .priv_size = sizeof(netlink_device_t), .setup = setup, .newlink = newlink,
};

/// Static options for the net device registration
static const struct net_device_ops netdev_options = {.ndo_open = ndo_open, .ndo_stop = ndo_stop};

/// Netlink device registration
int netlink_register(void)
{
    return rtnl_link_register(&options);
}

/// Netlink device cleanup
void netlink_unregister(void)
{
    rtnl_link_unregister(&options);
}

/// The net_device setup function
void setup(struct net_device * dev)
{
    netlink_device_t * device = netdev_priv(dev);

    /// Adapt the net_device settings
    dev->netdev_ops = &netdev_options;
    dev->destructor = destruct;
    dev->hard_header_len = 0;
    dev->addr_len = 0;
    netif_keep_dst(dev);

    /// Set the private structure fields
    memset(device, 0, sizeof(netlink_device_t));

    pr_debug("Setup done");
}

/// Netdevice destruct function
void destruct(struct net_device * dev)
{
    free_netdev(dev);
    pr_debug("Devices deleted: %s", dev->name);
}

/// Function for configuring and registering a new device
int newlink(struct net * src_net, struct net_device * dev, struct nlattr * tb[], struct nlattr * data[])
{
    int ret = 0;

    // Register the net device
    if ((ret = register_netdevice(dev)) != 0) {
        pr_warn("Netdevice registration failed.");
        return ret;
    }

    pr_debug("Device created: %s", dev->name);
    return 0;
}

/// Opens a net device
int ndo_open(struct net_device * dev)
{
    int ret = 0;
    netlink_device_t * device = netdev_priv(dev);

    // Initialize the socket
    if ((ret = socket_initialize(device)) != 0) {
        return ret;
    }

    return ret;
}

int ndo_stop(struct net_device * dev)
{
    netlink_device_t * device = netdev_priv(dev);
    socket_destroy(device);
    return 0;
}
