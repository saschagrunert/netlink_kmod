#include "netlink.h"

/// Static options for the netlink registration
static struct rtnl_link_ops options __read_mostly = {
    .kind = KBUILD_MODNAME, .priv_size = 0, .setup = NULL, .newlink = NULL,
};

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
