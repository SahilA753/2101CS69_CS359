from scapy.all import *

#SRC Packet
src_ip_a = "192.168.1.100" 
#Dest Packet
dst_ip_b = "192.168.1.200"  
src_port_a = 12345  
dst_port_b = 12346  

#Packet UDP
packet_ab = IP(src=src_ip_a, dst=dst_ip_b) / UDP(sport=src_port_a, dport=dst_port_b)

#SRC packet
src_ip_b = "192.168.1.200"  
#Dest Packet
dst_ip_a = "192.168.1.100"  
src_port_b = 12346 
dst_port_a = 12345  

#Reverse Packet UDP
packet_ba = IP(src=src_ip_b, dst=dst_ip_a) / UDP(sport=src_port_b, dport=dst_port_a)

packets = [packet_ab, packet_ba]

pcap_filename = "C:/Users/agraw/Downloads/two_udp_packets.pcap"

#Writing pAcket
pcap_writer = PcapWriter(pcap_filename)

for packet in packets:
    send(packet, verbose=False)
    pcap_writer.write(packet)

pcap_writer.close()

print("Two UDP packets captured and saved to", pcap_filename)
