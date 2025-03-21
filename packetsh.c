#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/slab.h>

static struct nf_hook_ops nfho;

unsigned int packet_hook(void *priv, struct sk_buff *skb,
                         const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    struct udphdr *udp_header;
    
    if (!skb)
        return NF_ACCEPT;

    ip_header = ip_hdr(skb);
    if (!ip_header)
        return NF_ACCEPT;

    if (ip_header->protocol == IPPROTO_TCP) {
        tcp_header = (struct tcphdr *)((__u32 *)ip_header + ip_header->ihl);
        if (tcp_header) {
            printk(KERN_INFO "TCP Packet: Src Port: %u, Dst Port: %u\n",
                   ntohs(tcp_header->source), ntohs(tcp_header->dest));
        }
    } else if (ip_header->protocol == IPPROTO_UDP) {
        udp_header = (struct udphdr *)((__u32 *)ip_header + ip_header->ihl);
        if (udp_header) {
            printk(KERN_INFO "UDP Packet: Src Port: %u, Dst Port: %u\n",
                   ntohs(udp_header->source), ntohs(udp_header->dest));
        }
    }

    return NF_ACCEPT;
}

static int __init packet_shortener_init(void) {
    nfho.hook = packet_hook;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Packet Shortener Module Loaded\n");
    return 0;
}

static void __exit packet_shortener_exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Packet Shortener Module Unloaded\n");
}

module_init(packet_shortener_init);
module_exit(packet_shortener_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayy Man");
MODULE_DESCRIPTION("Kernel Module for Packet Shortening and Filtering");
