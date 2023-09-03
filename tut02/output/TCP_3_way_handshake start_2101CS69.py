import scapy.all as scapy

# Target Website and Port
target_ip = "149.28.158.93"
target_port = 443  # 443 for HTTPS

# Create the SYN PACKET
SYN_PACKET = scapy.IP(dst=target_ip) / scapy.TCP(dport=target_port, flags="S")

# Send and receive the RESPONSE
RESPONSE = scapy.sr1(SYN_PACKET, timeout=2, verbose=True)

# Define the pcap file name for saving the packets
pcap_filename = "tcp_handshake.pcap"

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
