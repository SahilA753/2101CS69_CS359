import scapy.all as scapy

# Target Website and Port
target_ip = "149.28.158.93"
target_port = 443  # 443 for HTTPS

# Create the SYN PACKET
SYN_PACKET = scapy.IP(dst=target_ip) / scapy.TCP(dport=target_port, flags="S")

# Send and receive the RESPONSE
RESPONSE = scapy.sr1(SYN_PACKET, timeout=2, verbose=True)

# Define the pcap file name for saving the packets
pcap_filename = "TCP_3_way_handshake_start_2101CS69.pcap"

# Create a PcapWriter for saving packets
pcap_writer = scapy.PcapWriter(pcap_filename)

# Write the SYN packet to the pcap file
pcap_writer.write(SYN_PACKET)

if RESPONSE:
    if RESPONSE.haslayer(scapy.TCP) and RESPONSE.getlayer(scapy.TCP).flags == 0x12:
        # Create the ACK packet
        ack_packet = scapy.IP(dst=target_ip) / scapy.TCP(dport=target_port, flags="A", ack=RESPONSE.getlayer(scapy.TCP).seq + 1)
        
        # Write RESPONSE and ACK packets to the pcap file
        pcap_writer.write(RESPONSE)
        pcap_writer.write(ack_packet)

        print(f"TCP three-way handshake packets saved to {pcap_filename}")
    else:
        print("No valid RESPONSE received.")
else:
    print("No RESPONSE received.")

# Close the PCAP file
pcap_writer.close()






target_ip = "149.28.158.93"
dport = 443

# Creating IP and TCP packets
IP_PACKET = IP(dst=target_ip)
SYN_PACKET = TCP(dport=dport, flags="S")
SYN_ACK_RESPONSE = sr1(IP_PACKET / SYN_PACKET)

if SYN_ACK_RESPONSE is None:
    print("No response received.")
else:
    ACK_PACKET = TCP(dport=dport, flags="A", seq=SYN_ACK_RESPONSE.ack, ack=SYN_ACK_RESPONSE.seq + 1)

    send(IP_PACKET / ACK_PACKET)

    print("TCP 3-way handshake completed.")
        
    FIN_PACKET = TCP(dport=dport, flags="FA", seq=SYN_ACK_RESPONSE.ack, ack=SYN_ACK_RESPONSE.seq + 1)

    FIN_ACK_RESPONSE = sr1(IP_PACKET / FIN_PACKET)

    ACK_PACKET = TCP(dport=dport, flags="A", seq=FIN_ACK_RESPONSE.ack, ack=FIN_ACK_RESPONSE.seq + 1)

    send(IP_PACKET / ACK_PACKET)

# Create a PcapWriter for saving packets to a PCAP file
pcap_filename = "C:/Users/agraw/Downloads/TCP_handshake_close_2101CS69.pcap"
pcap_writer = PcapWriter(pcap_filename)

# Write the packets to the PCAP file
packets = [IP_PACKET / SYN_PACKET, SYN_ACK_RESPONSE, IP_PACKET / ACK_PACKET, FIN_PACKET, FIN_ACK_RESPONSE, ACK_PACKET]

for packet in packets:
    pcap_writer.write(packet)

pcap_writer.close()

print("Packet details saved to", pcap_filename)








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

pcap_filename = "C:/Users/agraw/Downloads/TCP_Packets_2101CS69.pcap"

#Saving file
pcap_writer = PcapWriter(pcap_filename)

for packet in packets:
    send(packet, verbose=False)
    pcap_writer.write(packet)


pcap_writer.close()

print("Two TCP packets captured and saved to", pcap_filename)







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

pcap_filename = "C:/Users/agraw/Downloads/UDP_Packets_2101CS69.pcap"

#Writing pAcket
pcap_writer = PcapWriter(pcap_filename)

for packet in packets:
    send(packet, verbose=False)
    pcap_writer.write(packet)

pcap_writer.close()

print("Two UDP packets captured and saved to", pcap_filename)
