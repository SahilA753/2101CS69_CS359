from scapy.all import *

#SRC IP
src_ip_a = "192.168.1.100"  
#Dest IP
dst_ip_b = "192.168.1.200"  
src_port_a = 12345  
dst_port_b = 80  

#Sending Packet
packet_ab = IP(src=src_ip_a, dst=dst_ip_b) / TCP(sport=src_port_a, dport=dst_port_b, flags="S")

#SRC IP
src_ip_b = "192.168.1.200"  
#Dest IP
dst_ip_a = "192.168.1.100"  
src_port_b = 80 
dst_port_a = 12345  


#Sending reverse Packet
packet_ba = IP(src=src_ip_b, dst=dst_ip_a) / TCP(sport=src_port_b, dport=dst_port_a, flags="S")

packets = [packet_ab, packet_ba]

pcap_filename = "C:/Users/agraw/Downloads/two_tcp_packets.pcap"

#Saving file
pcap_writer = PcapWriter(pcap_filename)

for packet in packets:
    send(packet, verbose=False)
    pcap_writer.write(packet)


pcap_writer.close()

print("Two TCP packets captured and saved to", pcap_filename)
