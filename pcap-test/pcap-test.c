#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <libnet.h>
//#include "pcap-test.h"


//Ethernet header => print mac address
void print_mac_addr(uint8_t *mac){

        //prinf ex) %02x  00:12:34:56:78:90
        for(int i=0; i<6; i++){
                printf("%02x", mac[i]);
                if(i!=5)printf(":");
        }
       
       	return;
}

void print_eth(struct libnet_ethernet_hdr *ethernet_header){
        
	printf("MAC	src:	");
	print_mac_addr(ethernet_header->ether_shost);
        printf("\nMAC	dst:	");
	print_mac_addr(ethernet_header->ether_dhost);
       	return;
}



//IP header => print ip address
void print_ip_addr(struct in_addr ip){
	
	char *str = inet_ntoa(ip); //네트워크주소변환 함수
	printf("	%s\n", str);
}


void print_ip(struct libnet_ipv4_hdr *ipv4_hdr){

	printf("\nIP	src: ");
	print_ip_addr(ipv4_hdr->ip_src);
	printf("IP	dst: ");
	print_ip_addr(ipv4_hdr->ip_dst);

	return;
}

//TCP header => print port
void print_port(uint16_t port){
	
	printf("%d\n", ntohs(port));
	return;
}

void print_tcp(struct libnet_tcp_hdr *tcp_hdr){
	
	printf("Port	src:	");
	print_port(tcp_hdr->th_sport);
	printf("Port	dst:	");
	print_port(tcp_hdr->th_dport);

	return;
}

//print Data
void print_data(const uint8_t *data, uint8_t data_base, uint8_t data_len){

	printf("Data	:	");

	if (data_len == 0)
		printf("Empty Data");
	else if (data_len > 8)
		data_len = 8;

	for(int i = 0; i < data_len; i++){
		printf("%x", data[data_base + i]);
	}

	return;
}






void usage() {
	printf("syntax: pcap-test <interface>\n");
	printf("sample: pcap-test wlan0\n");
}

typedef struct {
	char* dev_;
} Param;

Param param = {
	.dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
	if (argc != 2) {
		usage();
		return false;
	}
	param->dev_ = argv[1];
	return true;
}

int main(int argc, char* argv[]) {
	if (!parse(&param, argc, argv))
		return -1;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
	if (pcap == NULL) {
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
		return -1;
	}


	int packet_num = 1;

	while (true) {
		struct pcap_pkthdr* header;
		const u_char* packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == 0) continue;
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}
		
		//printf("%u bytes captured\n", header->caplen);
		printf("\n\n");
		printf("Packet	Number:	%d\n", packet_num);
		printf("Packet	Size:	%d bytes\n", header->len);

		//ethernet 헤더 => mac address print   
		struct libnet_ethernet_hdr *ethernet_header = (struct libnet_ethernet_hdr *) packet;
		print_eth(ethernet_header);
				
		//ipv4 헤더 => ip address print
		struct libnet_ipv4_hdr *ipv4_hdr = (struct libnet_ipv4_hdr *)(packet + sizeof(struct libnet_ethernet_hdr));
		print_ip(ipv4_hdr);
		
		//TCP헤더 => port print
		struct libnet_tcp_hdr *tcp_hdr = (struct libnet_tcp_hdr *)(packet + sizeof(struct libnet_ethernet_hdr) + sizeof(struct libnet_ipv4_hdr));
		print_tcp(tcp_hdr);

		//Data
		uint8_t data_base = sizeof(struct libnet_ethernet_hdr) + sizeof(struct libnet_ipv4_hdr) + sizeof(struct libnet_tcp_hdr);
		uint8_t data_len = ntohs(ipv4_hdr->ip_len) - sizeof(ipv4_hdr) - sizeof(tcp_hdr);
		print_data(packet, data_base, data_len);

		packet_num++;
	}

	pcap_close(pcap);
}
