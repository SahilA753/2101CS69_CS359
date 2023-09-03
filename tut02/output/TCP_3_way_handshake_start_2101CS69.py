from scapy.all import *

#target ip
target_ip = "149.28.158.93"
dport = 443

#ip packet
IPPKT = IP(dst=target_ip)
#syn packet
SYNPKT = TCP(dport=dport, flags="S")

SynAckResp = sr1(IPPKT / SYNPKT)

if SynAckResp is None:
    print("No response received.")
else:
    #ack packet
    ACKPKT = TCP(dport=dport, flags="A", seq=SynAckResp.ack, ack=SynAckResp.seq + 1)

    send(IPPKT / ACKPKT)

    print("TCP 3-way handshake completed.")
    
fin_packet = TCP(dport=dport, flags="FA", seq=SynAckResp.ack, ack=SynAckResp.seq + 1)

FinAckResp = sr1(IPPKT / fin_packet)

ACKPKT = TCP(dport=dport, flags="A", seq=FinAckResp.ack, ack=FinAckResp.seq + 1)
#and all the responses written in file
send(IPPKT / ACKPKT)

packets = [IPPKT / fin_packet, FinAckResp, IPPKT / ACKPKT]
wrpcap("C:/Users/agraw/Downloads/TCP_handshake_close_2101CS69.pcap", packets)
