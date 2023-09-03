from scapy.all import *

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
