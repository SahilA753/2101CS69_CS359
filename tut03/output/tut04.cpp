#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <cstring>

const char* targetIpAddress = "202.137.235.71";

void packet_handler(u_char* user, const struct pcap_pkthdr* header, const u_char* packet) {
    pcap_dump(user, header, packet);
    // Add any specific packet handling logic if needed
}

int main() {
    const char* iface = "wlop"; // Change this to your network interface
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open the network interface for packet capture
    pcap_t* handle = pcap_open_live(iface, BUFSIZ, 1, 100, errbuf); // Promiscuous mode and timeout of 100 ms
    if (handle == nullptr) {
        fprintf(stderr, "Couldn't open device %s: %s\n", iface, errbuf);
        return 1;
    }

    // Create and open a PCAP dump file for all packets
    pcap_dumper_t* pcap_dumper = pcap_dump_open(handle, "/home/sahil/Desktop/all_packets.pcap");
    if (pcap_dumper == nullptr) {
        fprintf(stderr, "Couldn't open PCAP dump file: %s\n", pcap_geterr(handle));
        return 1;
    }

    // Capture packets for 60 seconds
    time_t startTime = time(nullptr);
    while (time(nullptr) - startTime < 60) {
        pcap_loop(handle, 1, packet_handler, (u_char*)pcap_dumper);
    }

    pcap_dump_close(pcap_dumper); // Close the PCAP dump file
// Now, open the all_packets.pcap file for reading
    pcap_t* reding_hndlr = pcap_open_offline("/home/sahil/Desktop/all_packets.pcap", eerr);
    if (reding_hndlr == nullptr) {
        fprintf(stderr, "Couldn't open all_packets.pcap for reading: %s\n", eerr);
        return 1;
    }

    // Read packets from all_packets.pcap and write TCP SYN packets from the specific IP to tcp_syn.pcap
    struct pcap_pkthdr header;
    const u_char* packet;
    uint16_t srcprt;
    while ((packet = pcap_next(reding_hndlr, &header))) {
        // Extract and check source IP address
        struct ip* ip_header = (struct ip*)(packet + 14); // Assuming Ethernet header
        // Check if the source IP address matches the target IP address
        struct tcphdr* tcp_header = (struct tcphdr*)(packet + 14 + (ip_header->ip_hl << 2));

        // Convert the source IP address to a string for comparison
        char srcitstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcitstr, INET_ADDRSTRLEN);

        if (strcmp(srcitstr, tipa) == 0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->syn && tcp_header->ack) {
                // Extract the source port from the packet
                srcprt = ntohs(tcp_header->th_dport);
                break;
        }
    }
    pcap_close(reding_hndlr);
    pcap_close(handle);
    
    
    pcap_t* handshake_handle = pcap_open_offline("/home/sahil/Desktop/all_packets.pcap", eerr);
    // Create and open a new PCAP dump file for TCP SYN packets
    pcap_dumper_t* tcp_syn_dumper = pcap_dump_open(handshake_handle, "/home/sahil/Desktop/tcp_open.pcap");
     pcap_dumper_t* only_tcp_dumper = pcap_dump_open(handshake_handle, "/home/sahil/Desktop/tcp_packets.pcap");
    if (tcp_syn_dumper == nullptr) {
        fprintf(stderr, "Couldn't open PCAP dump file for TCP opening handshake packets: %s\n", pcap_geterr(handshake_handle));
        return 1;
    }

    bool syn = 1;
    bool synack = 0;
    bool ack = 0;
    while((packet = pcap_next(handshake_handle, &header))){
        struct ip* ip_header = (struct ip*)(packet + 14); // Assuming Ethernet header
        // Check if the source IP address matches the target IP address
        struct tcphdr* tcp_header = (struct tcphdr*)(packet + 14 + (ip_header->ip_hl << 2));

        // Convert the source IP address to a string for comparison
        char srcitstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcitstr, INET_ADDRSTRLEN);

        char destIpstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_dst), destIpstr, INET_ADDRSTRLEN);
        
        if (syn && strcmp(destIpstr, tipa) == 0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->syn && ntohs(tcp_header->th_sport) == srcprt) {
                // Extract the source port from the packet
                pcap_dump((u_char*)tcp_syn_dumper, &header, packet);
                pcap_dump((u_char*)only_tcp_dumper, &header, packet);
                syn = 0;
                synack = 1;
        }
        else if(synack && strcmp(srcitstr, tipa) == 0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->syn && tcp_header->ack && ntohs(tcp_header->th_dport) == srcprt){
            pcap_dump((u_char*)tcp_syn_dumper, &header, packet);
            pcap_dump((u_char*)only_tcp_dumper, &header, packet);
            synack = 0;
            ack = 1;
        }
        else if(ack && strcmp(destIpstr, tipa) == 0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->ack && ntohs(tcp_header->th_sport) == srcprt){
            pcap_dump((u_char*)tcp_syn_dumper, &header, packet);
            break;
        }
    }
    pcap_dump_close(tcp_syn_dumper); // Close the TCP SYN PCAP dump file
    pcap_close(handshake_handle);
    
    pcap_t* closing = pcap_open_offline("/home/sahil/Desktop/all_packets.pcap", eerr);
    // Create and open a new PCAP dump file for TCP SYN packets
    pcap_dumper_t* tcp_fin_dumper = pcap_dump_open(handshake_handle, "/home/sahil/Desktop/tcp_close.pcap");
    if (tcp_fin_dumper == nullptr) {
        fprintf(stderr, "Couldn't open PCAP dump file for TCP opening handshake packets: %s\n", pcap_geterr(closing));
        return 1;
    }
    bool finack1 = 1;
    bool ack1 = 0;
    bool finack2 = 0;
    bool ack2 = 0;
    while((packet = pcap_next(closing, &header))){
    struct ip* ip_header = (struct ip*)(packet + 14); // Assuming Ethernet header
        // Check if the source IP address matches the target IP address
        struct tcphdr* tcp_header = (struct tcphdr*)(packet + 14 + (ip_header->ip_hl << 2));
        // Convert the source IP address to a string for comparison
        char srcitstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcitstr, INET_ADDRSTRLEN);

        char destIpstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_dst), destIpstr, INET_ADDRSTRLEN);
        if(finack1 && strcmp(destIpstr,tipa)==0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->fin && tcp_header -> ack && (ntohs(tcp_header->th_dport) == srcprt || ntohs(tcp_header->th_sport) == srcprt))
        {
            pcap_dump((u_char*)tcp_fin_dumper, &header, packet);
            finack1 = 0;
            ack1=1;
    }
    else if (ack1 && strcmp(srcitstr,tipa)==0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->ack &&(ntohs(tcp_header->th_dport) == srcprt || ntohs(tcp_header->th_sport) == srcprt))
    {
        pcap_dump((u_char*)tcp_fin_dumper, &header, packet);
            finack2 = 1;
            ack1=0;
    }
    else if (finack2 && strcmp(srcitstr,tipa)==0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->fin && tcp_header->ack &&(ntohs(tcp_header->th_dport) == srcprt || ntohs(tcp_header->th_sport) == srcprt))
    {
        pcap_dump((u_char*)tcp_fin_dumper, &header, packet);
            finack2 = 0;
            ack2=1;
    }
    else if (ack2 && strcmp(destIpstr,tipa)==0 && ip_header->ip_p == IPPROTO_TCP && tcp_header->ack &&(ntohs(tcp_header->th_dport) == srcprt || ntohs(tcp_header->th_sport) == srcprt))
    {
        pcap_dump((u_char*)tcp_fin_dumper, &header, packet);
        break;
    }

    }
    pcap_dump_close(tcp_fin_dumper); // Close the TCP SYN PCAP dump file
    pcap_close(closing);
    
    pcap_t* udp_handle = pcap_open_offline("/home/sahil/Desktop/all_packets.pcap", eerr);
    // Create and open a new PCAP dump file for TCP SYN packets
    pcap_dumper_t* udp_dumper = pcap_dump_open(handshake_handle, "/home/sahil/Desktop/udp_packets.pcap");
    if (udp_dumper == nullptr) {
        fprintf(stderr, "Couldn't open PCAP dump file for TCP opening handshake packets: %s\n", pcap_geterr(udp_handle));
        return 1;
    }
       uint16_t firstudp;
     while((packet = pcap_next(udp_handle, &header))){
    struct ip* ip_header = (struct ip*)(packet + 14); // Assuming Ethernet header
        // Check if the source IP address matches the target IP address
        struct tcphdr* tcp_header = (struct tcphdr*)(packet + 14 + (ip_header->ip_hl << 2));
          struct udphdr *udp_header;
           udp_header = (struct udphdr*)(packet + 14 + (ip_header->ip_hl << 2));
        // Convert the source IP address to a string for comparison
        char srcitstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcitstr, INET_ADDRSTRLEN);

        char destIpstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_dst), destIpstr, INET_ADDRSTRLEN);

        if(ip_header->ip_p == IPPROTO_UDP)
        {
            firstudp = ntohs(udp_header->uh_dport);
            pcap_dump((u_char*)udp_dumper, &header, packet);
            break;
        }
     }
    pcap_close(udp_handle);
    pcap_t* new_udp_handle = pcap_open_offline("/home/sahil/Desktop/all_packets.pcap", eerr);
    // Create and open a new PCAP dump file for TCP SYN packets
          while((packet = pcap_next(new_udp_handle, &header))){
        struct ip* ip_header = (struct ip*)(packet + 14); // Assuming Ethernet header
        // Check if the source IP address matches the target IP address
          struct udphdr *udp_header;
           udp_header = (struct udphdr*)(packet + 14 + (ip_header->ip_hl << 2));
        // Convert the source IP address to a string for comparison
        char srcitstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcitstr, INET_ADDRSTRLEN);

        char destIpstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_dst), destIpstr, INET_ADDRSTRLEN);

        if(ip_header->ip_p == IPPROTO_UDP && ntohs(udp_header->uh_sport) == firstudp)
        {
            pcap_dump((u_char*)udp_dumper, &header, packet);
            break;
        }
     }
    pcap_dump_close(udp_dumper); 
    pcap_close(new_udp_handle);

    // Close handles
    pcap_close(handle);

    return 0;
}
